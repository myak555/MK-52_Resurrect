//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "RPN_Functions.hpp"

#define __DEBUG
using namespace MK52_Interpreter;

//
// deal with a single NaN
//
RPN_Stack *RPN_Function::_dealWithClergy1(void *components[]){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    if( s->X->isEmpty()) return NULL;
    if( isnan(s->X->toReal())) return NULL;
    return s; // the rest of ariphmetics
}

//
// deal with a pair of NaNs
//
RPN_Stack *RPN_Function::_dealWithClergy2(void *components[]){
    RPN_Stack *s = (RPN_Stack *)components[COMPONENT_STACK];
    if( s->X->isEmpty() || s->Y->isEmpty()) return NULL;
    double valueX = s->X->toReal();
    double valueY = s->Y->toReal();

    if( isnan(valueX) && isnan(valueY)){
        s->pop(2); // remove Y, leave one NaN in X
        return NULL;
    }
    if( isnan(valueX)){
        s->pop(1); // remove X, leave Y
        return NULL;
    }
    if( isnan(valueY)){
        s->pop(2); // remove Y, leave X
        return NULL;
    }
    return s; // the rest of ariphmetics
}

bool RPN_Function::_startsWith(char *name, const char *keyword){
    int8_t ln = strlen_P( keyword);
    for( int8_t i=0; i<ln; i++, name++){
        if( !(*name)) return false;
        if( (char)pgm_read_byte( keyword+i) != *name) return false;
    }
    return true; // all letters are the same
}
