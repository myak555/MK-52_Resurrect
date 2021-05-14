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

namespace MK52Simulator
{
    public class RPN_Functions
    {
        #region Constants
        public const uint FUNC_10X = 1;
        public const uint FUNC_1X = 2;

        public const uint FUNC_A_M2X = 3;
        public const uint FUNC_A_X2M = 4;
        public const uint FUNC_ABS = 5;
        public const uint FUNC_AND = 6;
        public const uint FUNC_ARCCOS = 7;
        public const uint FUNC_ARCSIN = 8;
        public const uint FUNC_ARCTG = 9;

        public const uint FUNC_BX = 10;

        public const uint FUNC_CHAIN = 11;
        public const uint FUNC_CLEAR_X = 12;
        public const uint FUNC_COMMENT = 13;
        public const uint FUNC_COS = 14;

        public const uint FUNC_D2DM = 15;
        public const uint FUNC_D2DMS = 16;
        public const uint FUNC_DELAY = 17;
        public const uint FUNC_DIVIDE = 18;
        public const uint FUNC_DM2D = 19;
        public const uint FUNC_D2RAD = 20;
        public const uint FUNC_DMS2D = 21;
        public const uint FUNC_DMOD_DEG = 22;
        public const uint FUNC_DMOD_GRD = 23;
        public const uint FUNC_DMOD_RAD = 24;

        public const uint FUNC_EE = 25;
        public const uint FUNC_ENTER = 26;
        public const uint FUNC_EXP = 27;

        public const uint FUNC_FRAC = 28;

        public const uint FUNC_GOTO = 29;
        public const uint FUNC_GOSUB = 30;

        public const uint FUNC_IFNOTEQ0 = 31;
        public const uint FUNC_IFNOTGE0 = 32;
        public const uint FUNC_IFNOTLT0 = 33;
        public const uint FUNC_IFNOTNE0 = 34;
        public const uint FUNC_IFNOTEQY = 35;
        public const uint FUNC_IFNOTGEY = 36;
        public const uint FUNC_IFNOTLTY = 37;
        public const uint FUNC_IFNOTNEY = 38;
        public const uint FUNC_IN2MM = 39;

        public const uint FUNC_K_M2X = 40;
        public const uint FUNC_K_X2M = 41;

        public const uint FUNC_L0 = 42;
        public const uint FUNC_L1 = 43;
        public const uint FUNC_L2 = 44;
        public const uint FUNC_L3 = 45;
        public const uint FUNC_LBR = 46;
        public const uint FUNC_LBT = 47;
        public const uint FUNC_LBX = 48;
        public const uint FUNC_LBY = 49;
        public const uint FUNC_LBZ = 50;
        public const uint FUNC_LEDOFF = 51;
        public const uint FUNC_LEDON = 52;
        public const uint FUNC_LG = 53;
        public const uint FUNC_LN = 54;
        public const uint FUNC_LOAD = 55;
        public const uint FUNC_LOADALL = 56;
        public const uint FUNC_LOADDATA = 57;
        public const uint FUNC_LOG = 58;

        public const uint FUNC_M2X = 59;
        public const uint FUNC_MAX = 60;
        public const uint FUNC_MEMSET = 61;
        public const uint FUNC_MEMSWP = 62;
        public const uint FUNC_MEXTOR = 63;
        public const uint FUNC_MEXTOX = 64;
        public const uint FUNC_MINUS = 65;
        public const uint FUNC_MKDIR = 66;
        public const uint FUNC_MM2IN = 67;
        public const uint FUNC_MULTIPLY = 68;

        public const uint FUNC_NEGATE = 69;
        public const uint FUNC_NOT = 71;

        public const uint FUNC_ONEQ0 = 72;
        public const uint FUNC_ONGE0 = 73;
        public const uint FUNC_ONLT0 = 74;
        public const uint FUNC_ONNE0 = 75;
        public const uint FUNC_ONEQY = 76;
        public const uint FUNC_ONGEY = 77;
        public const uint FUNC_ONLTY = 78;
        public const uint FUNC_ONNEY = 79;
        public const uint FUNC_ONKBD = 80;
        public const uint FUNC_OR = 81;

