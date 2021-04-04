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
        public const uint FUNC_COMMENT = 1;
        public const uint FUNC_SET_DMOD_DEG = 9;
        public const uint FUNC_SET_DMOD_RAD = 10;
        public const uint FUNC_SET_DMOD_GRD = 11;
        public const uint FUNC_NEGATE = 12;
        public const uint FUNC_ENTER = 13;
        public const uint FUNC_SWAP = 14;
        public const uint FUNC_PLUS = 15;
        public const uint FUNC_MINUS = 16;
        public const uint FUNC_MULTIPLY = 17;
        public const uint FUNC_DIVIDE = 18;
        public const uint FUNC_CLEAR_X = 19;
        public const uint FUNC_SIN = 20;
        public const uint FUNC_ARCSIN = 21;
        public const uint FUNC_COS = 22;
        public const uint FUNC_ARCCOS = 23;
        public const uint FUNC_TG = 24;
        public const uint FUNC_ARCTG = 25;
        public const uint FUNC_EXP = 26;
        public const uint FUNC_10X = 27;
        public const uint FUNC_LG = 28;
        public const uint FUNC_LN = 29;
        public const uint FUNC_POW = 30;
        public const uint FUNC_LOG = 31;
        public const uint FUNC_ROT = 32;
        public const uint FUNC_X2 = 33;
        public const uint FUNC_1X = 34;
        public const uint FUNC_SQRT = 35;
        public const uint FUNC_PI = 36;
        public const uint FUNC_EE = 37;
        public const uint FUNC_BX = 38;
        public const uint FUNC_RAND = 39;
        public const uint FUNC_SEED = 40;
        public const uint FUNC_WHOLE = 41;
        public const uint FUNC_FRAC = 42;
        public const uint FUNC_MAX = 43;
        public const uint FUNC_ABS = 44;
        public const uint FUNC_SIGN = 45;
        public const uint FUNC_AND = 46;
        public const uint FUNC_OR = 47;
        public const uint FUNC_XOR = 48;
        public const uint FUNC_NOT = 49;
        public const uint FUNC_D2DM = 50;
        public const uint FUNC_D2DMS = 51;
        public const uint FUNC_DM2D = 52;
        public const uint FUNC_DMS2D = 53;
        public const uint FUNC_D2RAD = 54;
        public const uint FUNC_RAD2D = 55;
        public const uint FUNC_MM2IN = 56;
        public const uint FUNC_IN2MM = 57;
        public const uint FUNC_M2X = 58;
        public const uint FUNC_X2M = 59;
        public const uint FUNC_K_M2X = 60;
        public const uint FUNC_K_X2M = 61;
        public const uint FUNC_A_M2X = 62;
        public const uint FUNC_A_X2M = 63;
        public const uint FUNC_GOTO = 64;
        public const uint FUNC_GOSUB = 65;
        public const uint FUNC_RETURN = 66;
        public const uint FUNC_MEMSET = 67;
        public const uint FUNC_MEMSWP = 68;
        public const uint FUNC_MEXTOX = 69;
        public const uint FUNC_XTOMEX = 70;
        public const uint FUNC_MEXTOR = 71;
        public const uint FUNC_RTOMEX = 72;
        public const uint FUNC_STOP = 75;
        public const uint FUNC_MKDIR = 76;
        public const uint FUNC_UPDIR = 77;
        public const uint FUNC_NEXTFILE = 78;
        public const uint FUNC_PREVFILE = 79;
        public const uint FUNC_REMOVE = 80;
        public const uint FUNC_STEPIN = 81;
        public const uint FUNC_SAVE = 82;
        public const uint FUNC_SAVEAS = 83;
        public const uint FUNC_LOAD = 84;
        public const uint FUNC_LOADFROM = 85;
        public const uint FUNC_CHAIN = 86;
        public const uint FUNC_SAVEDATA = 87;
        public const uint FUNC_SAVEDATAAS = 88;
        public const uint FUNC_LOADDATA = 89;
        public const uint FUNC_LOADDATAFROM = 90;
        public const uint FUNC_GOMEM = 91;
        public const uint FUNC_IFNOTLT0 = 92;
        public const uint FUNC_IFNOTEQ0 = 93;
        public const uint FUNC_IFNOTGE0 = 94;
        public const uint FUNC_IFNOTNE0 = 95;
        public const uint FUNC_IFNOTLTY = 96;
        public const uint FUNC_IFNOTEQY = 97;
        public const uint FUNC_IFNOTGEY = 98;
        public const uint FUNC_IFNOTNEY = 99;
        public const uint FUNC_L0 = 100;
        public const uint FUNC_L1 = 101;
        public const uint FUNC_L2 = 102;
        public const uint FUNC_L3 = 103;
        public const uint FUNC_LBX = 104;
        public const uint FUNC_LBY = 105;
        public const uint FUNC_LBZ = 106;
        public const uint FUNC_LBT = 107;
        public const uint FUNC_LBR = 108;
        public const uint FUNC_SAVEALL = 109;
        public const uint FUNC_SAVEALLAS = 110;
        public const uint FUNC_LOADALL = 111;
        public const uint FUNC_LOADALLFROM = 112;
        public const uint FUNC_NOP = 113;
        
        public const uint MK52_NFUNCTIONS = 128;
        public const int PROGRAM_LINE_LENGTH = 64; // TODO
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
            _appendFunction( new Func_Empty());
            // #define FUNC_COMMENT            1
            _appendFunction( new Func_Comment());
            // #define FUNC_SET_DMOD_DEG       9
            _appendFunction( new Func_set_DMOD_DEG());
            // #define FUNC_SET_DMOD_RAD       10
            _appendFunction( new Func_set_DMOD_RAD());
            // #define FUNC_SET_DMOD_GRD       11
            _appendFunction( new Func_set_DMOD_GRD());
            // #define FUNC_NEGATE             12
            _appendFunction( new Func_Negate());
            // #define FUNC_ENTER              13
            _appendFunction( new Func_Enter());
            // #define FUNC_SWAP               14
            _appendFunction( new Func_Swap());
            // #define FUNC_PLUS               15
            _appendFunction( new Func_Plus());
            // #define FUNC_MINUS              16
            _appendFunction( new Func_Minus());
            // #define FUNC_MULTIPLY           17
            _appendFunction( new Func_Multiply());
            // #define FUNC_DIVIDE             18
            _appendFunction( new Func_Divide());
            // #define FUNC_CLEAR_X            19
            _appendFunction( new Func_Clear_X());
            // #define FUNC_SIN                20
            _appendFunction( new Func_Sin());
            // #define FUNC_ARCSIN             21
            _appendFunction( new Func_ArcSin());
            // #define FUNC_COS                22
            _appendFunction( new Func_Cos());
            // #define FUNC_ARCCOS             23
            _appendFunction( new Func_ArcCos());
            // #define FUNC_TG                 24
            _appendFunction( new Func_Tg());
            // #define FUNC_ARCTG              25
            _appendFunction( new Func_ArcTg());
            // #define FUNC_EXP                26
            _appendFunction( new Func_Exp());
            // #define FUNC_10X                27
            _appendFunction( new Func_10x());
            // #define FUNC_LG                 28
            _appendFunction( new Func_Lg());
            // #define FUNC_LN                 29
            _appendFunction( new Func_Ln());
            // #define FUNC_POW                30
            _appendFunction( new Func_Pow());
            // #define FUNC_LOG                31
            _appendFunction( new Func_Log());
            // #define FUNC_ROT                32
            _appendFunction( new Func_Rot());
            // #define FUNC_X2                 33
            _appendFunction( new Func_X2());
            // #define FUNC_1X                 34
            _appendFunction( new Func_1X());
            // #define FUNC_SQRT               35
            _appendFunction( new Func_SQRT());
            // #define FUNC_PI                 36
            _appendFunction( new Func_PI());
            // #define FUNC_EE                 37
            _appendFunction( new Func_EE());
            // #define FUNC_BX                 38
            _appendFunction( new Func_Bx());
            // #define FUNC_RAND               39
            _appendFunction( new Func_Rand());
            // #define FUNC_SEED               40
            _appendFunction( new Func_Seed());
            // #define FUNC_WHOLE              41
            _appendFunction( new Func_Whole());
            // #define FUNC_FRAC               42
            _appendFunction( new Func_Frac());
            // #define FUNC_MAX                43
            _appendFunction( new Func_Max());
            // #define FUNC_ABS                44
            _appendFunction( new Func_Abs());
            // #define FUNC_SIGN               45
            _appendFunction( new Func_Sign());
            // #define FUNC_AND                46
            _appendFunction( new Func_And());
            // #define FUNC_OR                 47
            _appendFunction( new Func_Or());
            // #define FUNC_XOR                48
            _appendFunction( new Func_Xor());
            // #define FUNC_NOT                49
            _appendFunction( new Func_Not());
            // #define FUNC_D2DM               50
            _appendFunction( new Func_D2DM());
            // #define FUNC_D2DMS              51
            _appendFunction( new Func_D2DMS());
            // #define FUNC_DM2D               52
            _appendFunction( new Func_DM2D());
            // #define FUNC_DMS2D              53
            _appendFunction( new Func_DMS2D());
            // #define FUNC_D2RAD              54
            _appendFunction( new Func_D2Rad());
            // #define FUNC_RAD2D              55
            _appendFunction( new Func_Rad2D());
            // #define FUNC_MM2IN              56
            _appendFunction( new Func_mm2in());
            // #define FUNC_IN2MM              57
            _appendFunction( new Func_in2mm());
            // #define FUNC_M2X                58
            _appendFunction( new Func_M2X());
            // #define FUNC_X2M                59
            _appendFunction( new Func_X2M());
            // #define FUNC_K_M2X              60
            _appendFunction( new Func_K_M2X());
            // #define FUNC_K_X2M              61
            _appendFunction( new Func_K_X2M());
            // #define FUNC_A_M2X              62
            _appendFunction( new Func_A_M2X());
            // #define FUNC_A_X2M              63
            _appendFunction( new Func_A_X2M());
            // #define FUNC_GOTO               64
            _appendFunction( new Func_GOTO());
            // #define FUNC_GOSUB              65
            _appendFunction( new Func_GOSUB());
            // #define FUNC_RETURN             66
            _appendFunction( new Func_Return());
            // #define FUNC_MEMSET             67
            _appendFunction( new Func_MemSet());
            // #define FUNC_MEMSWP             68
            _appendFunction( new Func_MemSwp());
            // #define FUNC_MEXTOX             69
            _appendFunction( new Func_MexToX());
            // #define FUNC_XTOMEX             70
            _appendFunction( new Func_XToMex());
            // #define FUNC_MEXTOR             71
            _appendFunction( new Func_MexToR());
            // #define FUNC_RTOMEX             72
            _appendFunction( new Func_RToMex());
            // #define FUNC_STOP               75
            _appendFunction( new Func_Stop());
            // #define FUNC_MKDIR              76
            _appendFunction( new Func_MkDir());
            // #define FUNC_UPDIR              77
            _appendFunction( new Func_UpDir());
            // #define FUNC_NEXTFILE           78
            _appendFunction( new Func_NextFile());
            // #define FUNC_PREVFILE           79
            _appendFunction( new Func_PrevFile());
            // #define FUNC_REMOVE             80
            _appendFunction( new Func_Remove());
            // #define FUNC_STEPIN             81
            _appendFunction( new Func_StepIn());
            // #define FUNC_SAVE               82
            _appendFunction( new Func_Save());
            // #define FUNC_SAVEAS             83
            _appendFunction( new Func_SaveAs());
            // #define FUNC_LOAD               84
            _appendFunction( new Func_Load());
            // #define FUNC_LOADFROM           85
            _appendFunction( new Func_LoadFrom());
            // #define FUNC_CHAIN              86
            _appendFunction( new Func_Chain());
            // #define FUNC_SAVEDATA           87
            _appendFunction( new Func_SaveData());
            // #define FUNC_SAVEDATAAS         88
            _appendFunction( new Func_SaveDataAs());
            // #define FUNC_LOADDATA           89
            _appendFunction( new Func_LoadData());
            // #define FUNC_LOADDATAFROM       90
            _appendFunction( new Func_LoadDataFrom());
            // #define FUNC_GOMEM              91
            _appendFunction( new Func_GOMEM());
            // #define FUNC_IFNOTLT0           92
            _appendFunction( new Func_IfNotLT0());
            // #define FUNC_IFNOTEQ0           93
            _appendFunction( new Func_IfNotEQ0());
            // #define FUNC_IFNOTGE0           94
            _appendFunction( new Func_IfNotGE0());
            // #define FUNC_IFNOTNE0           95
            _appendFunction( new Func_IfNotNE0());
            // #define FUNC_IFNOTLTY           96
            _appendFunction( new Func_IfNotLTY());
            // #define FUNC_IFNOTEQY           97
            _appendFunction( new Func_IfNotEQY());
            // #define FUNC_IFNOTGEY           98
            _appendFunction( new Func_IfNotGEY());
            // #define FUNC_IFNOTNEY           99
            _appendFunction( new Func_IfNotNEY());
            // #define FUNC_L0                 100
            _appendFunction( new Func_L0());
            // #define FUNC_L1                 101
            _appendFunction( new Func_L1());
            // #define FUNC_L2                 102
            _appendFunction( new Func_L2());
            // #define FUNC_L3                 103
            _appendFunction( new Func_L3());
            // #define FUNC_LBX                104
            _appendFunction( new Func_LBX());
            // #define FUNC_LBY                105
            _appendFunction( new Func_LBY());
            // #define FUNC_LBZ                106
            _appendFunction( new Func_LBZ());
            // #define FUNC_LBT                107
            _appendFunction( new Func_LBT());
            // #define FUNC_LBR                108
            _appendFunction(new Func_LBR());
            // #define FUNC_SAVEALL            109
            _appendFunction(new Func_SaveAll());
            // #define FUNC_SAVEALLAS          110
            _appendFunction(new Func_SaveAllAs());
            // #define FUNC_LOADALL            111
            _appendFunction(new Func_LoadAll());
            // #define FUNC_LOADALLFROM        112
            _appendFunction(new Func_LoadAllFrom());

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

        public  string formFileName(string name)
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
