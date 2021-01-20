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
}

//uint8_t UniversalValue::fromString( char *text);

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
