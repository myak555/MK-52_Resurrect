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
    
    // #define FUNC_COMMENT            1
    _appendFunction( new Func_Comment());
    // #define FUNC_INCREMENT_PC       2
    _appendFunction( new Func_Increment_PC());
    // #define FUNC_DECREMENT_PC       3
    _appendFunction( new Func_Decrement_PC());
    // #define FUNC_INCREMENT_MC       4
    _appendFunction( new Func_Increment_MC());
    // #define FUNC_DECREMENT_MC       5
    _appendFunction( new Func_Decrement_MC());
    // #define FUNC_RESET_PC           6
    _appendFunction( new Func_Reset_PC());
    // #define FUNC_RESET_MC           7
    _appendFunction( new Func_Reset_MC());
    // #define FUNC_TOGGLE_DMOD        8
    _appendFunction( new Func_Toggle_DMOD());
    // #define FUNC_SET_DMOD_DEG       9
    _appendFunction( new Func_set_DMOD_DEG());
    // #define FUNC_SET_DMOD_RAD       10
    _appendFunction( new Func_set_DMOD_RAD());
    // #define FUNC_SET_DMOD_GRD       11
    _appendFunction( new Func_set_DMOD_GRD());
    // #define FUNC_NEGATE             12
    _appendFunction( new Func_Negate());
    // #define FUNC_ENTER              13
    _appendFunction( new Func_Enter());
    // #define FUNC_SWAP               14
    _appendFunction( new Func_Swap());
    // #define FUNC_PLUS               15
    _appendFunction( new Func_Plus());
    // #define FUNC_MINUS              16
    _appendFunction( new Func_Minus());
    // #define FUNC_MULTIPLY           17
    _appendFunction( new Func_Multiply());
    // #define FUNC_DIVIDE             18
    _appendFunction( new Func_Divide());
    // #define FUNC_CLEAR_X            19
    _appendFunction( new Func_Clear_X());
    // #define FUNC_SIN                20
    _appendFunction( new Func_Sin());
    // #define FUNC_ARCSIN             21
    _appendFunction( new Func_ArcSin());
    // #define FUNC_COS                22
    _appendFunction( new Func_Cos());
    // #define FUNC_ARCCOS             23
    _appendFunction( new Func_ArcCos());
    // #define FUNC_TG                 24
    _appendFunction( new Func_Tg());
    // #define FUNC_ARCTG              25
    _appendFunction( new Func_ArcTg());
    // #define FUNC_EXP                26
    _appendFunction( new Func_Exp());
    // #define FUNC_10X                27
    _appendFunction( new Func_10x());
    // #define FUNC_LG                 28
    _appendFunction( new Func_Lg());
    // #define FUNC_LN                 29
    _appendFunction( new Func_Ln());
    // #define FUNC_POW                30
    _appendFunction( new Func_Pow());
    // #define FUNC_LOG                31
    _appendFunction( new Func_Log());
    // #define FUNC_ROT                32
    _appendFunction( new Func_Rot());
    // #define FUNC_X2                 33
    _appendFunction( new Func_X2());
    // #define FUNC_1X                 34
    _appendFunction( new Func_1X());
    // #define FUNC_SQRT               35
    _appendFunction( new Func_SQRT());
    // #define FUNC_PI                 36
    _appendFunction( new Func_PI());
    // #define FUNC_EE                 37
    _appendFunction( new Func_EE());
    // #define FUNC_BX                 38
    _appendFunction( new Func_Bx());
    // #define FUNC_RAND               39
    _appendFunction( new Func_Rand());
    // #define FUNC_SEED               40
    _appendFunction( new Func_Seed());
    // #define FUNC_WHOLE              41
    _appendFunction( new Func_Whole());
    // #define FUNC_FRAC               42
    _appendFunction( new Func_Frac());
    // #define FUNC_MAX                43
    _appendFunction( new Func_Max());
    // #define FUNC_ABS                44
    _appendFunction( new Func_Abs());
    // #define FUNC_SIGN               45
    _appendFunction( new Func_Sign());
    // #define FUNC_AND                46
    _appendFunction( new Func_And());
    // #define FUNC_OR                 47
    _appendFunction( new Func_Or());
    // #define FUNC_XOR                48
    _appendFunction( new Func_Xor());
    // #define FUNC_NOT                49
    _appendFunction( new Func_Not());
    // #define FUNC_D2DM               50
    _appendFunction( new Func_D2DM());
    // #define FUNC_D2DMS              51
    _appendFunction( new Func_D2DMS());
    // #define FUNC_DM2D               52
    _appendFunction( new Func_DM2D());
    // #define FUNC_DMS2D              53
    _appendFunction( new Func_DMS2D());
    // #define FUNC_D2RAD              54
    _appendFunction( new Func_D2Rad());
    // #define FUNC_RAD2D              55
    _appendFunction( new Func_Rad2D());
    // #define FUNC_MM2IN              56
    _appendFunction( new Func_mm2in());
    // #define FUNC_IN2MM              57
    _appendFunction( new Func_in2mm());
    // #define FUNC_M2X                58
    _appendFunction( new Func_M2X());
    // #define FUNC_X2M                59
    _appendFunction( new Func_X2M());
    // #define FUNC_K_M2X              60
    _appendFunction( new Func_K_M2X());
    // #define FUNC_K_X2M              61
    _appendFunction( new Func_K_X2M());
    // #define FUNC_A_M2X              62
    _appendFunction( new Func_A_M2X());
    // #define FUNC_A_X2M              63
    _appendFunction( new Func_A_X2M());
    // #define FUNC_GOTO               64
    _appendFunction( new Func_GOTO());
    // #define FUNC_GOSUB              65
    _appendFunction( new Func_GOSUB());
    // #define FUNC_RETURN             66
    _appendFunction( new Func_Return());
    // #define FUNC_MEMSET             67
    _appendFunction( new Func_MemSet());
    // #define FUNC_MEMSWP             68
    _appendFunction( new Func_MemSwp());
    // #define FUNC_MEXTOX             69
    _appendFunction( new Func_MexToX());
    // #define FUNC_XTOMEX             70
    _appendFunction( new Func_XToMex());
    // #define FUNC_MEXTOR             71
    _appendFunction( new Func_MexToR());
    // #define FUNC_RTOMEX             72
    _appendFunction( new Func_RToMex());
    // #define FUNC_MEXCLR             73
    _appendFunction( new Func_MexClr());
    // #define FUNC_TOGGLE_EMOD        74
    _appendFunction( new Func_Toggle_EMOD());
    // #define FUNC_STOP               75
    _appendFunction( new Func_Stop());

    #ifdef __DEBUG
    Serial.print( _nfunctions);
    Serial.println(" functions defined");
    #endif
    return millis();
}

