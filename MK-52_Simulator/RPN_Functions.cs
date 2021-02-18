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
        public const uint FUNC_INCREMENT_PC = 2;
        public const uint FUNC_DECREMENT_PC = 3;
        public const uint FUNC_INCREMENT_MC = 4;
        public const uint FUNC_DECREMENT_MC = 5;
        public const uint FUNC_RESET_PC = 6;
        public const uint FUNC_RESET_MC = 7;
        public const uint FUNC_TOGGLE_DMOD = 8;
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
        public const uint FUNC_MEXCLR = 73;
        public const uint FUNC_TOGGLE_EMOD = 74;
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
        public const uint FUNC_NOP = 104;
        
        public const uint MK52_NFUNCTIONS = 128;
        #endregion

        private MK52_Host _parent = null;
        private SD_Manager _sd = null;
        private List<RPN_Function> _functions = new List<RPN_Function>();
        private UniversalValue _tmpuv = new UniversalValue(); // temporary value for number conversion
        private string _receiverRequested = "None";
        private string _receiverReturnRequested = "None";
        private uint _receiverModeRequested = 0;

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
            // #define FUNC_INCREMENT_PC       2
            _appendFunction( new Func_Increment_PC());
            // #define FUNC_DECREMENT_PC       3
            _appendFunction( new Func_Decrement_PC());
            // #define FUNC_INCREMENT_MC       4
            _appendFunction( new Func_Increment_MC());
            // #define FUNC_DECREMENT_MC       5
            _appendFunction( new Func_Decrement_MC());
            // #define FUNC_RESET_PC           6
            _appendFunction( new Func_Reset_PC());
            // #define FUNC_RESET_MC           7
            _appendFunction( new Func_Reset_MC());
            // #define FUNC_TOGGLE_DMOD        8
            _appendFunction( new Func_Toggle_DMOD());
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
            // #define FUNC_MEXCLR             73
            _appendFunction( new Func_MexClr());
            // #define FUNC_TOGGLE_EMOD        74
            _appendFunction( new Func_Toggle_EMOD());
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
            //TODO
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
        }

        public void executeStep()
        {
            if (_atStop)
            {
                if (progMem.isAtStop()) progMem.incrementCounter();
                _atStop = false;
            }
            executeRun();
            if (_atStop)
                rpnStack.setStackLabel_P(0, "STOP Reached");
        }

        public void executeRun()
        {
            string programLine = progMem.getCurrentLine();
            execute( programLine);
        }
        #endregion

        #region File Operations (TODO)
        public bool loadStateFile()
        {
            return true;
        }

        public bool saveStateFile()
        {
            return true;
        }

        public bool loadProgramFile()
        {
            return loadProgramFile(null);
        }
 
        public bool loadProgramFile( string name)
        {
            return true;
        }

        public bool saveProgramFile()
        {
            return saveProgramFile(null);
        }
        
        public bool saveProgramFile( string name)
        {
            return true;
        }

        public bool loadDataFile()
        {
            return loadDataFile(null);
        }
 
        public bool loadDataFile( string name)
        {
            return true;
        }

        public bool saveDataFile()
        {
            return saveDataFile(null);
        }
        
        public bool saveDataFile( string name)
        {
            return true;
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


        public void requestNextReceiver(string name)
        {
            requestNextReceiver(name, "None", 0);
        }

        public void requestNextReceiver(string name, string exitTo, uint mode)
        {
            _receiverRequested = name;
            _receiverReturnRequested = exitTo;
            _receiverModeRequested = mode;
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

        public uint getRequestedReceiverMode()
        {
            return _receiverModeRequested;
        }

        public void appendProgramLine_P( uint id)
        {
            progMem.updateLine_P( getFunctionByID(id).Name());
        }

        #region Private Functions
        private void _appendFunction( RPN_Function f)
        {
            if (_functions.Count >= MK52_NFUNCTIONS) return;
            _functions.Add( f);
        }

        private bool _writeStackFile()
        {
            return true;
        }

        private bool _writeRegisterFile()
        {
            return true;
        }

        private bool _writeProgramFile()
        {
            return true;
        }

        private bool _writeDataFile()
        {
            return true;
        }

        private bool _readFile(bool readStack, bool readProg, bool readMem)
        {
            return true;
        }
        #endregion
    }
}
