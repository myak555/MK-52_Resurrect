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
