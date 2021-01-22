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

#include <math.h>
#include "../functions/functions.hpp"

//
// Inits the calculator program memory
//
unsigned long RPN_Functions::init( void *components[]) {
    _components = components;
    Stack = (RPN_Stack *)components[COMPONENT_STACK];
    progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    
    _appendFunction( new Func_Comment());
    _appendFunction( new Func_Increment_PC());
    _appendFunction( new Func_Decrement_PC());
    _appendFunction( new Func_Increment_MC());
    _appendFunction( new Func_Decrement_MC());
    _appendFunction( new Func_Reset_PC());
    _appendFunction( new Func_Reset_MC());
    _appendFunction( new Func_Toggle_DMOD());
    _appendFunction( new Func_set_DMOD_DEG());
    _appendFunction( new Func_set_DMOD_RAD());
    _appendFunction( new Func_set_DMOD_GRD());
    _appendFunction( new Func_Negate());
    _appendFunction( new Func_Enter());
    _appendFunction( new Func_Swap());
    _appendFunction( new Func_Plus());
    _appendFunction( new Func_Minus());
    _appendFunction( new Func_Multiply());
    _appendFunction( new Func_Divide());
    _appendFunction( new Func_Clear_X());
    _appendFunction( new Func_Sin());

    #ifdef __DEBUG
    Serial.print( _nfunctions);
    Serial.println(" functions defined");
    #endif
    return millis();
}

void RPN_Functions::execute( int16_t id){
    if( id<0) return;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkID( id)) continue;
        pf->execute( _components);
        break;
    }
}

void RPN_Functions::execute( char *s){
    if( strlen(s)<=0) return;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( s)) continue;
        pf->execute( _components, s);
        return;
    }
    // if the name is not found, it must be a number and should be placed to register X
    Stack->X->fromString( s);
}

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

void RPN_Functions::_appendFunction( RPN_Function *f){
    if( _nfunctions >= MK52_NFUNCTIONS) return;
    _functions[ _nfunctions++] = f;
}

#include "../functions/Func_Divide.h"
#include "../functions/Func_Minus.h"
#include "../functions/Func_Multiply.h"
#include "../functions/Func_Negate.h"
#include "../functions/Func_Plus.h"
#include "../functions/Func_Trig.h"
