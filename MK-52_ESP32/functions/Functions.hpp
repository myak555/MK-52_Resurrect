#include "functions.h"

//
// Arithmetic
//
class Func_Negate: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NEGATE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("/-/");};
        inline const char*IOName(){ return PSTR("/-/");};
        void execute( void *components[], char *command);
};
class Func_Plus: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PLUS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("+");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Minus: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MINUS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("-");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Multiply: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MULTIPLY;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("*");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Divide: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DIVIDE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("/");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

//
// Comments, numbers and misc
// 
class Func_Comment: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COMMENT;};
        inline bool checkName(char *name){ return name[0]=='#';};
        inline const char*Name(){ return PSTR("#");};
        inline void execute( void *components[], char *command){};
};

class Func_Empty: public RPN_Function{
    public:
        inline bool checkName(char *name){ return name[0]==0;};
        inline const char*Name(){ return PSTR("");};
        inline void execute( void *components[], char *command){};
};

class Func_Number: public RPN_Function{
    public:
        inline bool checkName(char *name){ return UniversalValue::_looksLikeANumber(name);};
        void execute( void *components[], char *command);
};

//
// Converters
// 
class Func_in2mm: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IN2MM;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("in->mm");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_mm2in: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MM2IN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("mm->in");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_DM2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DM2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("<-DM");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_D2DM: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DM;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("->DM");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_DMS2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMS2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("<-DMS");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_D2DMS: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DMS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("->DMS");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

//
// File operations
// 
class Func_MkDir: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MKDIR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MKDIR ");};
        void execute( void *components[], char *command){
            _SDM(components)->createFolder( command);};
};

class Func_Remove: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_REMOVE;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("REMOVE ");};
        void execute( void *components[], char *command){
            _SDM(components)->deleteEntity( command);};
};

class Func_Save: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVE;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVE ");};
        void execute( void *components[], char *command);
};

class Func_Load: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOAD;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LOAD ");};
        void execute( void *components[], char *command);
};

class Func_SaveData: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEDATA;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVEDATA ");};
        void execute( void *components[], char *command);
};

class Func_LoadData: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADDATA;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LOADDATA ");};
        void execute( void *components[], char *command);
};

class Func_SaveAll: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEALL;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVEALL ");};
        void execute( void *components[], char *command);
};

class Func_LoadAll: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADALL;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LOADALL ");};
        void execute( void *components[], char *command);
};

class Func_Chain: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CHAIN;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("CHAIN ");};
        inline void advancePC(void *components[]){};
        void execute( void *components[], char *command);
};

//
// GOTO's and LOOP's
// 

class Func_GOTO: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOTO;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command){
            _ProgMem( components)->setCounter(command);};
};

class Func_GOSUB: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOSUB;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOSUB ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_Return: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RETURN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RETURN");};
        inline void advancePC(void *components[]){};
        void execute( void *components[], char *command);
};

class Func_Stop: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_STOP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("STOP");};
        // On the original MK-52 STOP advances PC to the next operator
        inline void advancePC(void *components[]){
           _ProgMem( components)->incrementCounter(); 
        };
        inline void execute( void *components[], char *command){
            RPN_Functions *fs = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
            fs->_atStop = true;};
};

class Func_L0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L0>0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L0);};
};

class Func_L1: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L1;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L1>0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L1);};
};

class Func_L2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L2;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L2>0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L2);};
};

class Func_L3: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L3;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L3>0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L3);};
};

//
// IF's branching
// 
class Func_IfNotLT0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTLT0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X<0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotEQ0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTEQ0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X=0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotGE0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTGE0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X>=0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotNE0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTNE0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X!=0 GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotLTY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTLTY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X<Y GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotEQY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTEQY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X=Y GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotGEY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTGEY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X>=Y GOTO ");};
        inline void advancePC(void *components[]){};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotNEY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTNEY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X!=Y GOTO ");};
        inline void advancePC(void *components[]){};
        void execute( void *components[], char *command);
};

//
// Logarithms
// 
class Func_Ln: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LN");};
        inline const char*IOName(){ return PSTR("Ln");};
        void execute( void *components[], char *command);
};

class Func_Lg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LG");};
        inline const char*IOName(){ return PSTR("Lg");};
        void execute( void *components[], char *command);
};

class Func_Log: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LOG");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_EE: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_EE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("e");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

//
// Logical TODO: these functions are nearly useless
// 
class Func_And: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_AND;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("AND");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Or: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_OR;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("OR");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Xor: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_XOR;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("XOR");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Not: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NOT;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("NOT");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

//
// Memory access
// 

class Func_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("M->X ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("X->M ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_K_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K M->X ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_K_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K X->M ");}; 
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;}; 
        void execute( void *components[], char *command);
};

class Func_A_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A M->X ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsMC(){return true;};
        void execute( void *components[], char *command);
};

class Func_A_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A X->M ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsMC(){return true;};
        void execute( void *components[], char *command);
};

class Func_MemSet: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEMSET;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MEMSET ");};
        void execute( void *components[], char *command);
};

class Func_MemSwp: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEMSWP;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MEMSWP ");};
        void execute( void *components[], char *command);
};

class Func_MexToX: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXTOX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("ExToX ");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_XToMex: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_XTOMEX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("XToEx ");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_MexToR: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXTOR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("ExToR ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_RToMex: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RTOMEX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("RToEx ");};
        inline const char*IOName(){ return Name();}; // TODO
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

//
// Number
// 
class Func_Whole: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_WHOLE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("[X]");};
        void execute( void *components[], char *command);
};

