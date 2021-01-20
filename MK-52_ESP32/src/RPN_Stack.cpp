//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "RPN_Stack.hpp"

#define __DEBUG

using namespace MK52_Interpreter;

const char _RPN_Stack_LabelX[] PROGMEM = "X:";
const char _RPN_Stack_LabelY[] PROGMEM = "Y:";
const char _RPN_Stack_LabelZ[] PROGMEM = "Z:";
const char _RPN_Stack_LabelT[] PROGMEM = "T:";

void RPN_Stack::init( void *components[]){
    #ifdef __DEBUG
    Serial.println("Started RPN Stack init...");
    #endif
    Bx = new UniversalValue(_stackValues);
    X = new UniversalValue(_stackValues+9);
    Y = new UniversalValue(_stackValues+18);
    Z = new UniversalValue(_stackValues+27);
    T = new UniversalValue(_stackValues+36);
    clearStack();
    char *ptr = _stackLabels;
    X_Label = ptr; ptr += SCREEN_COLS + 1;
    Y_Label = ptr; ptr += SCREEN_COLS + 1;
    Z_Label = ptr; ptr += SCREEN_COLS + 1;
    T_Label = ptr;
    resetStackLabels();
    setDMode( DMODE_DEGREES);
}

void RPN_Stack::resetStackLabels(){
    strcpy_P( X_Label, _RPN_Stack_LabelX);
    strcpy_P( Y_Label, _RPN_Stack_LabelY);
    strcpy_P( Z_Label, _RPN_Stack_LabelZ);
    strcpy_P( T_Label, _RPN_Stack_LabelT);
}

bool RPN_Stack::customStackLabels(){
    if( strcmp_P( X_Label, _RPN_Stack_LabelX) != 0) return true;
    if( strcmp_P( Y_Label, _RPN_Stack_LabelY) != 0) return true;
    if( strcmp_P( Z_Label, _RPN_Stack_LabelZ) != 0) return true;
    if( strcmp_P( T_Label, _RPN_Stack_LabelT) != 0) return true;
    return false;
}

//
// Resets stack to zero integers
//
void RPN_Stack::clearStack(){
    memset( _stackValues, 0, (RPN_STACK_SIZE+1)*9);
    for( int i=0; i<45; i+=9) _stackValues[i] = VALUE_TYPE_INTEGER;
}

//
// Sets stack labels
//
void RPN_Stack::setStackLabel(int n, char *text){
    char *ptr = _stackLabels + (SCREEN_COLS + 1) * n;
    strncpy( ptr, text, SCREEN_COLS);
    ptr[SCREEN_COLS] = 0;
}

void RPN_Stack::setStackLabel_P(int n, const char *text){
    char *ptr = _stackLabels + (SCREEN_COLS + 1) * n;
    strncpy_P( ptr, text, SCREEN_COLS);
    ptr[SCREEN_COLS] = 0;
}

void RPN_Stack::setDMode(uint8_t m){
    switch(m){
        case 1:
            _dMode = DMODE_RADIANS;
            strcpy_P( _dModeName, PSTR("RAD"));
            break;
        case 2:
            _dMode = DMODE_GRADS;
            strcpy_P( _dModeName, PSTR("GRD"));
            break;
        default:
            _dMode = DMODE_DEGREES;
            strcpy_P( _dModeName, PSTR("DEG"));
            break;
    }
} 

uint8_t RPN_Stack::flipDMode(){
    setDMode( _dMode+1);
    return _dMode;
} 

