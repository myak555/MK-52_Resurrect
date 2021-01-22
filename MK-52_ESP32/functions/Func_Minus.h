void Func_Minus::execute( void *components[], char *command)
{
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
