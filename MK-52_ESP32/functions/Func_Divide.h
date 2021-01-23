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
