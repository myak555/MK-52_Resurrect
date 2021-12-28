inline bool _checkResult( double result, bool isInt){
    if( !isInt) return false;
    if( result < HUGE_NEGATIVE_AS_REAL) return false;
    if( HUGE_POSITIVE_AS_REAL < result) return false;
    return true;
}

void Func_Radius::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = abs( s->X->toReal());
    double valueY = abs( s->Y->toReal());
    if( valueX < 1.0e-300){
        s->pop(0); // store Bx, remove X
        return;    
    }
    s->storeBx();
    if( valueY < 1.0e-300){
        s->pop(2); // remove Y
        return;    
    }
    if( valueX > valueY){
        valueY /= valueX;
        valueY *= valueY;
        s->X->fromReal( valueX * sqrt( valueY + 1.0));
        return;
    }
    valueX /= valueY;
    valueX *= valueX;
    s->X->fromReal( valueY * sqrt( valueX + 1.0));
}

void Func_Cath::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = abs( s->X->toReal());
    double valueY = abs( s->Y->toReal());
    if( valueX < 1.0e-300){
        s->pop(0); // store Bx, remove X
        return;    
    }
    s->storeBx();
    if( valueY < 1.0e-300){
        s->pop(2); // remove Y
        return;    
    }
    if( valueX > valueY){
        valueY /= valueX;
        valueY *= valueY;
        s->X->fromReal( valueX * sqrt( 1.0 - valueY));
        return;
    }
    valueX /= valueY;
    valueX *= valueX;
    s->X->fromReal( valueY * sqrt( 1.0 - valueX));
}

void Func_Poly1::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    bool isInt = s->X->isInt();
    double result = s->X->toReal();
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    result *= a.toReal();
    isInt = _checkResult( result, isInt);
    result += b.toReal();
    isInt = _checkResult( result, isInt);
    if(  !isInt){
        s->X->fromReal( result);
        return;
    }
    int64_t res = s->X->toInt();
    res *= a.toInt();
    res += b.toInt();
    s->X->fromInt( res);
}

void Func_Poly2::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    bool isInt = s->X->isInt();
    double myX = s->X->toReal();
    double result = myX;
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    UniversalValue c = UniversalValue(rm->_registerAddress(0xc));
    result *= a.toReal();
    isInt = _checkResult( result, isInt);
    result += b.toReal();
    isInt = _checkResult( result, isInt);
    result *= myX;
    isInt = _checkResult( result, isInt);
    result += c.toReal();
    isInt = _checkResult( result, isInt);
    if(  !isInt){
        s->X->fromReal( result);
        return;
    }
    int64_t mX = s->X->toInt();
    int64_t res = mX;
    res *= a.toInt();
    res += b.toInt();
    res *= mX;
    res += c.toInt();
    s->X->fromInt( res);
}

void Func_Poly3::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    bool isInt = s->X->isInt();
    double myX = s->X->toReal();
    double result = myX;
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    UniversalValue c = UniversalValue(rm->_registerAddress(0xc));
    UniversalValue d = UniversalValue(rm->_registerAddress(0xd));
    result *= a.toReal();
    isInt = _checkResult( result, isInt);
    result += b.toReal();
    isInt = _checkResult( result, isInt);
    result *= myX;
    isInt = _checkResult( result, isInt);
    result += c.toReal();
    isInt = _checkResult( result, isInt);
    result *= myX;
    isInt = _checkResult( result, isInt);
    result += d.toReal();
    isInt = _checkResult( result, isInt);
    if(  !isInt){
        s->X->fromReal( result);
        return;
    }
    int64_t mX = s->X->toInt();
    int64_t res = mX;
    res *= a.toInt();
    res += b.toInt();
    res *= mX;
    res += c.toInt();
    res *= mX;
    res += d.toInt();
    s->X->fromInt( res);
}
