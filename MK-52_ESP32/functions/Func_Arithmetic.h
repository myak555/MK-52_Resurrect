void Func_Negate::execute( void *components[], char *command){
    RPN_Stack *s = _Stack(components);
    if( s->X->isEmpty()) return;
    if( s->X->isInt()){
        uint64_t *ptrI = s->X->_asIntPtr();
        *ptrI = -(*ptrI);
        return;
    }
    double *ptrD = s->X->_asRealPtr();
    double value = *ptrD;
    if( isnan(value)) return;
    if( value == -INFINITY){
        *ptrD = INFINITY;
        return;
    }
    if( value == INFINITY){
        *ptrD = -INFINITY;
        return;
    }
    *ptrD = -(*ptrD);
}

void Func_Plus::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    double result = valueY + valueX;
    if(  result < HUGE_NEGATIVE_AS_REAL || HUGE_POSITIVE_AS_REAL < result || s->X->isReal() || s->Y->isReal() ){
        s->pop(0); // store Bx, remove X
        s->X->fromReal( result); 
        return;
    }
    int64_t res = s->Y->toInt() + s->X->toInt();
    s->pop(0); // store Bx, remove X
    s->X->fromInt( res);
}

void Func_Minus::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    double result = valueY - valueX;
    if(  result < HUGE_NEGATIVE_AS_REAL || HUGE_POSITIVE_AS_REAL < result || s->X->isReal() || s->Y->isReal() ){
        s->pop(0); // store Bx, remove X
        s->X->fromReal( result); 
        return;
    }
    int64_t res = s->Y->toInt() - s->X->toInt();
    s->pop(0); // store Bx, remove X
    s->X->fromInt( res);
}

void Func_Multiply::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    double result = valueY * valueX;
    if(  result < HUGE_NEGATIVE_AS_REAL || HUGE_POSITIVE_AS_REAL < result || s->X->isReal() || s->Y->isReal() ){
        s->pop(0); // store Bx, remove X
        s->X->fromReal( result); 
        return;
    }
    int64_t res = s->Y->toInt() * s->X->toInt();
    s->pop(0); // store Bx, remove X
    s->X->fromInt( res);
}

void Func_Divide::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    double result = valueY / valueX;
    if(  isnan(result) || result == -INFINITY || result == INFINITY || s->X->isReal() || s->Y->isReal()){
        s->pop(0); // store Bx, remove X
        s->X->fromReal( result); 
        return;
    }
    int64_t frac = s->Y->toInt() % s->X->toInt();
    int64_t res = s->Y->toInt() / s->X->toInt();
    s->pop(0); // store Bx, remove X
    if( frac == 0) s->X->fromInt( res); // exact division
    else s->X->fromReal( result);
}
