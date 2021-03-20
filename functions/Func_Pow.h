void Func_Exp::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    result = exp( result);
    s->X->fromReal( result);
}

void Func_10x::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = 1.0;
    if( s->X->isReal()){
        result = pow( 10.0, s->X->toReal());
        s->X->fromReal( result);
        return;
    }
    int64_t p = s->X->toInt();
    if( p>300){
        s->X->fromReal( INFINITY);
        return;
    }
    if(p<-300){
        s->X->fromInt( 0);
        return;
    }
    if( 0<=p && p<=18){
        int64_t r2 = 1L;
        while( p>0){
            r2 *= 10L;
            p--;
        }
        s->X->fromInt( r2);
        return;
    }
    while( p>0){
        result *= 10.0;
        p--;
    }
    while( p<0){
        result *= 0.1;
        p++;
    }
    s->X->fromReal( result);
}

void Func_Pow::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->Y->isEmpty()){
        s->X->fromInt( 1);
        return;
    }
    double result = 1.0;
    double x = s->X->toReal();
    if( s->Y->isReal()){
        result = pow( x, s->Y->toReal());
        s->X->fromReal( result);
        return;
    }
    int64_t p = s->Y->toInt();
    int64_t p2 = p;

    // Special point 0^0
    if( x==0.0 && p==0){
        s->X->fromInt(1);
        return;
    }
    if( x==0.0 && p<0){
        s->X->fromReal(INFINITY);
        return;
    }
    while( p>0){
        result *= x;
        p--;
    }
    x = 1.0 / x;
    while( p<0){
        result *= x;
        p++;
    }
    if (p2 <= 0 || s->X->isReal() || abs(result) > HUGE_POSITIVE_AS_REAL){
        s->X->fromReal(result);
        return;
    }
    // Try to keep as integer
    int64_t result2 = s->X->toInt();
    int64_t mul = result2;
    while (p2 > 1)
    {
        result2 *= mul;
        p2--;
    }
    s->X->fromInt(result2);
}

void Func_X2::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( x*x);
}

void Func_SQRT::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double x = s->X->toReal();
    if(s->setNegativeRootWarning( x)) x = -x;
    s->X->fromReal( sqrt(x));
}

void Func_1X::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( 1.0/x);
}
