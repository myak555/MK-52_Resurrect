using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Functions;
using MK52Simulator.Receivers;

namespace MK52Simulator
{
    //
    // Implements the state engine
    //
    public class MK52_Host
    {
        // hardware emulators
        public KBD_Manager KBD = null;
        public LCD_Manager LCD = null;
        public SD_Manager SD = new SD_Manager();

        // calculator memory
        public RPN_Stack CalcStack = null;
        public RPN_Registers Registers = null;
        public RPN_Program Program = null;
        public RPN_Memory Memory = null;
        public Stack<int> CallStack = new Stack<int>();

        // degrees/radian/gradian mode
        public const int dMode_Degrees = 0;
        public const int dMode_Radian = 1;
        public const int dMode_Gradian = 2;
        public int dMode = dMode_Degrees;

        // random number remembered
        public Random myRNG = new Random();

        // functions, receivers and displays
        public Dictionary<string, RPN_Function> Functions =
            new Dictionary<string, RPN_Function>();
        public Dictionary<string, Display> Displays =
            new Dictionary<string, Display>();
        public Dictionary<string, RPN_InputReceiver> Receivers =
            new Dictionary<string, RPN_InputReceiver>();

        public Display current_Display = null;
        public RPN_InputReceiver current_Receiver = null;

        private string _stateFile = "";

        public MK52_Host( KBD_Manager kbd, LCD_Manager lcd)
        {
            KBD = kbd;
            LCD = lcd;
            
            CalcStack = new RPN_Stack(this);
            Registers = new RPN_Registers(this);
            Program = new RPN_Program(this);
            Memory = new RPN_Memory(this);
            addFunctions();
            addDisplays();
            addReceivers();
            _stateFile = AppDomain.CurrentDomain.BaseDirectory + "_RPN_State_New.txt";
            //setDisplay("AUTO");
            //loadState();
        }

        public void init()
        {
            LCD.init();
            SD.init();
        }

        public void SwapDegreeMode()
        {
            dMode++;
            if (dMode > dMode_Gradian) dMode = dMode_Degrees;
        }

        public void tick()
        {
            //if (rpb.Moniker == "Dummy" && current_Receiver.Moniker != "AUTO_R") return;
            //current_Receiver.tick(rpb);
            if (!KBD.Available()) return; 
            RPN_Button rpb = KBD.GetButton();
            string newReceiver = current_Receiver.tick( rpb);
            setReceiver(newReceiver);
            current_Display.tick();
        }

        /// <summary>
        /// Sets display
        /// </summary>
        /// <param name="name">Display moniker</param>
        /// <returns>true if display is not available</returns>
        public bool setDisplay(string name)
        {
            if (!Displays.ContainsKey(name)) return true;
            Display dis = Displays[name];
            string receiver_name = dis.activate();
            current_Display = dis;
            setReceiver(receiver_name);
            return false;
        }

        public Display getDisplay(string name)
        {
            if (!Displays.ContainsKey(name)) return null;
            return Displays[name];
        }

        /// <summary>
        /// Sets receiver
        /// </summary>
        /// <param name="name">Receiver moniker</param>
        /// <returns>true if receiver is not available</returns>
        public bool setReceiver(string name)
        {
            if (!Receivers.ContainsKey(name)) return true;
            RPN_InputReceiver ri = Receivers[name];
            ri.activate();
            current_Receiver = ri;
            return false;
        }

        public RPN_InputReceiver getReceiver(string name)
        {
            if (!Receivers.ContainsKey(name)) return null;
            return Receivers[name];
        }

        public void executeFunction(string name)
        {
            if (!Functions.ContainsKey(name)) return;
            RPN_Function f = Functions[name];
            f.execute( name);
        }

        #region Load and Save
        public void loadState()
        {
            if( !File.Exists( _stateFile))
            {
                CalcStack.X_Label = "File not found";
                return;
            }
            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = File.Open( _stateFile, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs);
                CallStack.Clear();
                while (!sr.EndOfStream)
                {
                    string s = sr.ReadLine().Trim();
                    if (s.Length <= 0) continue;
                    if (s.StartsWith("#")) continue;
                    if (StatusLoadHelper(s)) continue;
                    if (IntLoadHelper(s, "dMode", ref dMode)) continue;
                    if (CalcStack.LoadLine(s)) continue;
                    if (Registers.LoadLine(s)) continue;
                    if (Memory.LoadLine(s)) continue;
                    if (Program.LoadLine(s)) continue;
                    if (CallStackLoadHelper(s)) continue;
                }
            }
            catch
            {
                CalcStack.X_Label = "Error: file load";
            }
            finally
            {
                if(sr != null) sr.Close();
                if(fs != null) fs.Close();
            }
        }

