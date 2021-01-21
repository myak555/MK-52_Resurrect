//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "UniversalValue.hpp"

const char _standard_DoubleFormat[] PROGMEM = "%f";  
const char _standard_FullPrecision[] PROGMEM = "%13.11f";  
const char _standard_ExponentFormat[] PROGMEM = "%+04d";  
const char _standard_Error[] PROGMEM = "Error";  
const char _standard_MinusInfinity[] PROGMEM = "-Inf";  
const char _standard_PlusInfinity[] PROGMEM = "+Inf";  
const char _standard_Decimals[] PROGMEM = "0123456789";  

using namespace MK52_Interpreter;

UniversalValue::UniversalValue( uint8_t *location){
    _ptr = location;
}

void UniversalValue::fromEmpty(){
    if(!_ptr) return;
    memset( _ptr, 0, 9);
}

void UniversalValue::fromInt(int64_t value){
    if(!_ptr) return;
    *_ptr = VALUE_TYPE_INTEGER;
    memcpy( _ptr+1, &value, sizeof(int64_t));
}

void UniversalValue::fromReal(double value){
    if(!_ptr) return;
    *_ptr = VALUE_TYPE_DOUBLE;
    memcpy( _ptr+1, &value, sizeof(double));
    _checkRounding();
}

uint8_t UniversalValue::fromString( char *text){
    char *ptr = text;
    while( *ptr == ' ') ptr++;
    bool positive = true;
    if( *ptr == '+') ptr++;
    if( *ptr == '-'){
        ptr++;
        positive = false;
    }
    int ln = strlen( ptr);
    if( ln <= 0){
        fromEmpty();
        return getType();
    }
    char *ptrE = strchr( text, 'E');
    if( ptrE == NULL) ptrE = strchr( text, 'e');
    char *ptrDecimal = strchr( text, '.');
    if( ptrE == NULL && ptrDecimal == NULL){ // no decimal or e - whole number
        fromInt( _recoverInt64( text));        
        return getType();
    }
    double result = 0.0;
    int64_t exponent = 0;
    if( ptrE == NULL && ptrDecimal != NULL){ // has decimal, but no e
        result = (double)_recoverInt64( ptr);
        result += _recoverDecimal( ptrDecimal+1);
        fromReal( positive? result: -result);        
        return getType();
    }
    // has e
    result = (double)_recoverInt64( ptr);
    if( ptrDecimal != NULL) result += _recoverDecimal(ptrDecimal+1); 
    exponent = _recoverInt64( ptrE+1);
    if( exponent < -300){
        fromInt( 0);        
        return getType();
    }
    if( exponent > 300){ // infinity
        fromReal( positive? 1.0/0.0: -1.0/0.0);        
        return getType();
    }
    int ex2 = (int)exponent;
    while( ex2 > 0){
        result *= 10.0;
        ex2--;
    }
    while( ex2 < 0){
        result *= 0.1;
        ex2++;
    }
    fromReal( positive? result: -result);        
    return getType();
}

int64_t UniversalValue::toInt(){
    if(!_ptr) return 0L;
    if(isEmpty()) return 0L;
    if(isInt()) return *_asIntPtr();
    double tmp = *_asRealPtr();
    if( tmp > HUGE_POSITIVE_AS_REAL) return HUGE_POSITIVE_INTEGER; 
    if( tmp < HUGE_NEGATIVE_AS_REAL) return HUGE_NEGATIVE_INTEGER;
    return (int64_t)tmp; 
}

double UniversalValue::toReal(){
    if(!_ptr) return 0.0;
    if(isEmpty()) return 0.0;
    if(isReal()) return *_asRealPtr();
    int64_t tmp = *_asIntPtr();
    return (double)tmp; 
}

char *UniversalValue::toString( char *text){
    if(!_ptr){
        sprintf_P( text, _standard_Error);
        return text;
    }
    if(isEmpty()){
        text[0] = 0;
        return text;
    }
    if(isInt()) return _composeInt64( text, toInt());
    return _composeDouble( text, toReal());
}

