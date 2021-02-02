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