        public const uint FUNC_PI = 82;
        public const uint FUNC_POW = 83;
        public const uint FUNC_POWYX = 84;
        public const uint FUNC_PLUS = 85;

        public const uint FUNC_RAD2D = 86;
        public const uint FUNC_RAND = 87;
        public const uint FUNC_REMOVE = 88;
        public const uint FUNC_RETURN = 89;
        public const uint FUNC_RTOMEX = 90;
        public const uint FUNC_ROT = 91;

        public const uint FUNC_SAVE = 92;
        public const uint FUNC_SAVEALL = 93;
        public const uint FUNC_SAVEDATA = 94;
        public const uint FUNC_SEED = 95;
        public const uint FUNC_SIGN = 96;
        public const uint FUNC_SIN = 97;
        public const uint FUNC_SQRT = 98;
        public const uint FUNC_STOP = 99;
        public const uint FUNC_SWAP = 100;

        public const uint FUNC_TG = 101;

        public const uint FUNC_UPDATE = 102;

        public const uint FUNC_WHOLE = 103;

        public const uint FUNC_X2 = 104;
        public const uint FUNC_X2M = 105;
        public const uint FUNC_XOR = 106;
        public const uint FUNC_XTOMEX = 107;
        
        public const uint MK52_NFUNCTIONS = 128;
        public const int PROGRAM_LINE_LENGTH = 128;
        #endregion

        private MK52_Host _parent = null;
        private SD_Manager _sd = null;
        private List<RPN_Function> _functions = new List<RPN_Function>();
        private UniversalValue _tmpuv = new UniversalValue(); // temporary value for number conversion
        private string _receiverRequested = "None";
        private string _receiverReturnRequested = "None";

        // random number remembered (emulator-only)
        public Random myRNG = new Random();

        //
        // For C++ emulation
        //
        private string _text = ""; // temporary output buffer
        private string[] _lines = new string[ LCD_Manager.SCREEN_ROWS];

        public bool _atStop = false;
        public RPN_Stack rpnStack = null;
        public Register_Memory regMem = null;
        public Program_Memory progMem = null;
        public Extended_Memory extMem = null;

