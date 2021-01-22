void Func_Negate::execute( void *components[], char *command)
{
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
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
