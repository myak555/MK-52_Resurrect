void Func_Whole::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()) return;
    double result = s->X->toReal();
    if( result < 0) result = -floor( -result);
    else result = floor( result);
    s->X->fromReal( result);
}

void Func_Frac::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()){
        s->X->fromInt( 0);
        return;
    }
    double result = s->X->toReal();
    bool positive = true;
    if( result < 0){
        result = -result;
        positive = false;
    }
    result = result - floor( result);
    s->X->fromReal( positive? result: -result);
}

void Func_Max::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    if( valueY > valueX) s->swap(); // keep both values in stack
}

void Func_Abs::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if( result >= 0) return;
    if( s->X->isReal()){
        s->X->fromReal( -result);
        return;
    }
    s->X->fromInt( -s->X->toInt());
}

void Func_Sign::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if( result == 0.0) return;
    s->X->fromInt( ( result < 0.0)? -1: 1);
}