        public void init( MK52_Host components)
        {
            _parent = components;
            rpnStack = components._m_RPN_Stack;
            regMem = components._m_Register_Memory;
            progMem = components._m_Program_Memory;
            extMem = components._m_Extended_Memory;
            _sd = components._m_Hardware_SD;
            for( int i=0; i<_lines.Length; i++) _lines[i] = "";

            // first check for empty program line
            _appendFunction(new Func_Empty());

            // #define FUNC_10X                1
            _appendFunction(new Func_10x());
            // #define FUNC_1X                 2
            _appendFunction(new Func_1X());

            // #define FUNC_A_M2X              3
            _appendFunction(new Func_A_M2X());
            // #define FUNC_A_X2M              4
            _appendFunction(new Func_A_X2M());
            // #define FUNC_ABS                5
            _appendFunction(new Func_Abs());
            // #define FUNC_AND                6
            _appendFunction(new Func_And());
            // #define FUNC_ARCCOS             7
            _appendFunction(new Func_ArcCos());
            // #define FUNC_ARCSIN             8
            _appendFunction(new Func_ArcSin());
            // #define FUNC_ARCTG              9
            _appendFunction(new Func_ArcTg());

            // #define FUNC_BX                 10
            _appendFunction(new Func_Bx());

            // #define FUNC_CHAIN              11
            _appendFunction(new Func_Chain());
            // #define FUNC_CLEAR_X            12
            _appendFunction(new Func_Clear_X());
            // #define FUNC_COMMENT            13
            _appendFunction(new Func_Comment());
            // #define FUNC_COS                14
            _appendFunction(new Func_Cos());

            // #define FUNC_D2DM               15
            _appendFunction(new Func_D2DM());
            // #define FUNC_D2DMS              16
            _appendFunction(new Func_D2DMS());
            // #define FUNC_DELAY              17
            _appendFunction(new Func_Delay());
            // #define FUNC_DIVIDE             18
            _appendFunction(new Func_Divide());
            // #define FUNC_DM2D               19
            _appendFunction(new Func_DM2D());
            // #define FUNC_D2RAD              20
            _appendFunction(new Func_D2Rad());
            // #define FUNC_DMS2D              21
            _appendFunction(new Func_DMS2D());
            // #define FUNC_DMOD_DEG           22
            _appendFunction(new Func_DMOD_DEG());
            // #define FUNC_DMOD_GRD           23
            _appendFunction(new Func_DMOD_GRD());
            // #define FUNC_DMOD_RAD           24
            _appendFunction(new Func_DMOD_RAD());

            // #define FUNC_EE                 25
            _appendFunction(new Func_EE());
            // #define FUNC_ENTER              26
            _appendFunction(new Func_Enter());
            // #define FUNC_EXP                27
            _appendFunction(new Func_Exp());

            // #define FUNC_FRAC               28
            _appendFunction(new Func_Frac());

            // #define FUNC_GOTO               29
            _appendFunction(new Func_GOTO());
            // #define FUNC_GOSUB              30
            _appendFunction(new Func_GOSUB());

            // #define FUNC_IFNOTEQ0           31
            _appendFunction(new Func_IfNotEQ0());
            // #define FUNC_IFNOTGE0           32
            _appendFunction(new Func_IfNotGE0());
            // #define FUNC_IFNOTLT0           33
            _appendFunction(new Func_IfNotLT0());
            // #define FUNC_IFNOTNE0           34
            _appendFunction(new Func_IfNotNE0());
            // #define FUNC_IFNOTEQY           35
            _appendFunction(new Func_IfNotEQY());
            // #define FUNC_IFNOTGEY           36
            _appendFunction(new Func_IfNotGEY());
            // #define FUNC_IFNOTLTY           37
            _appendFunction(new Func_IfNotLTY());
            // #define FUNC_IFNOTNEY           38
            _appendFunction(new Func_IfNotNEY());
            // #define FUNC_IN2MM              39
            _appendFunction(new Func_in2mm());

            // #define FUNC_K_M2X              40
            _appendFunction(new Func_K_M2X());
            // #define FUNC_K_X2M              41
            _appendFunction(new Func_K_X2M());

            // #define FUNC_L0                 42
            _appendFunction(new Func_L0());
            // #define FUNC_L1                 43
            _appendFunction(new Func_L1());
            // #define FUNC_L2                 44
            _appendFunction(new Func_L2());
            // #define FUNC_L3                 45
            _appendFunction(new Func_L3());
            // #define FUNC_LBR                46
            _appendFunction(new Func_LBR());
            // #define FUNC_LBT                47
            _appendFunction(new Func_LBT());
            // #define FUNC_LBX                48
            _appendFunction(new Func_LBX());
            // #define FUNC_LBY                49
            _appendFunction(new Func_LBY());
            // #define FUNC_LBZ                50
            _appendFunction(new Func_LBZ());
            // #define FUNC_LEDOFF             51
            _appendFunction(new Func_LEDOff());
            // #define FUNC_LEDON              52
            _appendFunction(new Func_LEDOn());
            // #define FUNC_LG                 53
            _appendFunction(new Func_Lg());
            // #define FUNC_LN                 54
            _appendFunction(new Func_Ln());
            // #define FUNC_LOAD               55
            _appendFunction(new Func_Load());
            // #define FUNC_LOADALL            56
            _appendFunction(new Func_LoadAll());
            // #define FUNC_LOADDATA           57
            _appendFunction(new Func_LoadData());
            // #define FUNC_LOG                58
            _appendFunction(new Func_Log());

            // #define FUNC_M2X                59
            _appendFunction(new Func_M2X());
            // #define FUNC_MAX                60
            _appendFunction(new Func_Max());
            // #define FUNC_MEMSET             61
            _appendFunction(new Func_MemSet());
            // #define FUNC_MEMSWP             62
            _appendFunction(new Func_MemSwp());
            // #define FUNC_MEXTOR             63
            _appendFunction(new Func_MexToR());
            // #define FUNC_MEXTOX             64
            _appendFunction(new Func_MexToX());
            // #define FUNC_MINUS              65
            _appendFunction(new Func_Minus());
            // #define FUNC_MKDIR              66
            _appendFunction(new Func_MkDir());
            // #define FUNC_MM2IN              67
            _appendFunction(new Func_mm2in());
            // #define FUNC_MULTIPLY           68
            _appendFunction(new Func_Multiply());

            // #define FUNC_NEGATE             69
            _appendFunction(new Func_Negate());
            // #define FUNC_NOT                71
            _appendFunction(new Func_Not());

            // #define FUNC_ONEQ0              72
            // #define FUNC_ONGE0              73
            // #define FUNC_ONLT0              74
            // #define FUNC_ONNE0              75
            // #define FUNC_ONEQY              76
            // #define FUNC_ONGEY              77
            // #define FUNC_ONLTY              78
            // #define FUNC_ONNEY              79
            // #define FUNC_ONKBD              80
            // #define FUNC_OR                 81
            _appendFunction(new Func_Or());

            // #define FUNC_PI                 82
            _appendFunction(new Func_PI());
            // #define FUNC_POW                83
            _appendFunction(new Func_Pow());
            // #define FUNC_POWYX              84
            _appendFunction(new Func_PowYX());
            // #define FUNC_PLUS               85
            _appendFunction(new Func_Plus());

            // #define FUNC_RAD2D              86
            _appendFunction(new Func_Rad2D());
            // #define FUNC_RAND               87
            _appendFunction(new Func_Rand());
            // #define FUNC_REMOVE             88
            _appendFunction(new Func_Remove());
            // #define FUNC_RETURN             89
            _appendFunction(new Func_Return());
            // #define FUNC_RTOMEX             90
            _appendFunction(new Func_RToMex());
            // #define FUNC_ROT                91
            _appendFunction(new Func_Rot());

            // #define FUNC_SAVE               92
            _appendFunction(new Func_Save());
            // #define FUNC_SAVEALL            93
            _appendFunction(new Func_SaveAll());
            // #define FUNC_SAVEDATA           94
            _appendFunction(new Func_SaveData());
            // #define FUNC_SEED               95
            _appendFunction(new Func_Seed());
            // #define FUNC_SIGN               96
            _appendFunction(new Func_Sign());
            // #define FUNC_SIN                97
            _appendFunction(new Func_Sin());
            // #define FUNC_SQRT               98
            _appendFunction(new Func_SQRT());
            // #define FUNC_STOP               99
            _appendFunction(new Func_Stop());
            // #define FUNC_SWAP               100
            _appendFunction(new Func_Swap());

            // #define FUNC_TG                 101
            _appendFunction(new Func_Tg());

            // #define FUNC_UPDATE             102
            _appendFunction(new Func_Update());

            // #define FUNC_WHOLE              103
            _appendFunction(new Func_Whole());

            // #define FUNC_X2                 104
            _appendFunction(new Func_X2());
            // #define FUNC_X2M                105
            _appendFunction(new Func_X2M());
            // #define FUNC_XOR                106
            _appendFunction(new Func_Xor());
            // #define FUNC_XTOMEX             107
            _appendFunction(new Func_XToMex());

            // if the name is not found, it must be a number and should be placed to register X
            _appendFunction( new Func_Number());
        }

