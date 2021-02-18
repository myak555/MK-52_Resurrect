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

        // receivers and displays
        public Dictionary<string, Display> Displays =
            new Dictionary<string, Display>();
        public Dictionary<string, Receiver> Receivers =
            new Dictionary<string, Receiver>();

        public Display current_Display = null;
        public Receiver current_Receiver = null;

        private string _stateFile = "";

        public MK52_Host( KBD_Manager kbd, LCD_Manager lcd)
        {
            _m_Hardware_KBD = kbd;
            _m_Hardware_LCD = lcd;
            addDisplays();
            addReceivers();
            _stateFile = AppDomain.CurrentDomain.BaseDirectory + "_RPN_State_New.txt";
            //setDisplay("AUTO");
            //loadState();
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

            //TODO
            _m_Extended_Memory.setCounter(8);
            foreach (Display d in Displays.Values) d.init(this);
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

        public void tick()
        {
            byte b = _m_Hardware_KBD.scan();
            while (b > 0)
            {
                b = current_Receiver.tick(b);
                if( setRequestedReceiver()) break;
            }
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
            ri.setMode(_m_RPN_Functions.getRequestedReceiverMode());
            current_Receiver = ri;
            return false;
        }

        #region Load and Save
        public void loadState()
        {
            if( !File.Exists( _stateFile))
            {
                //CalcStack.X_Label = "File not found";
                return;
            }
            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = File.Open( _stateFile, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs);
                //CallStack.Clear();
                while (!sr.EndOfStream)
                {
                    string s = sr.ReadLine().Trim();
                    if (s.Length <= 0) continue;
                    if (s.StartsWith("#")) continue;
                    if (StatusLoadHelper(s)) continue;
                    //if (IntLoadHelper(s, "dMode", ref dMode)) continue;
                    //if (CalcStack.LoadLine(s)) continue;
                    //if (Registers.LoadLine(s)) continue;
                    //if (Memory.LoadLine(s)) continue;
                    //if (_m_Program_Memory.LoadLine(s)) continue;
                    //if (CallStackLoadHelper(s)) continue;
                }
            }
            catch
            {
                //CalcStack.X_Label = "Error: file load";
            }
            finally
            {
                if(sr != null) sr.Close();
                if(fs != null) fs.Close();
            }
        }

        public void saveState()
        {
            //CalcStack.CompleteEntry();
            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = File.Open(_stateFile, FileMode.Create, FileAccess.Write, FileShare.Read);
                sw = new StreamWriter(fs);

                sw.Write("#\n");
                sw.Write("# MK-52 state file " + DateTime.Now.ToString("dd-MMM-yyyy HH:mm:ss\n"));
                sw.Write("#\n");

                string stat = current_Receiver.Moniker;
                if (stat == "OFF") stat = "AUTO"; // Upon the switch-off, always start in auto mode
                sw.Write("Status = " + stat.Substring(0, 4) + "\n");
                //if (dMode > 0) sw.Write("dMode = " + dMode.ToString() + "\n");

                //CalcStack.Save(sw);
                //Registers.Save(sw);
                //_m_Program_Memory.Save(sw);
                //Memory.Save(sw);
                //if (CallStack.Count > 0)
                //{
                //    sw.Write("#\n");
                //    sw.Write("# Call stack:");
                //    sw.Write("#\n");
                //    int[] cs = CallStack.ToArray();
                //    for (int i = 0; i < cs.Length; i++)
                //        sw.Write(cs[i].ToString("CS000\n"));
                //}
            }
            catch
            {
                //CalcStack.X_Label = "Error: file save";
            }
            finally
            {
                if (sw != null) sw.Close();
                if (fs != null) fs.Close();
            }
        }

        public void loadProgram( string name)
        {
            if (!File.Exists(name))
            {
                //CalcStack.X_Label = "File not found";
                return;
            }
            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = File.Open( name, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs);
                //_m_Program_Memory.Clear();
                while (!sr.EndOfStream)
                {
                    string s = sr.ReadLine().Trim();
                    if (s.Length <= 0) continue;
                    if (s.StartsWith("#")) continue;
                    //if (IntLoadHelper(s, "dMode", ref dMode)) continue;
                    //_m_Program_Memory.LoadLine(s);
                }
            }
            catch
            {
                //CalcStack.X_Label = "Error: file load";
            }
            finally
            {
                if (sr != null) sr.Close();
                if (fs != null) fs.Close();
            }
        }

        public void saveProgram(string filename)
        {
            //CalcStack.CompleteEntry();
            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = File.Open(filename, FileMode.Create, FileAccess.Write, FileShare.Read);
                sw = new StreamWriter(fs);

                sw.Write("#\n");
                sw.Write("# MK-52 program file " + DateTime.Now.ToString("dd-MMM-yyyy HH:mm:ss\n"));
                sw.Write("#\n");

                //if (dMode > 0) sw.Write("dMode = " + dMode.ToString() + "\n");
                //_m_Program_Memory.Save(sw);
            }
            catch
            {
                //CalcStack.X_Label = "Error: file save";
            }
            finally
            {
                if (sw != null) sw.Close();
                if (fs != null) fs.Close();
            }
        }

        private bool StatusLoadHelper(string s)
        {
            //string varName = "Status = ";
            //if (!s.StartsWith(varName)) return false;
            //string name = s.Substring(varName.Length).Trim();
            //if (name == "OFF") name = "AUTO_N"; // cold restart
            //setReceiver(name + "_N");
            return true;
        }

        private bool IntLoadHelper(string s, string varName, ref int inp)
        {
            varName += " = ";
            if (!s.StartsWith(varName)) return false;
            inp = Convert.ToInt32(s.Substring(varName.Length));
            return true;
        }

        //private bool CallStackLoadHelper(string s)
        //{
        //    if (!s.StartsWith("CS")) return false;
        //    CallStack.Push( Convert.ToInt32(s.Substring(2)));
        //    return true;
        //}
        #endregion

        public void shutdown()
        {
            //saveState();
            //setDisplay("OFF");
            _m_Hardware_LCD.clearScreen();
            _m_Hardware_LCD.forcePaint();
        }

        #region Implemented Functions
        //private void addFunctions()
        //{
            //addFunction(new Func_10x());
            //addFunction(new Func_1X());
            //addFunction(new Func_Abs());
            //addFunction(new Func_And());
            //addFunction(new Func_A_M2X());
            //addFunction(new Func_ArcCos());
            //addFunction(new Func_ArcSin());
            //addFunction(new Func_ArcTg());
            //addFunction(new Func_A_X2M());
            //addFunction(new Func_Cos());
            //addFunction(new Func_Clear_X());
            //addFunction(new Func_set_DMOD_DEG());
            //addFunction(new Func_Divide());
            //addFunction(new Func_EE());
            //addFunction(new Func_Enter());
            //addFunction(new Func_Exp());
            //addFunction(new Func_Frac());
            //addFunction(new Func_DM2D());
            //addFunction(new Func_DMS2D());
            //addFunction(new Func_in2mm());
            //addFunction(new Func_Rad2D());
            //addFunction(new Func_GOTO());
            //addFunction(new Func_GOSUB());
            //addFunction(new Func_set_DMOD_GRD());
            //addFunction(new Func_IfNotLT0());
            //addFunction(new Func_IfNotEQ0());
            //addFunction(new Func_IfNotGE0());
            //addFunction(new Func_IfNotNE0());
            //addFunction(new Func_IfNotLTY());
            //addFunction(new Func_IfNotEQY());
            //addFunction(new Func_IfNotGEY());
            //addFunction(new Func_IfNotNEY());
            //addFunction(new Func_Whole());
            //addFunction(new Func_K_M2X());
            //addFunction(new Func_K_X2M());
            //addFunction(new Func_LBT());
            //addFunction(new Func_LBX());
            //addFunction(new Func_LBY());
            //addFunction(new Func_LBZ());
            //addFunction(new Func_Lg());
            //addFunction(new Func_Ln());
            //addFunction(new Func_Log());
            //addFunction(new Func_L0());
            //addFunction(new Func_L1());
            //addFunction(new Func_L2());
            //addFunction(new Func_L3());
            //addFunction(new Func_Max());
            //addFunction(new Func_Minus());
            //addFunction(new Func_M2X());
            //addFunction(new Func_Multiply());
            //addFunction(new Func_Negate());
            //addFunction(new Func_NOP());
            //addFunction(new Func_Not());
            //addFunction(new Func_Or());
            //addFunction(new Func_PI());
            //addFunction(new Func_Plus());
            //addFunction(new Func_PrevFile());
            //addFunction(new Func_set_DMOD_RAD());
            //addFunction(new Func_Rand());
            //addFunction(new Func_Return());
            //addFunction(new Func_Rot());
            //addFunction(new Func_Seed());
            //addFunction(new Func_Sign());
            //addFunction(new Func_Sin());
            //addFunction(new Func_SQRT());
            //addFunction(new Func_Stop());
            //addFunction(new Func_Swap());
            //addFunction(new Func_Tg());
            //addFunction(new Func_D2DM());
            //addFunction(new Func_D2DMS());
            //addFunction(new Func_mm2in());
            //addFunction(new Func_D2Rad());
            //addFunction(new Func_X2());
            //addFunction(new Func_Xor());
            //addFunction(new Func_Pow());
            //addFunction(new Func_X2M());
            //addFunction(new Func_Toggle_DMOD());
        //}
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

        #region Implemented Displays
        //
        // Display adding helper
        // 
        private Display addDisplay(Display d)
        {
            Displays.Add(d.Moniker, d);
            return d;
        }
        private void addDisplays()
        {
            current_Display = addDisplay(new Display_Splash());
            addDisplay(new Display_OFF());
            addDisplay(new Display_RUN());
            addDisplay(new Display_AUTO());
            addDisplay(new Display_PROG());
            addDisplay(new Display_DATA());
            addDisplay(new Display_FILE());
            addDisplay(new Display_FontTest());
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
            current_Receiver = addReceiver(new Receiver_OFF(this));

            addReceiver(new Receiver_AUTO_N(this));
            addReceiver(new Receiver_AUTO_F(this));
            addReceiver(new Receiver_AUTO_K(this));
            addReceiver(new Receiver_AUTO_A(this));
            addReceiver(new Receiver_AUTO_R(this)); // Running in AUTO mode

            addReceiver(new Receiver_Address(this));
            addReceiver(new Receiver_Address_PC(this));
            addReceiver(new Receiver_Address_MC(this));
            addReceiver(new Receiver_Number(this));
            addReceiver(new Receiver_Register(this));
            addReceiver(new Receiver_Register_A(this));

            //addReceiver(new InputReceiver_PROG_N(this));
            //addReceiver(new InputReceiver_PROG_F(this));
            //addReceiver(new InputReceiver_PROG_K(this));
            //addReceiver(new InputReceiver_PROG_A(this));

            //addReceiver(new InputReceiver_DATA_N(this));
            //addReceiver(new InputReceiver_DATA_F(this));
            //addReceiver(new InputReceiver_DATA_K(this));
            //addReceiver(new InputReceiver_DATA_A(this));
        }
        #endregion
    }
}
