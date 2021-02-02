#include "functions.h"

class Func_Comment: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COMMENT;};
        inline bool checkName(char *name){ return name[0]=='#';};
        inline const char*Name(){ return PSTR("#");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){};
};

class Func_Increment_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_INCREMENT_PC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            Program_Memory *progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
            progMem->incrementCounter();
        };
};

class Func_Decrement_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DECREMENT_PC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            Program_Memory *progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
            progMem->decrementCounter();
        };
};

class Func_Increment_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_INCREMENT_MC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        void execute( void *components[], char *command);
};

class Func_Decrement_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DECREMENT_MC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        void execute( void *components[], char *command);
};

class Func_Reset_PC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RESET_PC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            Program_Memory *progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
            progMem->resetCounter();
        };
};

class Func_Reset_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RESET_MC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        void execute( void *components[], char *command);
};

class Func_Toggle_DMOD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TOGGLE_DMOD;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->toggleAngleMode();
        };
};

class Func_set_DMOD_DEG: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_DEG;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->setDMode( DMODE_DEGREES);
        };
};

class Func_set_DMOD_RAD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_RAD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RAD");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->setDMode( DMODE_RADIANS);
        };
};

class Func_set_DMOD_GRD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SET_DMOD_GRD;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("GRD");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->setDMode( DMODE_GRADS);
        };
};

class Func_Negate: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NEGATE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("/-/");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Enter: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ENTER;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Enter");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->push();
        };
};

class Func_Swap: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SWAP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("X<->Y");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->swap();
        };
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
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->X->fromInt(0);
        };
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
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
            _stack->rotate();
        };
};

class Func_Bx: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_BX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("Bx");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Stack *_stack = (RPN_Stack *)components[COMPONENT_STACK];
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
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Seed: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SEED;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SEED");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Whole: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_WHOLE;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("[X]");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Frac: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_FRAC;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("{X}");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Max: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MAX;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("MAX");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Abs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ABS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("|X|");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Sign: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SIGN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("SIGN");};
        inline const char*IOName(){ return Name();};
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
        inline const char*Name(){ return PSTR("DM->DEG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_D2DM: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DM;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG->DM");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_DMS2D: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DMS2D;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DMS->DEG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_D2DMS: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_D2DMS;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("DEG->DMS");};
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
        void execute( void *components[], char *command);
};

class Func_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("X->M ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_K_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K M->X ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_K_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_K_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("K X->M ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_A_M2X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_M2X;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A M->X ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_A_X2M: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_A_X2M;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("A X->M ");};
        inline const char*IOName(){ return Name();};
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
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_RToMex: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RTOMEX;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("RToEx ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_MexClr: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MEXCLR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MexCx");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_GOTO: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOTO;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOTO ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_GOMEM: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOMEM;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOMEM ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_GOSUB: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_GOSUB;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("GOSUB ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Return: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RETURN;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("RETURN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Stop: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_STOP;};
        inline bool checkName(char *name){ return UniversalValue::_identicalTo_P( name, Name());};
        inline const char*Name(){ return PSTR("STOP");};
        inline const char*IOName(){ return Name();};
        inline void execute( void *components[], char *command){
            RPN_Functions *fs = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
            fs->_atStop = true;};
};

class Func_Toggle_EMOD: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TOGGLE_EMOD;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
            pm->toggleEditMode();};
};

class Func_MkDir: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MKDIR;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("MKDIR ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_UpDir: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_UPDIR;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};

class Func_NextFile: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_NEXTFILE;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};

class Func_PrevFile: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PREVFILE;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};

class Func_Remove: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_REMOVE;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};

class Func_StepIn: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_STEPIN;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};

// Insert here! TODO

class Func_SaveDataAs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SAVEDATAAS;};
        inline bool checkName(char *name){ return UniversalValue::_startsWith_P( name, Name());};
        inline const char*Name(){ return PSTR("SAVEDATA ");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_LoadData: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOADDATA;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return NULL;};
        inline const char*IOName(){ return NULL;};
        void execute( void *components[], char *command);
};