        #region IO Buffer
        public string getOutputBuffer()
        {
            return _text;
        }

        public string setOutputBuffer(string text)
        {
            _text = text;
            return _text;
        }

        public string appendOutputBuffer(string text)
        {
            _text += text;
            return _text;
        }

        public string setOutputBuffer_P(string text)
        {
            _text = text;
            return _text;
        }

        public string appendOutputBuffer_P(string text)
        {
            _text += text;
            return _text;
        }

        public string getOutputLine(int n)
        {
            return _lines[n];
        }

        public string[] getOutputLines()
        {
            return _lines;
        }
        #endregion

        #region Execute
        public RPN_Function getFunctionByID(uint id)
        {
            // TODO
            if( id<0) return null;
            for(int i=0; i<_functions.Count; i++)
            {
                RPN_Function pf = _functions[i];
                if( !pf.checkID( id)) continue;
                return pf;
            }
            return null;
        }

        public RPN_Function getFunctionByName(string command)
        {
            for (int i = 0; i < _functions.Count; i++)
            {
                RPN_Function pf = _functions[i];
                if (!pf.checkName(command)) continue;
                return pf;
            }
            return null;
        }

        public RPN_Function getFunctionByIOName(string command)
        {
            if (command.Length <= 0) return null;
            for (int i = 0; i < _functions.Count; i++)
            {
                RPN_Function pf = _functions[i];
                if( !UniversalValue._startsWith_P( command, pf.IOName())) continue;
                return pf;
            }
            return null;
        }