//
// Converts double number
//
char *UniversalValue::_composeDouble(char *text, double value){ 
    if( isnan(value)){
        sprintf_P(text, _standard_Error);
        return text;
    }
    if( value == -INFINITY){
        sprintf_P(text, _standard_MinusInfinity);
        return text;
    }
    if( value == INFINITY){
        sprintf_P(text, _standard_PlusInfinity);
        return text;
    }
    bool negative = false;
    if( value < 0.0){
        negative = true;
        value = -value;
    } 
    if( 0.1 <= value && value < 1.e12){
        snprintf_P(text, 29, _standard_DoubleFormat, negative? -value: value);
        text[29] = 0;
        return text;
    }
    int16_t exponent = 0;
    while(value<1.0){
        exponent--;
        value *= 10.0;
    }
    while(value>=10.0){
        exponent++;
        value *= 0.1;
    }
    snprintf_P(text, 24, _standard_FullPrecision, negative? -value: value);
    text[24] = 0;
    int16_t i = strlen(text);
    snprintf_P(text+i, 29-i, _standard_ExponentFormat, exponent);
    text[29] = 0; // safety zero
    return text;
}

//
// Converts int
//
char *UniversalValue::_composeInt64(char *text, int64_t value){ 
    if( value > HUGE_POSITIVE_INTEGER){
        snprintf_P(text, 29, _standard_MinusInfinity);
        return text;
    }
    if( value < HUGE_NEGATIVE_INTEGER){
        snprintf_P(text, 29, _standard_PlusInfinity);
        return text;
    }
    // my own version of lltoa
    // return lltoa( value, text, 10);
    char *ptr = text;
    if( value == 0L){
        *ptr++ = '0';
        *ptr = 0;
        return text;
    }
    if( value < 0){
        *ptr++ = '-';
        value = -value;
    }
    int64_t mult = 1000000000000000000L;
    while( mult && !(value / mult)) mult /= 10;
    while( mult){
        *ptr++ = '0' + (int8_t)(value / mult);
        value %= mult;
        mult /= 10;
    }
    *ptr = 0;
    return text;
}


//
// Converts int
//
double UniversalValue::_recoverDecimal(char *ptr){
    double tmp = 0.0;
    double frac = 0.1;
    while( *ptr){
        if( !_isDecimal( *ptr)) return tmp;
        tmp += (*ptr - '0') * frac;
        frac *= 0.1;
        if( frac < 1e-12) return tmp;
        ptr++;
    }
    return tmp;
}

//
// Converts int
//
int64_t UniversalValue::_recoverInt64(char *ptr){
    bool positive = true;
    if( *ptr == '-'){
        ptr++;
        positive = false;
    }
    if( *ptr == '+') ptr++;
    int64_t tmp = 0;
    while( *ptr){
        if( !_isDecimal( *ptr)) return positive? tmp: -tmp;
        tmp *= 10L;
        tmp += *ptr - '0';
        if( tmp > HUGE_POSITIVE_INTEGER) return positive? HUGE_POSITIVE_INTEGER: HUGE_NEGATIVE_INTEGER;
        ptr++;
    }
    return positive? tmp: -tmp;
}

void UniversalValue::_checkRounding(){
    if( !isReal()) return;
    double value = *_asRealPtr();
    if( isnan(value)) return;
    if( value == -INFINITY) return;
    if( value == INFINITY) return;
    bool positive = true;
    if( value<0.0){
        positive = false;
        value = -value;
    }    
    int exponent = 0;
    while( value >= 10.0){
        exponent++;
        value *= 0.1;
    }
    while( value < 1.0){
        exponent--;
        value *= 10.0;
    }
    // at this point, value is normalized to 1 <= x < 10.0
    // we check, if the decimal part is less than 1e-12
    double fl = floor(value);
    if( value - fl >= 1.0e-12) return;
    while( exponent > 0){
        exponent--;
        fl *= 10.0;
    }
    while( exponent < 0){
        exponent++;
        fl *= 0.1;
    }
    if( fl < HUGE_POSITIVE_INTEGER){
        fromInt( positive? (int64_t)fl: -(int64_t)fl);
        return;
    }
    fromReal( positive? fl: -fl);
}

bool UniversalValue::_isDecimal(char c){
    const char *ptr = _standard_Decimals;
    for( uint8_t i=0; i<10; i++)
        if( c == (char)pgm_read_byte(ptr++)) return true;
    return false;
}