        public void saveState()
        {
            CalcStack.CompleteEntry();
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
                if (dMode > 0) sw.Write("dMode = " + dMode.ToString() + "\n");

                CalcStack.Save(sw);
                Registers.Save(sw);
                Program.Save(sw);
                Memory.Save(sw);
                if (CallStack.Count > 0)
                {
                    sw.Write("#\n");
                    sw.Write("# Call stack:");
                    sw.Write("#\n");
                    int[] cs = CallStack.ToArray();
                    for (int i = 0; i < cs.Length; i++)
                        sw.Write(cs[i].ToString("CS000\n"));
                }
            }
            catch
            {
                CalcStack.X_Label = "Error: file save";
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
                CalcStack.X_Label = "File not found";
                return;
            }
            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = File.Open( name, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs);
                Program.Clear();
                while (!sr.EndOfStream)
                {
                    string s = sr.ReadLine().Trim();
                    if (s.Length <= 0) continue;
                    if (s.StartsWith("#")) continue;
                    if (IntLoadHelper(s, "dMode", ref dMode)) continue;
                    Program.LoadLine(s);
                }
            }
            catch
            {
                CalcStack.X_Label = "Error: file load";
            }
            finally
            {
                if (sr != null) sr.Close();
                if (fs != null) fs.Close();
            }
        }

        public void saveProgram(string filename)
        {
            CalcStack.CompleteEntry();
            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = File.Open(filename, FileMode.Create, FileAccess.Write, FileShare.Read);
                sw = new StreamWriter(fs);

                sw.Write("#\n");
                sw.Write("# MK-52 program file " + DateTime.Now.ToString("dd-MMM-yyyy HH:mm:ss\n"));
                sw.Write("#\n");

                if (dMode > 0) sw.Write("dMode = " + dMode.ToString() + "\n");
                Program.Save(sw);
            }
            catch
            {
                CalcStack.X_Label = "Error: file save";
            }
            finally
            {
                if (sw != null) sw.Close();
                if (fs != null) fs.Close();
            }
        }

        private bool StatusLoadHelper(string s)
        {
            string varName = "Status = ";
            if (!s.StartsWith(varName)) return false;
            string name = s.Substring(varName.Length).Trim();
            if (name == "OFF") name = "AUTO_N"; // cold restart
            setReceiver(name + "_N");
            return true;
        }

        private bool IntLoadHelper(string s, string varName, ref int inp)
        {
            varName += " = ";
            if (!s.StartsWith(varName)) return false;
            inp = Convert.ToInt32(s.Substring(varName.Length));
            return true;
        }

        private bool CallStackLoadHelper(string s)
        {
            if (!s.StartsWith("CS")) return false;
            CallStack.Push( Convert.ToInt32(s.Substring(2)));
            return true;
        }
        #endregion

        public void Shutdown()
        {
            saveState();
            setDisplay("OFF");
            LCD.clearScreen();
            LCD.Refresh();
        }

        #region Implemented Functions
        //
        // Function adding helper
        // 
        private void addFunction(RPN_Function f)
        {
            Functions.Add(f.Keyword, f);
        }
        private void addFunctions()
        {
            addFunction(new RPN_Function_Empty(this)); // These three must be checked first
            addFunction(new RPN_Function_Comment(this));
            addFunction(new RPN_Function_Number(this));

            addFunction(new RPN_Function_10x(this));
            addFunction(new RPN_Function_1x(this));
            addFunction(new RPN_Function_ABS(this));
            addFunction(new RPN_Function_AND(this));
            addFunction(new RPN_Function_AMtoX(this));
            addFunction(new RPN_Function_arcCOS(this));
            addFunction(new RPN_Function_arcSIN(this));
            addFunction(new RPN_Function_arcTG(this));
            addFunction(new RPN_Function_AXtoM(this));
            addFunction(new RPN_Function_COS(this));
            addFunction(new RPN_Function_Cx(this));
            addFunction(new RPN_Function_DEG(this));
            addFunction(new RPN_Function_Divide(this));
            addFunction(new RPN_Function_e(this));
            addFunction(new RPN_Function_Enter(this));
            addFunction(new RPN_Function_EXP(this));
            addFunction(new RPN_Function_FRAC(this));
            addFunction(new RPN_Function_FromDM(this));
            addFunction(new RPN_Function_FromDMS(this));
            addFunction(new RPN_Function_FromIN(this));
            addFunction(new RPN_Function_FromRAD(this));
            addFunction(new RPN_Function_GOTO(this));
            addFunction(new RPN_Function_GOSUB(this));
            addFunction(new RPN_Function_GRAD(this));
            addFunction(new RPN_Function_IF0(this));
            addFunction(new RPN_Function_IF0a(this));
            addFunction(new RPN_Function_IF1(this));
            addFunction(new RPN_Function_IF1a(this));
            addFunction(new RPN_Function_IF2(this));
            addFunction(new RPN_Function_IF2a(this));
            addFunction(new RPN_Function_IF3(this));
            addFunction(new RPN_Function_IF3a(this));
            addFunction(new RPN_Function_INT(this));
            addFunction(new RPN_Function_KMtoX(this));
            addFunction(new RPN_Function_KXtoM(this));
            addFunction(new RPN_Function_LblT(this));
            addFunction(new RPN_Function_LblX(this));
            addFunction(new RPN_Function_LblY(this));
            addFunction(new RPN_Function_LblZ(this));
            addFunction(new RPN_Function_LG(this));
            addFunction(new RPN_Function_LN(this));
            addFunction(new RPN_Function_LOG(this));
            addFunction(new RPN_Function_LOOP0(this));
            addFunction(new RPN_Function_LOOP1(this));
            addFunction(new RPN_Function_LOOP2(this));
            addFunction(new RPN_Function_LOOP3(this));
            addFunction(new RPN_Function_MAX(this));
            addFunction(new RPN_Function_Minus(this));
            addFunction(new RPN_Function_MtoX(this));
            addFunction(new RPN_Function_Mult(this));
            addFunction(new RPN_Function_Neg(this));
            addFunction(new RPN_Function_NOP(this));
            addFunction(new RPN_Function_NOT(this));
            addFunction(new RPN_Function_OR(this));
            addFunction(new RPN_Function_pi(this));
            addFunction(new RPN_Function_Plus(this));
            addFunction(new RPN_Function_Prev(this));
            addFunction(new RPN_Function_RAD(this));
            addFunction(new RPN_Function_RAND(this));
            addFunction(new RPN_Function_RETURN(this));
            addFunction(new RPN_Function_Rotate(this));
            addFunction(new RPN_Function_SEED(this));
            addFunction(new RPN_Function_SIGN(this));
            addFunction(new RPN_Function_SIN(this));
            addFunction(new RPN_Function_SQRT(this));
            addFunction(new RPN_Function_STOP(this));
            addFunction(new RPN_Function_Swap(this));
            addFunction(new RPN_Function_TG(this));
            addFunction(new RPN_Function_ToDM(this));
            addFunction(new RPN_Function_ToDMS(this));
            addFunction(new RPN_Function_ToIN(this));
            addFunction(new RPN_Function_ToRAD(this));
            addFunction(new RPN_Function_x2(this));
            addFunction(new RPN_Function_XOR(this));
            addFunction(new RPN_Function_XpY(this));
            addFunction(new RPN_Function_XtoM(this));
        }
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
                foreach (RPN_Function f in Functions.Values)
                {
                    sw.Write(f.Keyword.PadRight(20));
                    sw.Write("\t");
                    sw.Write(f.Description);
                    sw.Write("\n");
                }
            }
            catch
            {
                CalcStack.X_Label = "Error: file save";
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
            addDisplay(new Display_Splash(this));
            addDisplay(new Display_OFF(this));
            addDisplay(new Display_RUN(this));
            addDisplay(new Display_AUTO(this));
            addDisplay(new Display_PROG(this));
            addDisplay(new Display_DATA(this));
            addDisplay(new Display_FILE(this));
        }
        #endregion

        #region Implemented Receivers
        //
        // Receiver adding helper
        // 
        private RPN_InputReceiver addReceiver(RPN_InputReceiver r)
        {
            Receivers.Add(r.Moniker, r);
            return r;
        }
        private void addReceivers()
        {
            current_Receiver = addReceiver(new InputReceiver_AUTO_N(this));
            addReceiver(new InputReceiver_AUTO_F(this));
            addReceiver(new InputReceiver_AUTO_K(this));
            addReceiver(new InputReceiver_AUTO_A(this));
            addReceiver(new InputReceiver_RUN(this)); // Running in AUTO mode

            addReceiver(new InputReceiver_PROG_N(this));
            addReceiver(new InputReceiver_PROG_F(this));
            addReceiver(new InputReceiver_PROG_K(this));
            addReceiver(new InputReceiver_PROG_A(this));

            addReceiver(new InputReceiver_DATA_N(this));
            addReceiver(new InputReceiver_DATA_F(this));
            addReceiver(new InputReceiver_DATA_K(this));
            addReceiver(new InputReceiver_DATA_A(this));

            addReceiver(new InputReceiver_OFF(this));
        }
        #endregion
    }
}