        public void execute(uint id)
        {
            execute(id, "");
        }

        public void execute( uint id, string command)
        {
            RPN_Function pf = getFunctionByID(id);
            if (pf == null) return;
            pf.execute(_parent, command);
        }

        public void execute( string command)
        {
            for (int i = 0; i < _functions.Count; i++)
            {
                RPN_Function pf = _functions[i];
                if (!pf.checkName(command)) continue;
                int operand = pf.Name().Length;
                pf.execute( _parent, command.Substring(operand));
                pf.advancePC( _parent);
                return;
            }
            rpnStack.setLabel(0, command);
            progMem.incrementCounter();
        }
        
        /// <summary>
        /// Resets the stop for counter
        /// </summary>
        /// <returns>True if the condition cleared</returns>
        public bool clearStopCondition()
        {
            if (!_atStop) return false;
            if (progMem.isAtStop()) progMem.incrementCounter();
            _atStop = false;
            return true;
        }

        /// <summary>
        /// Some original MK-52 programs used PP for data entry;
        /// must simulate the same, although not obvious for debugging.
        /// the commented line is to revert to other logic
        /// </summary>
        public void executeStep()
        {
            // if( clearStopCondition()) return; // just move to the next line
            //clearStopCondition();
            //executeRun();
            //if (_atStop && progMem.isAtStop()) 
            //    rpnStack.setStackLabel_P(0, "STOP Reached");
            _atStop = false;
            if (progMem.isAtStop())
            {
                rpnStack.setLabel_P(0, "STOP Reached");
                progMem.incrementCounter();
                return;
            }
            executeRun();
        }

        public void executeRun()
        {
            string programLine = progMem.getCurrentLine();
            execute( programLine);
            if (progMem.isAtEnd()) _atStop = true;
        }
        #endregion

        #region File Operations
        public bool loadState()
        {
            _receiverRequested = "AUTO_N"; // this is in case file reading fails
            _receiverReturnRequested = "None";
            if (_sd.openFile_P(_sd.StatusFileName, false)) return true;
            bool result = _read(true, true, true);
            _sd.closeFile();
            return result;
        }

        public bool saveState( string returnReceiver)
        {
            if (_sd.openFile_P(_sd.StatusFileName, true)) return true;
            bool result = _writeStack(returnReceiver);
            if (!result) result = _writeRegisters();
            if (!result) result = _writeProgram();
            if (!result) result = _writeData();
            if (!result) result = _writeReturnStack();
            _sd.closeFile();
            return result;
        }

        public bool loadProgram()
        {
            return loadProgram("");
        }
 
        public bool loadProgram( string name)
        {
            if( _sd.openFile(name, false)) return true;
            progMem.clear();
            bool result = _read( false, true, false);
            _sd.closeFile();
            return result;
        }

