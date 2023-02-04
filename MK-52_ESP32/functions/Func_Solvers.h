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

double ReduceAngle360( double x){
    x *= 0.5;
    while( x > __PI) x -= __PI;
    while( x < 0.0) x += __PI;
    return x * 2.0;
}

void Func_Polar::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();
    double valueXa = abs( s->X->toReal());
    double valueYa = abs( s->Y->toReal());
    s->pop(0); // store Bx, remove X
    if( valueXa < 1.0e-300 && valueYa < 1.0e-300){
        s->X->fromInt( 0);
        s->push();
        s->X->fromInt( 0);
        return;    
    }
    if( valueXa < 1.0e-300){
        s->OctantToX((valueY > 0.0)? 2:6);
        s->push();
        s->X->fromReal( valueYa);
        return;    
    }
    if( valueYa < 1.0e-300){
        s->OctantToX((valueX > 0.0)? 0:4);
        s->push();
        s->X->fromReal( valueXa);
        return;    
    }
    double teta = ReduceAngle360( atan2( valueY, valueX));
    s->RadianToX(teta);
    s->push();
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

void Func_Carte::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy2(components);
    if( s == NULL) return;
    double R = abs( s->X->toReal());
    s->pop(0); // store Bx, remove X
    int8_t oct = s->XtoOctant();
    switch(oct){
        case -1:
            break;
        case 0:
            s->X->fromInt( 0);
            s->push();
            s->X->fromReal( R);
            return;
        case 2:
            s->X->fromReal( R);
            s->push();
            s->X->fromInt( 0);
            return;
        case 4:
            s->X->fromInt( 0);
            s->push();
            s->X->fromReal( -R);
            return;
        case 6:
            s->X->fromReal( -R);
            s->push();
            s->X->fromInt( 0);
            return;
        default:
            break;
    }
    double result = s->XtoRadian();
    if(  result == -INFINITY || result == INFINITY){
        s->X->fromReal( NAN); 
        return;
    }
    if( s->X->isReal()) s->setTrigAccuracyWarning(result);
    double sinx = sin(result);
    double cosx = cos(result);
    s->X->fromReal( R * cosx);
    s->push();
    s->X->fromReal( R * sinx);
}

void Func_Inter::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy4(components);
    if( s == NULL) return;
    Register_Memory *rm = _RegMem(components);
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    double offset = s->Z->toReal();
    double x1 = s->Y->toReal();
    double dx = s->T->toReal() - s->Y->toReal();
    double dy = s->X->toReal() - s->Z->toReal();
    double dxa = abs(dx);
    double dya = abs(dy);
    s->storeBx();
    s->T->fromReal( dy);
    s->Z->fromReal( dx);
    if( dxa < 1.0e-300 && dya < 1.0e-300){
        s->Y->fromInt( 0); // X still contains the y2 value
        a.fromInt( 0); // gain
        b.fromReal( offset);
        return;
    }
    if( dxa < 1.0e-300){
        s->Y->fromReal( (dx*dy>=0)? INFINITY: -INFINITY);
        s->X->fromReal( NAN);
        // A and B are unchanged!
        return;
    }
    double gain = dy/dx;
    offset -= gain * x1;
    s->Y->fromReal( gain);
    s->X->fromReal( offset);
    a.fromReal( gain);
    b.fromReal( offset);
}

void Func_Poly1::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double result = s->X->toReal();
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    bool isInt = s->X->isInt() && a.isInt() && b.isInt();
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
    double myX = s->X->toReal();
    double result = myX;
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    UniversalValue c = UniversalValue(rm->_registerAddress(0xc));
    bool isInt = s->X->isInt() && a.isInt() && b.isInt() && c.isInt();
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
    double myX = s->X->toReal();
    double result = myX;
    UniversalValue a = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue b = UniversalValue(rm->_registerAddress(0xb));
    UniversalValue c = UniversalValue(rm->_registerAddress(0xc));
    UniversalValue d = UniversalValue(rm->_registerAddress(0xd));
    bool isInt = s->X->isInt() && a.isInt() && b.isInt() && c.isInt() && d.isInt();
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

