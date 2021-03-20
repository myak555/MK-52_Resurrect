void Func_And::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    int64_t valueX = s->X->toInt();
    int64_t valueY = s->Y->toInt();
    s->pop(0);
    s->X->fromInt( valueX & valueY);
}

void Func_Or::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    int64_t valueX = s->X->toInt();
    int64_t valueY = s->Y->toInt();
    s->pop(0);
    s->X->fromInt( valueX | valueY);
}

void Func_Xor::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    int64_t valueX = s->X->toInt();
    int64_t valueY = s->Y->toInt();
    s->pop(0);
    s->X->fromInt( valueX ^ valueY);
}

void Func_Not::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    int64_t result = s->X->toInt();
    s->X->fromInt( ~result);
}