        public bool saveProgram()
        {
            return saveProgram("");
        }
        
        public bool saveProgram( string name)
        {
            name = name.Replace('/', '\\');
            if (_sd.openFile(name, true)) return true;
            bool result = _writeProgram();
            _sd.closeFile();
            _sd.readFolderItems();
            return result;
        }

        public bool loadData()
        {
            return loadData("");
        }
 
        public bool loadData( string name)
        {
            if (_sd.openFile(name, false)) return true;
            extMem.clear();
            bool result = _read(false, false, true);
            _sd.closeFile();
            return result;
        }

        public bool saveData()
        {
            return saveData("");
        }
        
        public bool saveData( string name)
        {
            name = name.Replace('/', '\\');
            if (_sd.openFile(name, true)) return true;
            bool result = _writeData();
            _sd.closeFile();
            _sd.readFolderItems();
            return result;
        }

        public bool loadAll()
        {
            return loadAll("");
        }

        public bool loadAll(string name)
        {
            if (_sd.openFile(name, false)) return true;
            rpnStack.clear();
            regMem.clear();
            progMem.clear();
            extMem.clear();
            bool result = _read(true, true, true);
            _sd.closeFile();
            return result;
        }

        public bool saveAll()
        {
            return saveAll("");
        }

        public bool saveAll(string name)
        {
            if (_sd.openFile_P(_sd.StatusFileName, true)) return true;
            bool result = _writeStack("AUTO_N");
            if (!result) result = _writeRegisters();
            if (!result) result = _writeProgram();
            if (!result) result = _writeData();
            _sd.closeFile();
            _sd.readFolderItems();
            return result;
        }

        public void stepIn()
        {
            string filename = _sd.getItemFromListing();
            if( !_sd.stepIn( filename)) return;
            if( UniversalValue._endsWith_P( filename, ".DAT"))
                loadData( filename);
            else
                loadProgram( filename);
        }

        public string formFileName(string name)
        {
            return _sd.makeEntityName( name);
        }
        
        public bool fileExists(string name)
        {
            return _sd.checkEntityExists(name);
        }
        #endregion

        #region Next Receiver Setting
        public byte requestNextReceiver(string name)
        {
            return requestNextReceiver(name, "None");
        }

        public byte requestNextReceiver(string name, string exitTo)
        {
            _receiverRequested = name;
            _receiverReturnRequested = exitTo;
            return (byte)0;
        }

        public string getRequestedReceiver()
        {
            string tmp = _receiverRequested;
            _receiverRequested = "None";
            return tmp;
        }

        public string getRequestedReturnReceiver()
        {
            string tmp = _receiverReturnRequested;
            _receiverReturnRequested = "None";
            return tmp;
        }

        public void appendProgramLine_P( uint id)
        {
            progMem.updateLine_P( getFunctionByID(id).Name());
        }
        #endregion

        #region Private Functions
        private void _appendFunction( RPN_Function f)
        {
            if (_functions.Count >= MK52_NFUNCTIONS) return;
            _functions.Add( f);
        }

        private bool _writeStack(string returnReceiver)
        {
            if( _sd.println_P("#")) return true;
            if( _sd.println_P("# MK-52 stack")) return true;
            if( _sd.println_P("#")) return true;
            if (_sd.print("DISPL=")) return true;
            if (_sd.println( returnReceiver)) return true;
            if (_sd.print("DMODE=")) return true;
            if(_sd.println(rpnStack.getDModeName())) return true;
            if (_sd.print("EMODE=")) return true;
            if (_sd.println(progMem.getEModeName())) return true;
            if (_sd.print("Bx=")) return true;
            if (_sd.println(rpnStack.Bx.toString())) return true;
            if (_sd.print("X=")) return true;
            if (_sd.println(rpnStack.X.toString())) return true;
            if (_sd.print("Y=")) return true;
            if (_sd.println(rpnStack.Y.toString())) return true;
            if (_sd.print("Z=")) return true;
            if (_sd.println(rpnStack.Z.toString())) return true;
            if (_sd.print("T=")) return true;
            if (_sd.println(rpnStack.T.toString())) return true;
            if (!rpnStack.customLabels()) return false;
            if (_sd.print("LX=")) return true;
            if (_sd.println(rpnStack.X_Label)) return true;
            if (_sd.print("LY=")) return true;
            if (_sd.println(rpnStack.Y_Label)) return true;
            if (_sd.print("LZ=")) return true;
            if (_sd.println(rpnStack.Z_Label)) return true;
            if (_sd.print("LT=")) return true;
            if (_sd.println(rpnStack.T_Label)) return true;
            return false;
        }

