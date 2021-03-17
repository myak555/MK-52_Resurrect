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
const char *_RPN_Stack_Labels[] PROGMEM = {
    _RPN_Stack_LabelX,
    _RPN_Stack_LabelY,
    _RPN_Stack_LabelZ,
    _RPN_Stack_LabelT};
const char _DMODE_Label0[] PROGMEM = "DEG";
const char _DMODE_Label1[] PROGMEM = "RAD";
const char _DMODE_Label2[] PROGMEM = "GRD";
const char *_DMODE_Labels[] PROGMEM = {
    _DMODE_Label0,
    _DMODE_Label1,
    _DMODE_Label2};

const char _RPN_Stack_TrigAccuracy[] PROGMEM = "Warn: Trig Accuracy";
const char _RPN_Stack_ComplexRoot[] PROGMEM = "Warn: Complex";

static double _DMODE_ConversionsToRadian[] = {1.7453292519943295e-2, 1.0, 1.5707963267948967e-2};
static double _DMODE_ConversionsFromRadian[] = {57.29577951308232, 1.0, 63.66197723675813};

void RPN_Stack::init( void *components[]){
    Bx = new UniversalValue(_stackValues);
    X = new UniversalValue(_stackValues+9);
    Y = new UniversalValue(_stackValues+18);
    Z = new UniversalValue(_stackValues+27);
    T = new UniversalValue(_stackValues+36);
    clear();
    char *ptr = _stackLabels;
    X_Label = ptr; ptr += SCREEN_COLS + 1;
    Y_Label = ptr; ptr += SCREEN_COLS + 1;
    Z_Label = ptr; ptr += SCREEN_COLS + 1;
    T_Label = ptr;
    resetLabels();
    setDMode( DMODE_DEGREES);
    #ifdef __DEBUG
    Serial.print("Stack init with: ");
    Serial.println( getDModeName());
    Serial.print("Labels are: ");
    Serial.println( customLabels()? "CUSTOM": "STANDARD");
    #endif
}

void RPN_Stack::resetLabels(){
    strcpy_P( X_Label, _RPN_Stack_LabelX);
    strcpy_P( Y_Label, _RPN_Stack_LabelY);
    strcpy_P( Z_Label, _RPN_Stack_LabelZ);
    strcpy_P( T_Label, _RPN_Stack_LabelT);
}

bool RPN_Stack::customLabels(){
    if( !UniversalValue::_identicalTo_P( X_Label, _RPN_Stack_LabelX)) return true;
    if( !UniversalValue::_identicalTo_P( Y_Label, _RPN_Stack_LabelY)) return true;
    if( !UniversalValue::_identicalTo_P( Z_Label, _RPN_Stack_LabelZ)) return true;
    if( !UniversalValue::_identicalTo_P( T_Label, _RPN_Stack_LabelT)) return true;
    return false;
}

//
// Resets stack to zero integers
//
void RPN_Stack::clear(){
    memset( _stackValues, 0, (RPN_STACK_SIZE + 1)*9);
    for( int i=0; i<(RPN_STACK_SIZE + 1)*9; i+=9) _stackValues[i] = VALUE_TYPE_INTEGER;
}

//
// Sets stack labels
//
void RPN_Stack::setLabel(int n, char *text){
    if( text[0] == 0){
        setLabel_P( n, _RPN_Stack_Labels[n]);
        return;
    }
    char *ptr = _stackLabels + (SCREEN_COLS + 1) * n;
    strncpy( ptr, text, SCREEN_COLS);
    ptr[SCREEN_COLS] = 0;
}

void RPN_Stack::setLabel_P(int n, const char *text){
    char *ptr = _stackLabels + (SCREEN_COLS + 1) * n;
    strncpy_P( ptr, text, SCREEN_COLS);
    ptr[SCREEN_COLS] = 0;
}

void RPN_Stack::setDMode(uint8_t m){
    _dMode = (m>2)? 0: m;
    strcpy_P( _dModeName, _DMODE_Labels[_dMode]);
} 

uint8_t RPN_Stack::toggleAngleMode(){
    setDMode( _dMode+1);
    return _dMode;
} 

void RPN_Stack::push( uint16_t start){
    if( start >= RPN_STACK_SIZE) return;
    uint16_t toMove = (RPN_STACK_SIZE - start) * 9;
    start *= 9;
    memmove( _stackValues+start+9, _stackValues+start, toMove);    
}

void RPN_Stack::pop( uint16_t start){
    if( start >= RPN_STACK_SIZE) return;
    uint16_t toMove = (RPN_STACK_SIZE - start) * 9;
    start *= 9;
    memmove( _stackValues+start, _stackValues+start+9, toMove);    
}

void RPN_Stack::storeBx(){
    memcpy(_stackValues, _stackValues+9, 9);    
}

void RPN_Stack::swap(){
    memcpy(_stackValues, _stackValues+9, 9);   
    memcpy(_stackValues+9, _stackValues+18, 9);   
    memcpy(_stackValues+18, _stackValues, 9);   
}

void RPN_Stack::rotate(){
    pop( 0);
    memcpy( _stackValues + RPN_STACK_SIZE*9, _stackValues, 9);
}

double RPN_Stack::XtoRadian(){
    double tmp = X->toReal();
    if( X->isInt()){
        if( _dMode == DMODE_DEGREES) tmp = (double)(X->toInt() % 360);
        if( _dMode == DMODE_DEGREES) tmp = (double)(X->toInt() % 400);
    }
    return tmp * _DMODE_ConversionsToRadian[_dMode];
}

int8_t RPN_Stack::XtoOctant(){
    if( _dMode == DMODE_RADIANS) return -1;
    if( X->isEmpty()) return -1;
    if( X->isReal()) return -1;
    int64_t octant = _dMode ? 50: 45;
    int64_t result = X->toInt();
    if( result % octant != 0) return -1;
    result /= octant;
    result %= 8;
    if( result < 0) result += 8;
    #ifdef __DEBUG
    Serial.print("Octant found: ");
    Serial.println((int)result);
    #endif
    return (int8_t)result;
}

void RPN_Stack::RadianToX(double value){
    X->fromReal( value * _DMODE_ConversionsFromRadian[_dMode]);
    // in case of degrees and grads, need to round-up higher, to account for the Radian conversion
    if( _dMode != DMODE_RADIANS) X->_checkRounding( __ROUNDING_ACCURACY * 0.01);
}

void RPN_Stack::OctantToX(int8_t value){
    switch( _dMode){
        case DMODE_DEGREES:
            X->fromInt( value * 45);
            break;
        case DMODE_GRADS:
            X->fromInt( value * 50);
            break;
        default:
            X->fromReal( __PI4 * value);
            break;
    }
}

//
// value in radians
// if outside of -1e12 to 1e12 range, perioodic functions lose precision
//
void RPN_Stack::setTrigAccuracyWarning( double value){
    if( -1e12 <= value && value <= 1e12) return;
    setLabel_P(0, _RPN_Stack_TrigAccuracy);
}

bool RPN_Stack::setNegativeRootWarning( double value){
    if( value >= 0) return false;
    setLabel_P(0, _RPN_Stack_ComplexRoot);
    return true;
}