class Func_Frac: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_FRAC;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("{X}");};
        void execute( void *components[], char *command);
};

class Func_Max: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MAX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("MAX");};
        void execute( void *components[], char *command);
};

class Func_Abs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ABS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("|X|");};
        void execute( void *components[], char *command);
};

class Func_Sign: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SIGN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SIGN");};
        void execute( void *components[], char *command);
};

//
// Power functions
// 
class Func_Exp: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_EXP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("EXP");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_10x: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_10X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("10^x");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_Pow: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POW;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X^Y");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_PowYX: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POWYX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Y^X");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_X2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X^2");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_SQRT: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SQRT;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SQRT");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_1X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_1X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("1/X");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

//
// Random numbers
// 
class Func_Rand: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RAND;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAND");};
        void execute( void *components[], char *command);
};

class Func_Seed: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SEED;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SEED");};
        void execute( void *components[], char *command);
};

//
// Stack manipulation
// 
class Func_Enter: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ENTER;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Enter");};
        inline const char*IOName(){ return PSTR("Enter");}; // TODO
        inline void execute( void *components[], char *command){
            _Stack( components)->push();};
};

class Func_Swap: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SWAP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X<->Y");};
        inline const char*IOName(){ return PSTR("X<->Y");}; // TODO
        inline void execute( void *components[], char *command){
            _Stack( components)->swap();};
};

class Func_Clear_X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CLEAR_X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Cx");};
        inline void execute( void *components[], char *command){
            _Stack( components)->X->fromInt(0);};
};

class Func_Rot: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ROT;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Rotate");};
        inline const char*IOName(){ return PSTR("Rotate");};
        inline void execute( void *components[], char *command){
            _Stack( components)->rotate();
        };
};

class Func_Bx: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_BX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Bx");};
        inline void execute( void *components[], char *command){
            _Stack( components)->push(0);
        };
};

class Func_LBX: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBX> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setLabel( 0, command);};
};

class Func_LBY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBY> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setLabel( 1, command);};
};

class Func_LBZ: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBZ;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBZ> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setLabel( 2, command);};
};

class Func_LBT: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBT;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBT> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setLabel( 3, command);};
};

class Func_LBR: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBR;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LBR");};
        inline void execute( void *components[], char *command){
            _Stack(components)->resetLabels();};
};

//
// Trig
// 
class Func_Sin: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SIN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SIN");};
        inline const char*IOName(){ return PSTR("Sin");};
        void execute( void *components[], char *command);
};

class Func_ArcSin: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCSIN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcSIN");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_Cos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("COS");};
        inline const char*IOName(){ return PSTR("Cos");};
        void execute( void *components[], char *command);
};

class Func_ArcCos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCCOS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcCOS");};
        inline const char*IOName(){ return Name();}; //TODO
        void execute( void *components[], char *command);
};

class Func_Tg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("TG");};
        inline const char*IOName(){ return PSTR("Tg");};
        void execute( void *components[], char *command);
};

class Func_ArcTg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCTG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcTG");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_PI: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PI;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("pi");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_D2Rad: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2RAD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG->RAD");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_Rad2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RAD2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAD->DEG");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_DMOD_DEG: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMOD_DEG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_DEGREES);};
};

class Func_DMOD_RAD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMOD_RAD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAD");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_RADIANS);};
};

class Func_DMOD_GRD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMOD_GRD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("GRD");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_GRADS);};
};

//
// ESP32 Hardware
// 
class Func_Delay: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DELAY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("DELAY ");};
        void execute( void *components[], char *command);
};

class Func_LEDOn: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LEDON;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LED ON");};
        void execute( void *components[], char *command);
};

class Func_LEDOff: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LEDOFF;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LED OFF");};
        void execute( void *components[], char *command);
};

class Func_Update: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_UPDATE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("UPDATE");};
        void execute( void *components[], char *command);
};

//
// Hyperbolic
// 
class Func_Sinh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SINH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SINH");};
        inline const char*IOName(){ return PSTR("Sinh");};
        void execute( void *components[], char *command);
};

class Func_ArSinh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARSINH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArSINH");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

class Func_Cosh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COSH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("COSH");};
        inline const char*IOName(){ return PSTR("Cosh");};
        void execute( void *components[], char *command);
};

class Func_ArCosh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCOSH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArCOSH");};
        inline const char*IOName(){ return Name();}; //TODO
        void execute( void *components[], char *command);
};

class Func_Tgh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TGH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("TGH");};
        inline const char*IOName(){ return PSTR("Tgh");};
        void execute( void *components[], char *command);
};

class Func_ArTgh: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARTGH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArTGH");};
        inline const char*IOName(){ return Name();}; // TODO
        void execute( void *components[], char *command);
};

//
// Solvers
// 
class Func_Radius: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RADIUS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RADIUS");};
        inline const char*IOName(){ return PSTR("Radius");};
        void execute( void *components[], char *command);
};

class Func_Cath: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CATH;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("CATH");};
        inline const char*IOName(){ return PSTR("Cathetus");};
        void execute( void *components[], char *command);
};

class Func_Poly1: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POLY1;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("POLY1");};
        inline const char*IOName(){ return PSTR("Polynomial1");};
        void execute( void *components[], char *command);
};

class Func_Poly2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POLY2;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("POLY2");};
        inline const char*IOName(){ return PSTR("Polynomial2");};
        void execute( void *components[], char *command);
};

class Func_Poly3: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POLY3;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("POLY3");};
        inline const char*IOName(){ return PSTR("Polynomial3");};
        void execute( void *components[], char *command);
};