        private bool _writeRegisters()
        {
            if( _sd.println_P("#")) return true;
            if( _sd.println_P("# MK-52 registers")) return true;
            if( _sd.println_P("#")) return true;
            for( byte i=0; i<Register_Memory.REGISTER_MEMORY_NVALS; i++)
            {
                UniversalValue uv = regMem._registerAddress(i);
                if( uv.isEmpty()) continue;
                if (_sd.print("R")) return true;
                if (_sd.print(i.ToString("00"))) return true;
                if (_sd.print("=")) return true;
                if (_sd.println(uv.toString())) return true;
            }
            return false;
        }

        private bool _writeProgram()
        {
            if( _sd.println_P("#")) return true;
            if( _sd.println_P("# MK-52 program")) return true;
            if( _sd.println_P("#")) return true;
            uint ctr = progMem.getCounter();
            if (_sd.print("PC=")) return true;
            if (_sd.println(ctr.ToString("0000"))) return true;
            progMem.setCounter(0);
            while (!progMem.isAtEnd())
            {
                string ptr = progMem.getCurrentLine();
                if (ptr.Length == 0)
                { // empty lines ignored
                    progMem.incrementCounter();
                    continue;
                }
                if (_sd.print_P("P") ||
                    _sd.print(progMem.getCounter().ToString("0000")) ||
                    _sd.print_P(": ") ||
                    _sd.println(ptr))
                {
                    progMem.setCounter(ctr);
                    return true;
                }
                progMem.incrementCounter();
            }
            progMem.setCounter(ctr);
            return false;
        }

        private bool _writeData()
        {
            if( _sd.println_P("#")) return true;
            if( _sd.println_P("# MK-52 data")) return true;
            if( _sd.println_P("#")) return true;
            if (_sd.print_P("MC=")) return true;
            if (_sd.println_P(extMem.getCounter().ToString("0000"))) return true;
            for( uint i=0; i<Extended_Memory.EXTENDED_MEMORY_NVALS; i++){
                UniversalValue ptr = extMem.getLine( i);
                if( ptr.isEmpty()) continue;
                if (_sd.print_P("M")) return true;
                if (_sd.print_P(i.ToString("0000"))) return true;
                if (_sd.print_P(": ")) return true;
                if (_sd.println_P(ptr.toString())) return true;
            }
            return false;
        }

        private bool _writeReturnStack()
        {
            uint n = progMem.getCallStackPtr();
            if (n == 0) return false;
            if (_sd.println_P("#")) return true;
            if (_sd.println_P("# MK-52 return stack")) return true;
            if (_sd.println_P("#")) return true;
            if (_sd.print_P("RS=")) return true;
            if (_sd.println_P(n.ToString("0000"))) return true;
            for (uint i = 0; i < n; i++)
            {
                if (_sd.println(progMem.getCallStackValues(i))) return true;
            }
            return false;
        }

