void Func_Rand::execute( void *components[], char *command){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    s->storeBx();
    s->push();
    double result = (double)rand();
    s->X->fromReal( result/RAND_MAX);
}

void Func_Seed::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL){
        srand( 1);
        return;
    }
    int32_t result = (int32_t)(s->X->toInt() & 0x7FFF);
    srand( result);
    s->pop(0);
}
