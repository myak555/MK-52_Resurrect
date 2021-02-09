void Func_GOTO::execute( void *components[], char *command){
    _ProgMem( components)->setCounter(command);
}

void Func_GOSUB::execute( void *components[], char *command){
    Program_Memory *pm = _ProgMem( components);
    if( !pm->goSub(command)) return;
    RPN_Stack *st = _Stack( components);
    st->setStackLabel_P(0, PSTR("Error: call stack full"));
}

void Func_Return::execute( void *components[], char *command){
    Program_Memory *pm = _ProgMem( components);
    if( !pm->returnFromSub()) return;
    RPN_Stack *st = _Stack( components);
    st->setStackLabel_P(0, PSTR("Error: stack busted!"));
}
