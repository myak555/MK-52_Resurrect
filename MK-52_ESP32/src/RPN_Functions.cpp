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

void RPN_Functions::_appendFunction( RPN_Function *f){
    if( _nfunctions >= MK52_NFUNCTIONS) return;
    _functions[ _nfunctions++] = f;
}
