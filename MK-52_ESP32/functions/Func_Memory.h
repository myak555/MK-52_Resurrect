void Func_Increment_MC::execute( void *components[], char *command){
    Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    extMem->incrementCounter();
}

void Func_Decrement_MC::execute( void *components[], char *command){
    Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    extMem->decrementCounter();
}

void Func_Reset_MC::execute( void *components[], char *command){
    Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    extMem->resetCounter();
}

void Func_GOMEM::execute( void *components[], char *command){
    Extended_Memory *extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    extMem->setCounter(command);
}

void Func_M2X::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->MtoX(command);
}

void Func_X2M::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->XtoM(command);
}

void Func_K_M2X::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->K_MtoX(command);
}

void Func_K_X2M::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->K_XtoM(command);
}

void Func_A_M2X::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->A_MtoX(command);
}

void Func_A_X2M::execute( void *components[], char *command){
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    rm->A_XtoM(command);
}

void Func_MemSet::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    UniversalValue *uv = new UniversalValue(em->getCurrentLine());
    Serial.print("Data to EM");
    Serial.print(command);
    uv->fromString( command);
    delete( uv);
}

void Func_MemSwp::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    RPN_Stack *stk = (RPN_Stack *)components[COMPONENT_STACK];
    uint8_t *ptr = em->getCurrentLine();
    if( *ptr == VALUE_TYPE_EMPTY){
        stk->X->toLocation(ptr);
        stk->X->fromInt(0);
        return;
    }
    uint8_t tmp[9];
    stk->X->toLocation( tmp);
    stk->X->fromLocation( ptr);
    memcpy( ptr, tmp, 9);
}

void Func_MexToX::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    RPN_Stack *stk = (RPN_Stack *)components[COMPONENT_STACK];
    stk->storeBx();
    stk->push();
    uint8_t *ptr = em->getCurrentLine();
    if( *ptr == VALUE_TYPE_EMPTY){
        stk->X->fromInt(0);
        return;
    }
    stk->X->fromLocation( ptr);
}

void Func_XToMex::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    RPN_Stack *stk = (RPN_Stack *)components[COMPONENT_STACK];
    uint8_t *ptr = em->getCurrentLine();
    stk->X->toLocation( ptr);
}

void Func_MexToR::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    uint8_t *ptrE = em->getCurrentLine();
    uint8_t *ptrR = rm->_registerAddress( rm->registerByName( command));
    if( *ptrE == VALUE_TYPE_EMPTY){
        *ptrR++ = VALUE_TYPE_INTEGER;
        memset( ptrR, 0, 8);
        return;
    }
    memcpy( ptrR, ptrE, 9);
}

void Func_RToMex::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    Register_Memory *rm = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    uint8_t *ptrE = em->getCurrentLine();
    uint8_t *ptrR = rm->_registerAddress( rm->registerByName( command));
    memcpy( ptrE, ptrR, 9);
}

void Func_MexClr::execute( void *components[], char *command){
    Extended_Memory *em = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    uint8_t *ptr = em->getCurrentLine();
    memset( ptr, 0, 9);
}