RPN_Function *RPN_Functions::getFunctionByID(int16_t id){
    if( id<0) return NULL;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkID( id)) continue;
        return pf;
    }
    return NULL;
}

RPN_Function *RPN_Functions::getFunctionByName(char *command){
    if( strlen(command)<=0) return NULL;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( command)) continue;
        return pf;
    }
    return NULL;
}

void RPN_Functions::execute( int16_t id, char *command){
    RPN_Function *pf = getFunctionByID( id);
    if( pf==NULL) return;
    pf->execute( _components, command);
}

void RPN_Functions::execute( char *command, bool pushNeeded){
    if( strlen(command)<=0) return;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( command)) continue;
        int operand = strlen_P( pf->Name());
        pf->execute( _components, command+operand);
        return;
    }
    // if the name is not found, it must be a number and should be placed to register X
    if( pushNeeded){
        Stack->storeBx();
        Stack->push();
    }
    Stack->X->fromString( command);
}

//
// Executes one step at project counter
//
void RPN_Functions::executeStep(){
    if(_atStop){
        _atStop = false;
        progMem->incrementCounter();
    }
    char *programLine = progMem->getCurrentLine();
    #ifdef __DEBUG
    Serial.print( "Execute: [");
    Serial.print( programLine);
    Serial.println( "]");
    #endif
    execute( programLine, true);
    if( _atStop)
        Stack->setStackLabel_P(0, PSTR("STOP Reached"));
    else
        progMem->incrementCounter();
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

bool RPN_Function::_startsWith(char *name, const char *keyword){
    int8_t ln = strlen_P( keyword);
    for( int8_t i=0; i<ln; i++, name++){
        if( !(*name)) return false;
        if( (char)pgm_read_byte( keyword+i) != *name) return false;
    }
    return true; // all letters are the same
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
#include "../functions/Func_Pow.h"
#include "../functions/Func_Log.h"
#include "../functions/Func_Rand.h"
#include "../functions/Func_Numb.h"
#include "../functions/Func_Logical.h"
#include "../functions/Func_Convert.h"
#include "../functions/Func_Memory.h"
#include "../functions/Func_Goto.h"
