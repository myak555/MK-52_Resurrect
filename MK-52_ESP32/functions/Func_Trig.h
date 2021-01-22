void Func_Sin::execute( void *components[], char *command)
{
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
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
    result = sin(result);
    s->X->fromReal( result);
}
