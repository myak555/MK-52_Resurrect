#include "functions.h"

class Func_Comment: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COMMENT;};
        inline bool checkName(char *name){ return name[0]=='#';};
        inline const char*Name(){ return PSTR("#");};
        inline void execute( void *components[], char *command){};
};

class Func_Increment_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_INCREMENT_PC;};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            _ProgMem(components)->incrementCounter();};
};

class Func_Decrement_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DECREMENT_PC;};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            _ProgMem(components)->decrementCounter();};
};

class Func_Increment_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_INCREMENT_MC;};
        inline bool advanceRequired(){return false;};
        void execute( void *components[], char *command);
};

class Func_Decrement_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DECREMENT_MC;};
        inline bool advanceRequired(){return false;};
        void execute( void *components[], char *command);
};

class Func_Reset_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RESET_PC;};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            _ProgMem(components)->resetCounter();};
};

class Func_Reset_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RESET_MC;};
        inline bool advanceRequired(){return false;};
        void execute( void *components[], char *command);
};

class Func_Toggle_DMOD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TOGGLE_DMOD;};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            _Stack( components)->toggleAngleMode();};
};

class Func_set_DMOD_DEG: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_DEG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_DEGREES);};
};

class Func_set_DMOD_RAD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_RAD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAD");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_RADIANS);};
};

class Func_set_DMOD_GRD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_GRD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("GRD");};
        inline void execute( void *components[], char *command){
            _Stack( components)->setDMode( DMODE_GRADS);};
};

class Func_Negate: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NEGATE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("/-/");};
        inline const char*IOName(){ return PSTR("/-/");};
        void execute( void *components[], char *command);
};

class Func_Enter: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ENTER;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Enter");};
        inline const char*IOName(){ return PSTR("Enter");};
        inline void execute( void *components[], char *command){
            _Stack( components)->push();};
};

class Func_Swap: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SWAP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X<->Y");};
        inline const char*IOName(){ return PSTR("X<->Y");};
        inline void execute( void *components[], char *command){
            _Stack( components)->swap();};
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

class Func_Clear_X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CLEAR_X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Cx");};
        inline void execute( void *components[], char *command){
            _Stack( components)->X->fromInt(0);};
};

class Func_Sin: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SIN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SIN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcSin: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCSIN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcSIN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Cos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("COS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcCos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCCOS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcCOS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Tg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("TG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcTg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCTG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("ArcTG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Exp: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_EXP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("EXP");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Ln: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_10x: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_10X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("10^x");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Lg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Pow: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POW;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X^Y");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Log: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("LOG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_X2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X^2");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_SQRT: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SQRT;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SQRT");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_1X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_1X;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("1/X");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Rot: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ROT;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Rotate");};
        inline const char*IOName(){ return PSTR("Rotate");};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = _Stack( components);
            _stack->rotate();
        };
};

class Func_Bx: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_BX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Bx");};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = _Stack( components);
            _stack->push(0);
        };
};

class Func_EE: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_EE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("e");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_PI: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PI;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("pi");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

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

class Func_D2Rad: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2RAD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG->RAD");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Rad2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RAD2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAD->DEG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_DM2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DM2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("<-DM");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_D2DM: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DM;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("->DM");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_DMS2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMS2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("<-DMS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_D2DMS: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DMS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("->DMS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_in2mm: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IN2MM;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("in->mm");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_mm2in: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MM2IN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("mm->in");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("M->X ");};
        inline const char*IOName(){ return Name();};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("X->M ");};
        inline const char*IOName(){ return Name();};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_K_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K M->X ");};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_K_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K X->M ");};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_A_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A M->X ");};
        inline const char*IOName(){ return Name();};
        inline bool containsMC(){return true;};
        void execute( void *components[], char *command);
};

class Func_A_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A X->M ");};
        inline const char*IOName(){ return Name();};
        inline bool containsMC(){return true;};
        void execute( void *components[], char *command);
};

class Func_MemSet: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEMSET;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MEMSET ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_MemSwp: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEMSWP;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MEMSWP ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_MexToX: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXTOX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("ExToX ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_XToMex: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_XTOMEX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("XToEx ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_MexToR: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXTOR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("ExToR ");};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_RToMex: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RTOMEX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("RToEx ");};
        inline bool containsRegister(){return true;};
        void execute( void *components[], char *command);
};