//
// Zelen and Severo algorithm (1964) is 7.5e-8 accurate 
//
static double _PDF_ZelenSevero_( double x){
    bool negative = x<0;
    if( negative) x = -x;
    double t = 1.0/(1.0 + 0.2316419 * x);
    double tv = 0.5307027142649737 * t;
    tv = (tv - 0.7265760130580615) * t;
    tv = (tv + 0.7107068706716199) * t;
    tv = (tv - 0.14224836829963933) * t;
    tv = (tv + 0.1274147958962986) * t;
    tv *= exp( - 0.5 * x * x);
    if( negative) return tv;
    return 1.0-tv;
}

//
// Zelen and Severo inverse 1e-6 accurate 
//
static double _PROBIT_ZelenSevero_( double p){
    double x0 = -4.0;
    double x2 = 4.0;
    if( p < 0.5) x2 = 0.0;
    else x0 = 0.0;
    while( true){
        double x1 = (x0+x2) * 0.5;
        double pc = _PDF_ZelenSevero_(x1);
        if( abs( pc-p) < 0.0000001) return x1;
        if( p<pc) x2 = x1;
        else x0 = x1;
    }
}

void Func_Prob::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double p = s->X->toReal();
    if (p == 0.0){
        s->X->fromReal(0.5);
        return;
    }
    if (p <= -4.0){
        s->X->fromInt(0);
        return;
    }
    if (p >= 4.0){
        s->X->fromInt(1);
        return;
    }
    s->X->fromReal(_PDF_ZelenSevero_(p));
}

void Func_ProbAB::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double p = s->X->toReal();
    UniversalValue aUV = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue bUV = UniversalValue(rm->_registerAddress(0xb));
    double a = aUV.toReal();
    double b = bUV.toReal();
    if (a <= 0.0){
        s->X->fromInt(0);
        return;
    }
    p = (p - b) / a;
    if (p == 0.0){
        s->X->fromReal(0.5);
        return;
    }
    if (p <= -4.0){
        s->X->fromInt(0);
        return;
    }
    if (p >= 4.0){
        s->X->fromInt(1);
        return;
    }
    s->X->fromReal(_PDF_ZelenSevero_(p));
}

void Func_RProb::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double p = s->X->toReal();
    if (p == 0.5){
        s->X->fromReal(0);
        return;
    }
    if( p <0.0 || p>1.0){
        s->X->fromReal(NAN);
        return;
    }
    if (p <= 0.0){
        s->X->fromReal(-4.0);
        return;
    }
    if (p >= 1.0){
        s->X->fromReal(4.0);
        return;
    }
    double x = _PROBIT_ZelenSevero_( p);
    s->X->fromReal(x);
}

void Func_RProbAB::execute( void *components[], char *command){
    Register_Memory *rm = _RegMem(components);
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    double p = s->X->toReal();
    UniversalValue aUV = UniversalValue(rm->_registerAddress(0xa));
    UniversalValue bUV = UniversalValue(rm->_registerAddress(0xb));
    double a = aUV.toReal();
    double b = bUV.toReal();
    if (p == 0.5){
        s->X->fromReal(b);
        return;
    }
    if( p <0.0 || p>1.0){
        s->X->fromReal(NAN);
        return;
    }
    if (p <= 0.0){
        s->X->fromReal(b-4.0*a);
        return;
    }
    if (p >= 1.0){
        s->X->fromReal(b+4.0*a);
        return;
    }
    double x = _PROBIT_ZelenSevero_( p);
    s->X->fromReal(b + x * a);
}

