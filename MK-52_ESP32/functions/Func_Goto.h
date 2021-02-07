void Func_GOTO::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    pm->setCounter(command);
}

void Func_GOSUB::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    bool result = pm->setCounter(command);
    if( !result) return;
    RPN_Stack *st = (RPN_Stack *)components[COMPONENT_STACK];
    st->setStackLabel_P(0, PSTR("Error: call stack full"));
}

void Func_Return::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    bool result = pm->returnFromSub();
    if( !result) return;
    RPN_Stack *st = (RPN_Stack *)components[COMPONENT_STACK];
    st->setStackLabel_P(0, PSTR("Error: stack busted!"));
}

void Func_L0::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    int64_t *ptr = (int64_t *)(rm->_registerAddress( 16) + 1);
    if( *ptr > 0){
        *ptr = (*ptr) - 1;
        pm->setCounter(command);
    }
    else
        pm->incrementCounter();
}

void Func_L1::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    int64_t *ptr = (int64_t *)(rm->_registerAddress( 17) + 1);
    if( *ptr > 0){
        *ptr = (*ptr) - 1;
        pm->setCounter(command);
    }
    else
        pm->incrementCounter();
}

void Func_L2::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    int64_t *ptr = (int64_t *)(rm->_registerAddress( 18) + 1);
    if( *ptr > 0){
        *ptr = (*ptr) - 1;
        pm->setCounter(command);
    }
    else
        pm->incrementCounter();
}

void Func_L3::execute( void *components[], char *command){
    Program_Memory *pm = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    int64_t *ptr = (int64_t *)(rm->_registerAddress( 19) + 1);
    if( *ptr > 0){
        *ptr = (*ptr) - 1;
        pm->setCounter(command);
    }
    else
        pm->incrementCounter();
}
