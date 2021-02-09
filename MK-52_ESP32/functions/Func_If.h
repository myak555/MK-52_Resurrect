void Func_IfNotLT0::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() < 0.0) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotEQ0::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() == 0.0) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotGE0::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() >= 0.0) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotNE0::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() != 0.0) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotLTY::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() < st->Y->toReal()) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotEQY::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() == st->Y->toReal()) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotGEY::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() >= st->Y->toReal()) pm->incrementCounter();
    else pm->setCounter(command);
}

void Func_IfNotNEY::execute( void *components[], char *command){
    RPN_Stack *st = _Stack( components);
    Program_Memory *pm = _ProgMem( components);
    if( st->X->toReal() != st->Y->toReal()) pm->incrementCounter();
    else pm->setCounter(command);
}