        private bool _read(bool readStack, bool readProg, bool readMem)
        {
            uint pmemctr = progMem.getCounter();
            uint ememctr = extMem.getCounter();
            //uint callStackDeclared = 0; presented in dump file, but not used
            uint callStackActual = 0;
            byte regAddress = 0;
            while (true)
            {
                bool result = _sd.readln( _text, PROGRAM_LINE_LENGTH);
                _text = _sd.__text;
                if (result && _text.Length == 0) break;
                if (_text.Length == 0) continue;
                if( _text[0] == '#') continue;
                if( readProg){
                    if( UniversalValue._startsWith_P( _text, "PC=")){
                        progMem.setCounter(_text.Substring(3));
                        pmemctr = progMem.getCounter();
                        continue;
                    }
                    if( UniversalValue._isProgramAddress(_text)){
                        string[] ptr = UniversalValue._selectAddress(_text);
                        if (ptr[0].Length < 4 && ptr[1].Length < 1) continue; // string too short or incorrectly formed
                        progMem.setCounter( ptr[0]);
                        progMem.replaceLine( ptr[1]); // TODO: name conversion
                        continue;
                    }
                    if (UniversalValue._isReturnStackAddress(_text))
                    {
                        string[] ptr = UniversalValue._selectAddress(_text);
                        if (ptr[0].Length < 4 && ptr[1].Length < 1) continue; // string too short or incorrectly formed
                        progMem.setCallStackValues(callStackActual++, ptr[0], ptr[1]);
                        continue;
                    }
                }
                if( readMem){
                    if( UniversalValue._startsWith_P( _text, "MC=")){
                        extMem.setCounter(_text.Substring(3));
                        ememctr = extMem.getCounter();
                        continue;
                    }
                    if( UniversalValue._isMemoryAddress(_text)){
                        string[] ptr = UniversalValue._selectAddress(_text);
                        if (ptr[0].Length < 4 && ptr[1].Length < 1) continue; // string too short or incorrectly formed
                        extMem.setCounter( ptr[0]);
                        extMem.fromString( ptr[1]);
                        continue;
                    }
                }
                if( readStack){
                    if( UniversalValue._startsWith_P( _text, "DISPL=")){
                        _receiverRequested = _text.Substring(6);
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "X=")){
                        rpnStack.X.fromString(_text.Substring(2));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "Y=")){
                        rpnStack.Y.fromString(_text.Substring(2));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "Z=")){
                        rpnStack.Z.fromString(_text.Substring(2));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "T=")){
                        rpnStack.T.fromString(_text.Substring(2));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "Bx=")){
                        rpnStack.Bx.fromString(_text.Substring(3));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "DMODE=DEG")){
                        rpnStack.setDMode(0);
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "DMODE=RAD")){
                        rpnStack.setDMode(1);
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "DMODE=GRD")){
                        rpnStack.setDMode(2);
                        continue;
                    }
                    if (UniversalValue._startsWith_P(_text, "EMODE=OVR"))
                    {
                        progMem.setEMode(0);
                        continue;
                    }
                    if (UniversalValue._startsWith_P(_text, "EMODE=INS"))
                    {
                        progMem.setEMode(1);
                        continue;
                    }
                    if (UniversalValue._startsWith_P(_text, "DMODE=SHF"))
                    {
                        progMem.setEMode(2);
                        continue;
                    }
                    if (UniversalValue._startsWith_P(_text, "LX=")) {
                        rpnStack.setLabel(0, _text.Substring(3));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "LY=")){
                        rpnStack.setLabel(1, _text.Substring(3));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "LZ=")){
                        rpnStack.setLabel(2, _text.Substring(3));
                        continue;
                    }
                    if( UniversalValue._startsWith_P( _text, "LT=")){
                        rpnStack.setLabel(3, _text.Substring(3));
                        continue;
                    }
                    regAddress = UniversalValue._isRegisterAddress(_text);
                    if( regAddress < Register_Memory.REGISTER_MEMORY_NVALS)
                    {
                        UniversalValue uv  = regMem._registerAddress(regAddress);
                        uv.fromString(_text.Substring(4));
                        continue;
                    }
                }
            }// while
            progMem.setCounter( pmemctr);
            extMem.setCounter( ememctr);
            return false;
        }

        #endregion
    }
}
