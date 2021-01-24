void Func_Sin::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    switch(s->XtoOctant()){
        case -1:
            break;
        case 0:
        case 4:
            s->X->fromInt( 0);
            return;
        case 2:
            s->X->fromInt( 1);
            return;
        case 6:
            s->X->fromInt( -1);
            return;
        default:
            break;
    }
    double result = s->XtoRadian();
    if(  result == -INFINITY || result == INFINITY){
        s->X->fromReal( NAN); 
        return;
    }
    s->setTrigAccuracyWarning(result);
    result = sin(result);
    s->X->fromReal( result);
}

void Func_ArcSin::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()){
        switch( s->X->toInt()){
            case -1:
                s->OctantToX(-2);
                return;
            case 0:
                s->OctantToX(0);
                return;
            case 1:
                s->OctantToX(-2);
                return;
            default:
                s->X->fromReal(NAN);
                return;
        }
        
    }
    double result = s->X->toReal();
    if( result < -1.0 || 1 < result){
        s->X->fromReal(NAN);
        return;
    }
    result = asin(result);
    s->RadianToX( result);
}

void Func_Cos::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    switch(s->XtoOctant()){
        case -1:
            break;
        case 0:
            s->X->fromInt( 1);
            return;
        case 2:
        case 6:
            s->X->fromInt( 0);
            return;
        case 4:
            s->X->fromInt( -1);
            return;
        default:
            break;
    }
    double result = s->XtoRadian();
    if(  result == -INFINITY || result == INFINITY){
        s->X->fromReal( NAN); 
        return;
    }
    s->setTrigAccuracyWarning(result);
    result = cos(result);
    s->X->fromReal( result);
}

void Func_ArcCos::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()){
        switch( s->X->toInt()){
            case -1:
                s->OctantToX(-4);
                return;
            case 0:
                s->OctantToX(2);
                return;
            case 1:
                s->OctantToX(0);
                return;
            default:
                s->X->fromReal(NAN);
                return;
        }
        
    }
    double result = s->X->toReal();
    if( result < -1.0 || 1 < result){
        s->X->fromReal(NAN);
        return;
    }
    result = acos(result);
    s->RadianToX( result);
}

void Func_Tg::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    switch(s->XtoOctant()){
        case -1:
            break;
        case 0:
        case 4:
            s->X->fromInt( 0);
            return;
        case 1:
        case 5:
            s->X->fromInt( 1);
            return;
        case 2:
            Serial.println();
            s->X->fromReal( INFINITY);
            return;
        case 3:
        case 7:
            s->X->fromInt( -1);
            return;
        case 6:
            s->X->fromReal( -INFINITY);
            return;
        default:
            break;
    }
    double result = s->XtoRadian();
    if(  result == -INFINITY || result == INFINITY){
        s->X->fromReal( NAN); 
        return;
    }
    s->setTrigAccuracyWarning(result);
    result = tan(result);
    s->X->fromReal( result);
}

void Func_ArcTg::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()){
        switch( s->X->toInt()){
            case -1:
                s->OctantToX(-1);
                return;
            case 0:
                s->OctantToX(0);
                return;
            case 1:
                s->OctantToX(1);
                return;
            default:
                break;
        }
        
    }
    double result = s->X->toReal();
    if(  result == -INFINITY){
        s->OctantToX(-2);
        return;
    }
    if(  result == INFINITY){
        s->OctantToX(2);
        return;
    }
    result = atan(result);
    s->RadianToX( result);
}

void Func_PI::execute( void *components[], char *command){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    s->storeBx();
    s->push();
    s->X->fromReal( __PI);
}

void Func_Rad2D::execute( void *components[], char *command){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( x * 5.729577951e1);
}

void Func_D2Rad::execute( void *components[], char *command){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( x * 1.745329252e-2);
    s->X->_checkRounding( 1.0e9);
}
