void Func_Sinh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if(  result == INFINITY){
        s->X->fromReal( INFINITY); 
        return;
    }
    if(  result == -INFINITY){
        s->X->fromReal( -INFINITY); 
        return;
    }
    result = sinh(result);
    s->X->fromReal( result);
}

void Func_ArSinh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if (result == -INFINITY){
        s->X->fromReal(-INFINITY);
        return;
    }
    if (result == INFINITY){
        s->X->fromReal(INFINITY);
        return;
    }
    result = sqrt(result*result + 1.0) + result;
    result = log(result);
    s->X->fromReal(result);
}

void Func_Cosh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if(  result == -INFINITY || result == INFINITY){
        s->X->fromReal( INFINITY); 
        return;
    }
    result = cosh(result);
    s->X->fromReal( result);
}

void Func_ArCosh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if (result < 1.0 || result == INFINITY){
        s->X->fromReal(NAN);
        return;
    }
    result = sqrt(result*result - 1.0) + result;
    result = log(result);
    s->X->fromReal(result);
}

void Func_Tgh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if(  result == INFINITY){
        s->X->fromReal( 1.0); 
        return;
    }
    if(  result == -INFINITY){
        s->X->fromReal( -1.0); 
        return;
    }
    result = tanh(result);
    s->X->fromReal( result);
}

void Func_ArTgh::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    if (result < -1.0 || 1.0 < result){
        s->X->fromReal(NAN);
        return;
    }
    if (result == -1.0){
        s->X->fromReal( -INFINITY);
        return;
    }
    if (result == 1.0){
        s->X->fromReal(INFINITY);
        return;
    }
    result = (1.0 + result) / (1.0 - result);
    result = log(result) * 0.5;
    s->X->fromReal(result);
}