void Func_Roots2::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy3(components);
    if( s == NULL) return;
    double a = s->Z->toReal();
    double b = s->Y->toReal();
    double c = s->X->toReal();
    double discr = b*b-4.0*a*c;
    s->Z->fromReal( discr);
    if( abs(a) < 1.0e-300 && abs(b) < 1.0e-300){
        s->Y->fromReal( NAN); // non-equation
        s->X->fromReal( NAN);
        return;
    }
    if( abs(a) < 1.0e-300){
        c /= -b;
        s->Y->fromReal( c); // linear equation
        s->X->fromReal( c);
        return;
    }
    if( discr < 0.0){
        s->Y->fromReal( NAN); // Complex roots
        s->X->fromReal( NAN);
        return;
    }
    if( abs(c) < 1.0e-300){
        s->Y->fromInt( 0); // zero root
        s->X->fromReal( -b/a);
        return;
    }
    if( abs(b) < 1.0e-300){
        c = sqrt(-c/a);
        s->Y->fromInt( c); // simple square
        s->X->fromReal( -c);
        return;
    }
    b = -b*0.5/a;
    discr = sqrt( 0.25*discr) / a;
    s->Y->fromReal( b+discr);
    s->X->fromReal( b-discr);
}

inline double solve_dnegative_( double p, double q){
    double po3 = -p/3.0;
    double res, sqrtpo3;
    if( p < 0.0){
        sqrtpo3 = -2.0 * sqrt(po3);
        res = (q<0)? -sqrtpo3: sqrtpo3;
        double arccoshpq = acosh(3.0*abs(q)/sqrtpo3/p);
        return res * cosh(arccoshpq / 3.0);
    }
    sqrtpo3 = 2.0 * sqrt(po3);
    res = -sqrtpo3;
    double arcsinhpq = asinh(3.0*q/sqrtpo3/p);
    return res * sinh(arcsinhpq / 3.0);
}

void Func_Roots3::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy4(components);
    if( s == NULL) return;
    double a = s->T->toReal();
    if( abs(a) < 1.0e-150){
        s->T->fromReal( NAN); // not a cubic equation
        s->Z->fromReal( NAN);
        s->Y->fromReal( NAN);
        s->X->fromReal( NAN);
        return;
    }
    double b = s->Z->toReal();
    double c = s->Y->toReal();
    double d = s->X->toReal();
    // convert to short form t^3+pt+q=0, x=t-b/(3a)
    double b3a = b / a / 3.0;
    double coa = c / a;
    double p = coa - b3a*b3a*3.0;
    double q = b3a * (2.0*b3a*b3a - coa) + d/a; 
    double discr = -4.0*p*p*p - 27.0*q*q;
    s->T->fromReal( discr);
    double discra = abs(discr);
    double pa = abs(p);
    if( discra < 1e-300 && pa < 1e-300){
        s->Z->fromReal( -b3a);
        s->Y->fromReal( -b3a);
        s->X->fromReal( -b3a);
        return;
    }
    double qop = q/p;
    if( discra < 1e-300){
        s->Z->fromReal( -1.5*qop-b3a);
        s->Y->fromReal( -1.5*qop-b3a);
        s->X->fromReal( 3.0*qop-b3a);
        return;
    }
    if( pa < 1e-300){
        p = pow( abs(q), 1.0/3.0);
        if(q<0) p = -p;
        s->Z->fromReal( p-b3a);
        s->Y->fromReal( p-b3a);
        s->X->fromReal( p-b3a);
        return;
    }
    if( discr < 0){
        p = solve_dnegative_( p, q);
        s->Z->fromReal( p-b3a);
        s->Y->fromReal( p-b3a);
        s->X->fromReal( p-b3a);
        return;
    }
    double po3 = -p/3.0;
    double sqrtpo3 = 2.0 * sqrt(po3);
    double arccospq = acos(3.0*q/sqrtpo3/p) / 3.0;
    s->Z->fromReal( sqrtpo3 * cos(arccospq) - b3a);
    s->Y->fromReal( sqrtpo3 * cos(arccospq - __PI/1.5) - b3a);
    s->X->fromReal( sqrtpo3 * cos(arccospq - __PI/0.75) - b3a);
}

void Func_Gauss::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy4(components);
    if( s == NULL) return;
    double peak = s->T->toReal();
    double sigma = s->Z->toReal();
    double x0 = s->Y->toReal();
    double x = s->X->toReal();
    s->storeBx();
    double result = x-x0;
    result = -sigma * result * result;
    result = peak * exp(result);

    if( abs(result) < 1.0e-300){
        s->X->fromInt( 0);
        return;
    }
    s->X->fromReal( result);
}