class Func_MexClr: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXCLR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MexCx");};
        void execute( void *components[], char *command);
};

class Func_GOTO: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOTO;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command){
            _ProgMem( components)->setCounter(command);};
};

class Func_GOMEM: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOMEM;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOMEM ");};
        inline bool containsMC(){return true;};
        void execute( void *components[], char *command);
};

class Func_GOSUB: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOSUB;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOSUB ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_Return: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RETURN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RETURN");};
        inline bool advanceRequired(){return false;};
        void execute( void *components[], char *command);
};

class Func_Stop: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_STOP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("STOP");};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            RPN_Functions *fs = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
            fs->_atStop = true;};
};

class Func_Toggle_EMOD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TOGGLE_EMOD;};
        inline bool advanceRequired(){return false;};
        inline void execute( void *components[], char *command){
            _ProgMem(components)->toggleEditMode();};
};

class Func_MkDir: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MKDIR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MKDIR ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command){
            _SDM(components)->createFolder( command);};
};

class Func_UpDir: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_UPDIR;};
        void execute( void *components[], char *command){
            _SDM(components)->upFolder();};
};

class Func_NextFile: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NEXTFILE;};
        void execute( void *components[], char *command){
            _SDM(components)->nextListingPosition();};
};

class Func_PrevFile: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PREVFILE;};
        void execute( void *components[], char *command){
            _SDM(components)->previousListingPosition();};
};

class Func_Remove: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_REMOVE;};
        void execute( void *components[], char *command);
};

class Func_StepIn: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_STEPIN;};
        void execute( void *components[], char *command);
};

class Func_Save: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVE;};
        void execute( void *components[], char *command);
};

class Func_SaveAs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEAS;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVE AS ");};
        void execute( void *components[], char *command);
};

class Func_Load: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOAD;};
        void execute( void *components[], char *command);
};

class Func_LoadFrom: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADFROM;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LOAD ");};
        void execute( void *components[], char *command);
};

class Func_SaveData: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEDATA;};
        void execute( void *components[], char *command);
};

class Func_SaveDataAs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEDATAAS;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVE DATA AS ");};
        void execute( void *components[], char *command);
};

class Func_LoadData: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADDATA;};
        void execute( void *components[], char *command);
};

class Func_LoadDataFrom: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADDATAFROM;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LOADDATA ");};
        void execute( void *components[], char *command);
};

class Func_Chain: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CHAIN;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("CHAIN ");};
        void execute( void *components[], char *command);
};

class Func_IfNotLT0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTLT0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X<0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotEQ0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTEQ0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X=0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotGE0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTGE0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X>=0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotNE0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTNE0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X!=0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotLTY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTLTY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X<Y GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotEQY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTEQY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X=Y GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotGEY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTGEY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X>=Y GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        void execute( void *components[], char *command);
};

class Func_IfNotNEY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_IFNOTNEY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("IFNOT X!=Y GOTO ");};
        inline bool advanceRequired(){return false;};
        void execute( void *components[], char *command);
};

class Func_L0: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L0;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L0>0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L0);};
};

class Func_L1: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L1;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L1>0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L1);};
};

class Func_L2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L2;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L2>0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L2);};
};

class Func_L3: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_L3;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("WHILE L3>0 GOTO ");};
        inline bool advanceRequired(){return false;};
        inline bool containsPC(){return true;};
        inline void execute( void *components[], char *command){
            _executeLoop( components, command, RPN_REGISTER_L3);};
};

class Func_LBX: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBX> ");};
        inline const char*IOName(){ return PSTR("LBX> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setStackLabel( 0, command);};
};

class Func_LBY: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBY;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBY> ");};
        inline const char*IOName(){ return PSTR("LBY> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setStackLabel( 1, command);};
};

class Func_LBZ: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBZ;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBZ> ");};
        inline const char*IOName(){ return PSTR("LBZ> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setStackLabel( 2, command);};
};

class Func_LBT: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LBT;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("LBT> ");};
        inline const char*IOName(){ return PSTR("LBT> ");};
        inline void execute( void *components[], char *command){
            _Stack(components)->setStackLabel( 3, command);};
};
