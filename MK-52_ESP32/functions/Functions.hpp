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
        inline void execute( void *components[], char *command){
            Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
            extMem->incrementCounter();
        };
};

class Func_Decrement_MC: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DECREMENT_MC;};
        inline bool checkName(char *name){ return false;};
        inline const char*Name(){ return (const char*)NULL;};
        inline const char*IOName(){ return (const char*)NULL;};
        inline void execute( void *components[], char *command){
            Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
            extMem->decrementCounter();
        };
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
        inline void execute( void *components[], char *command){
            Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
            extMem->resetCounter();
        };
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("/-/");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Enter: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ENTER;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("+");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Minus: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MINUS;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("-");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Multiply: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MULTIPLY;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("*");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Divide: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_DIVIDE;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("/");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Clear_X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_CLEAR_X;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("SIN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcSin: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCSIN;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("ArcSIN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Cos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_COS;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("COS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcCos: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCCOS;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("ArcCOS");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Tg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_TG;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("TG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_ArcTg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ARCTG;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("ArcTG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Exp: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_EXP;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("EXP");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Ln: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LN;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("LN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_10x: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_10X;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("10^x");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Lg: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LG;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("LG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Pow: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_POW;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("X^Y");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Log: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_LOG;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("LOG");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_X2: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_X2;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("X^2");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_SQRT: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SQRT;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("SQRT");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_1X: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_1X;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("1/X");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Rot: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ROT;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
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
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("e");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_PI: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_PI;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("pi");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Rand: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_RAND;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("RAND");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Seed: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SEED;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("SEED");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Whole: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_WHOLE;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("[X]");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Frac: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_FRAC;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("{X}");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Max: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_MAX;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("MAX");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Abs: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_ABS;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("|X|");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};

class Func_Sign: public RPN_Function{
    public:
        inline bool checkID( uint16_t id){ return id == FUNC_SIGN;};
        inline bool checkName(char *name){ return strcmp_P(name, Name())==0;};
        inline const char*Name(){ return PSTR("SIGN");};
        inline const char*IOName(){ return Name();};
        void execute( void *components[], char *command);
};
