void Func_Ln::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    result = log( result);
    s->X->fromReal( result);
}

void Func_Lg::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    result = log10( result);
    s->X->fromReal( result);
}

void Func_Log::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double x = s->X->toReal();
    double y = s->Y->toReal();
    s->pop(0);
    if ( x<=0.0 || y<=0.0){
        s->X->fromReal( NAN);
        return;
    }
    if( y == 1.0){
        s->X->fromReal( INFINITY);
        return;
    }
    double result = log10(y) / log10(x);
    s->X->fromReal( result);
}

void Func_EE::execute( void *components[], char *command){
    RPN_Stack *s = _Stack( components);
    s->storeBx();
    s->push();
    s->X->fromReal( __EE);
}
