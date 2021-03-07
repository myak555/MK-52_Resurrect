//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    //
    // Implements the state engine
    //
    public class MK52_Host
    {
        // hardware emulators
        public LCD_Manager _m_Hardware_LCD = null;
        public KBD_Manager _m_Hardware_KBD = null;
        public SD_Manager _m_Hardware_SD = new SD_Manager();

        // calculator state engine
        public RPN_Stack _m_RPN_Stack = new RPN_Stack();
        public Program_Memory _m_Program_Memory = new Program_Memory();
        public Extended_Memory _m_Extended_Memory = new Extended_Memory();
        public Register_Memory _m_Register_Memory = new Register_Memory();
        public RPN_Functions _m_RPN_Functions = new RPN_Functions();

        // receivers
        public Dictionary<string, Receiver> Receivers =
            new Dictionary<string, Receiver>();
        public Receiver current_Receiver = null;

        private string _stateFile = "";

        public MK52_Host( KBD_Manager kbd, LCD_Manager lcd)
        {
            _m_Hardware_KBD = kbd;
            _m_Hardware_LCD = lcd;
            addReceivers();
            _stateFile = AppDomain.CurrentDomain.BaseDirectory + "_RPN_State_New.txt";
        }

        public void init()
        {
            _m_Hardware_LCD.init();
            _m_Hardware_SD.init();

            _m_Program_Memory.init(this);
            _m_Extended_Memory.init(this);
            _m_Register_Memory.init(this);
            _m_RPN_Stack.init(this);
            _m_RPN_Functions.init(this);

            // Show splash (if "Undefined", the return receiver is set by loadState!)
            this.current_Receiver.activate( "Undefined");
            
            // Hide status loading behind splash
            _m_RPN_Functions.loadState();
        }

        /// <summary>
        /// Fake functon for C++ emulation 
        /// </summary>
        public LCD_Manager getLCD()
        {
            return _m_Hardware_LCD;
        }

        /// <summary>
        /// Fake functon for C++ emulation 
        /// </summary>
        public KBD_Manager getKBD()
        {
            return _m_Hardware_KBD;
        }

        /// <summary>
        /// Fake functon for C++ emulation 
        /// </summary>
        public SD_Manager getSD()
        {
            return _m_Hardware_SD;
        }

        /// <summary>
        /// Fake functon for C++ emulation 
        /// </summary>
        public RPN_Functions getFunctions()
        {
            return _m_RPN_Functions;
        }

        /// <summary>
        /// Runs one simulation cycle
        /// </summary>
        public void tick()
        {
            byte b = _m_Hardware_KBD.scan();
            // must be done once for display delayed update
            do
            {
                b = current_Receiver.tick(b);
                if (setRequestedReceiver()) break;
            }
            while (b > 0);
            _m_Hardware_LCD.update();
        }

        /// <summary>
        /// Returns the receiver by name
        /// </summary>
        public Receiver getReceiver(string name)
        {
            if (!Receivers.ContainsKey(name)) return null;
            return Receivers[name];
        }

        /// <summary>
        /// Sets receiver
        /// </summary>
        /// <param name="name">Receiver moniker</param>
        /// <returns>true if receiver is not available</returns>
        public bool setReceiver(string name)
        {
            Receiver ri = getReceiver( name);
            if (ri == null) return true;
            ri.activate( current_Receiver.Moniker);
            current_Receiver = ri;
            return false;
        }

        /// <summary>
        /// Sets receiver
        /// </summary>
        /// <param name="name">Receiver moniker</param>
        /// <returns>true if receiver change is not requested</returns>
        public bool setRequestedReceiver()
        {
            Receiver ri = getReceiver(_m_RPN_Functions.getRequestedReceiver());
            if (ri == null) return true;
            string return_to = _m_RPN_Functions.getRequestedReturnReceiver();
            if (return_to == "None") return_to = current_Receiver.Moniker;
            ri.activate(return_to);
            current_Receiver = ri;
            return false;
        }

        public void shutdown()
        {
            // TODO: Simulator dog-and-pony here
            _m_Hardware_LCD.clearScreen();
            _m_Hardware_LCD.showSplash();
            _m_Hardware_LCD.forcePaint();
            string returnReceiver = current_Receiver.Moniker;

            // checks for Simulator only;
            // the actual ESP32 hardware is simply off!
            switch (returnReceiver)
            {
                case "OFF":
                case "CONFIRMATION":
                case "Data_Erase":
                case "Prog_Erase":
                    returnReceiver = current_Receiver.getReturnReceiverMoniker();
                    break;
                case "ADDRESS":
                case "ADDRESS_AMX":
                case "ADDRESS_AXM":
                case "ADDRESS_MC":
                case "ADDRESS_PC":
                case "NUMBER":
                case "NUMBER_DATA":
                case "NUMBER_PROG":
                case "TEXT":
                    current_Receiver.tick(31);
                    returnReceiver = current_Receiver.getReturnReceiverMoniker();
                    break;
                default:
                    break;
            }
            _m_RPN_Functions.saveState(returnReceiver);
            _m_Hardware_LCD.clearScreen();
            _m_Hardware_LCD.forcePaint();
        }

        #region Implemented Functions
        public void listFunctions(string filename)
        {
            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = File.Open(filename, FileMode.Create, FileAccess.Write, FileShare.Read);
                sw = new StreamWriter(fs);

                sw.Write("#\n");
                sw.Write("# MK-52 implemented functions " + DateTime.Now.ToString("dd-MMM-yyyy HH:mm:ss\n"));
                sw.Write("#\n");
                for( int i = 0; i<RPN_Functions.MK52_NFUNCTIONS; i++)           
                {
                    sw.Write( i.ToString("000"));
                    sw.Write("\t");
                    RPN_Function f = _m_RPN_Functions.getFunctionByID( (uint)i);
                    if( f==null)
                    {
                        sw.Write("slot empty\n");
                        continue;
                    }
                    if( f.IOName() == null || f.IOName().Length == 0) sw.Write("No name");
                    else sw.Write(f.IOName());
                    sw.Write("\t");
                    sw.Write(f.Description);
                    sw.Write("\n");
                }
            }
            catch
            {
                this._m_RPN_Stack.setStackLabel_P( 0, "Error: file save");
            }
            finally
            {
                if (sw != null) sw.Close();
                if (fs != null) fs.Close();
            }
        }
        #endregion

        #region Implemented Receivers
        //
        // Receiver adding helper
        // 
        private Receiver addReceiver(Receiver r)
        {
            Receivers.Add(r.Moniker, r);
            return r;
        }
        private void addReceivers()
        {
            addReceiver(new Receiver_AUTO_N(this));
            addReceiver(new Receiver_AUTO_F(this));
            addReceiver(new Receiver_AUTO_K(this));
            addReceiver(new Receiver_AUTO_A(this));
            addReceiver(new Receiver_AUTO_R(this)); // Running in AUTO mode

            addReceiver(new Receiver_PROG_N(this));
            addReceiver(new Receiver_PROG_F(this));
            addReceiver(new Receiver_PROG_K(this));
            addReceiver(new Receiver_PROG_A(this));
            addReceiver(new Receiver_Prog_Erase(this));

            addReceiver(new Receiver_DATA_N(this));
            addReceiver(new Receiver_DATA_F(this));
            addReceiver(new Receiver_DATA_K(this));
            addReceiver(new Receiver_DATA_A(this));
            addReceiver(new Receiver_Data_Erase(this));

            addReceiver(new Receiver_FILE_N(this));
            addReceiver(new Receiver_FILE_F(this));
            addReceiver(new Receiver_FILE_K(this));
            addReceiver(new Receiver_FILE_A(this));
            addReceiver(new Receiver_FILE_Delete(this));
            addReceiver(new Receiver_FILE_Name(this));
            addReceiver(new Receiver_FILE_Data(this));
            addReceiver(new Receiver_FILE_MkDir(this));

            addReceiver(new Receiver_Address(this));
            addReceiver(new Receiver_Address_PC(this));
            addReceiver(new Receiver_Address_MC(this));
            addReceiver(new Receiver_Address_AMX(this));
            addReceiver(new Receiver_Address_AXM(this));

            addReceiver(new Receiver_Number(this));
            addReceiver(new Receiver_Number_DATA(this));
            addReceiver(new Receiver_Number_PROG(this));
            
            addReceiver(new Receiver_Register(this));
            addReceiver(new Receiver_Register_MX(this));
            addReceiver(new Receiver_Register_XM(this));
            addReceiver(new Receiver_Register_KMX(this));
            addReceiver(new Receiver_Register_KXM(this));
            addReceiver(new Receiver_Register_ME(this));
            addReceiver(new Receiver_Register_EM(this));

            addReceiver(new Receiver_Text(this));

            // Simulator-only
            current_Receiver = addReceiver(new Receiver_Splash(this));
            addReceiver(new Receiver_OFF(this));
            addReceiver(new Receiver_FontTest(this));
        }
        #endregion
    }
}
