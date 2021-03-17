void Func_GOSUB::execute( void *components[], char *command){
    Program_Memory *pm = _ProgMem( components);
    if( !pm->goSub(command)) return;
    _Stack( components)->setLabel_P(0, PSTR("Error: call stack full"));
}

void Func_Return::execute( void *components[], char *command){
    Program_Memory *pm = _ProgMem( components);
    if( !pm->returnFromSub()) return;
    _Stack( components)->setLabel_P(0, PSTR("Error: stack busted!"));
}
