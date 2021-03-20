void Func_Increment_MC::execute( void *components[], char *command){
    _ExtMem(components)->incrementCounter();
}

void Func_Decrement_MC::execute( void *components[], char *command){
    _ExtMem(components)->decrementCounter();
}

void Func_Reset_MC::execute( void *components[], char *command){
    _ExtMem(components)->resetCounter();
}

void Func_GOMEM::execute( void *components[], char *command){
    _ExtMem(components)->setCounter(command);
}

void Func_M2X::execute( void *components[], char *command){
    _RegMem(components)->MtoX(command);
}

void Func_X2M::execute( void *components[], char *command){
    _RegMem(components)->XtoM(command);
}

void Func_K_M2X::execute( void *components[], char *command){
    _RegMem(components)->K_MtoX(command);
}

void Func_K_X2M::execute( void *components[], char *command){
    _RegMem(components)->K_XtoM(command);
}

void Func_A_M2X::execute( void *components[], char *command){
    _RegMem(components)->A_MtoX(command);
}

void Func_A_X2M::execute( void *components[], char *command){
    _RegMem(components)->A_XtoM(command);
}

void Func_MemSet::execute( void *components[], char *command){
    _ExtMem(components)->fromString( command);
}

void Func_MemSwp::execute( void *components[], char *command){
    UniversalValue *X = _Stack( components)->X;
    _ExtMem(components)->swapWithUV( X);
    if( X->isEmpty()) X->fromInt(0);
}

void Func_MexToX::execute( void *components[], char *command){
    RPN_Stack *s = _Stack( components);
    s->storeBx();
    s->push();
    UniversalValue *X = s->X;
    _ExtMem(components)->toUV( X);
    if( X->isEmpty()) X->fromInt(0);
}

void Func_XToMex::execute( void *components[], char *command){
    _ExtMem(components)->fromUV( _Stack( components)->X);
}

void Func_MexToR::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    uint8_t *ptrE = _ExtMem(components)->getCurrentLine();
    uint8_t *ptrR = rm->_registerAddress( rm->registerByName( command));
    if( *ptrE == VALUE_TYPE_EMPTY){
        *ptrR++ = VALUE_TYPE_INTEGER;
        memset( ptrR, 0, 8);
        return;
    }
    memcpy( ptrR, ptrE, 9);
}

void Func_RToMex::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    uint8_t *ptrE = _ExtMem(components)->getCurrentLine();
    uint8_t *ptrR = rm->_registerAddress( rm->registerByName( command));
    memcpy( ptrE, ptrR, 9);
}

void Func_MexClr::execute( void *components[], char *command){
    _ExtMem(components)->clearCurrent();
}
