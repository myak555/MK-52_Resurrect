void Func_And::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    bool valueX = s->X->toInt() > 0;
    bool valueY = s->Y->toInt() > 0;
    s->pop(0);
    s->X->fromInt( (valueX && valueY)? 1: 0);
}

void Func_Or::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    bool valueX = s->X->toInt() > 0;
    bool valueY = s->Y->toInt() > 0;
    s->pop(0);
    s->X->fromInt( (valueX || valueY)? 1: 0);
}

void Func_Xor::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    bool valueX = s->X->toInt() > 0;
    bool valueY = s->Y->toInt() > 0;
    bool result = valueX? !valueY: valueY;
    s->pop(0);
    s->X->fromInt( result? 1: 0);
}

void Func_Not::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    bool result = s->X->toInt() > 0;
    s->X->fromInt( result? 0: 1);
}

