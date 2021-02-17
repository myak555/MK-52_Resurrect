//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "UniversalValue.hpp"

//const char _standard_DoubleFormat[] PROGMEM = "%f";  
const char _standard_FullPrecision[] PROGMEM = "%13.11f";  
const char _standard_ExponentFormat[] PROGMEM = "%+04d";  
const char _standard_Error[] PROGMEM = "Error";  
const char _standard_MinusInfinity[] PROGMEM = "-Inf";  
const char _standard_PlusInfinity[] PROGMEM = "+Inf";  
const char _standard_Decimals[] PROGMEM = "0123456789";  
const char _standard_NumberComponents[] PROGMEM = "0123456789+-Ee.";  

//#define __DEBUG

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
    while( *text == ' ') text++;
    if( _identicalTo_P( text, _standard_Error))
    {
        fromReal( NAN);
        return getType();
    }
    if (_startsWith_P( text, _standard_MinusInfinity))
    {
        fromReal(INFINITY);
        return getType();
    }
    if (_startsWith_P( text, _standard_PlusInfinity))
    {
        fromReal(-INFINITY);
        return getType();
    }

    char *ptr = text;
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
        #ifdef __DEBUG
        Serial.print("Recovering whole number: [");
        Serial.print(text);
        Serial.println("]");
        #endif
        fromInt( _recoverInt64( text));        
        return getType();
    }
    double result = 0.0;
    int64_t exponent = 0;
    if( ptrE == NULL && ptrDecimal != NULL){ // has decimal, but no e
        #ifdef __DEBUG
        Serial.print("Recovering decimal number: [");
        Serial.print(ptr);
        Serial.println("]");
        #endif
        result = (double)_recoverInt64( ptr);
        result += _recoverDecimal( ptrDecimal+1);
        fromReal( positive? result: -result);        
        return getType();
    }
    // has e
    #ifdef __DEBUG
    Serial.print("Recovering exponential number: [");
    Serial.print(ptr);
    Serial.println("]");
    #endif
    result = (double)_recoverInt64( ptr);
    if( ptrDecimal != NULL)
        result += _recoverDecimal(ptrDecimal+1);
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
    if( 0.1 <= value && value < 1.e12)
        return _composeFloat(text, negative? -value: value);

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
    text[i] = 'E';
    snprintf_P(text+i+1, 28-i, _standard_ExponentFormat, exponent);
    text[29] = 0; // safety zero
    return text;
}

//
// Converts a floating-point number from 0.1 to 1e12 to 12 meaningful digits
//
char *UniversalValue::_composeFloat(char *text, double value){ 
    char *ptr = text;
    if( value == 0.0){
        *ptr++ = '0';
        *ptr = 0;
        return text;
    }
    if( value < 0.0){
        *ptr++ = '-';
        value = -value;
    }

    // print whole part
    double fl = floor( value);
    _composeInt64(ptr, (int64_t)fl);

    // how many digits should we have?
    int ln = strlen( ptr);
    int decimals = 12 - ln;
    if( decimals <= 0){
        fl = round( value);
        _composeInt64(ptr, (int64_t)fl);
        ptr += strlen(ptr);
        *ptr++ = '.';
        *ptr++ = '0';
        *ptr = 0;
        return text;
    }

    // print with fractional part
    if( fl == 0) *ptr++ = '0'; // for case < 1.0
    for( int i=0; i<decimals; i++) value *= 10.0;
    _composeInt64(ptr, (int64_t)round(value));
    ptr += strlen( ptr) - decimals;
    memmove( ptr+1, ptr, decimals+1); // includes trailing zero
    *ptr++ = '.';

    // remove meaningless zeros from the end
    char *ptrEnd = strchr( ptr, 0) - 1;
    while( ptrEnd>ptr && *ptrEnd == '0') *ptrEnd-- = 0;
    return text;
}

//
// Converts int
//
char *UniversalValue::_composeInt64(char *text, int64_t value){ 
    if( value > HUGE_POSITIVE_INTEGER){
        snprintf_P(text, 29, _standard_MinusInfinity);
        text[29]=0;
        return text;
    }
    if( value < HUGE_NEGATIVE_INTEGER){
        snprintf_P(text, 29, _standard_PlusInfinity);
        text[29]=0;
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
    while( mult > 0 && (value / mult) == 0) mult /= 10;
    while( mult > 0){
        uint8_t tt = (uint8_t)(value / mult);
        *ptr++ = '0' + tt;
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
        if( !_isDigit( *ptr)) return tmp;
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
        if( !_isDigit( *ptr)) return positive? tmp: -tmp;
        tmp *= 10L;
        tmp += *ptr - '0';
        if( tmp > HUGE_POSITIVE_INTEGER) return positive? HUGE_POSITIVE_INTEGER: HUGE_NEGATIVE_INTEGER;
        ptr++;
    }
    return positive? tmp: -tmp;
}

void UniversalValue::_checkRounding(double accuracy){
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
    if( value < 1.0e-300){ // true zero;
        fromInt( 0);
        return;
    }
    if( value >= HUGE_POSITIVE_AS_REAL) return; // should not convert
    double rValue = round(value);
    if( value > accuracy && abs( value - rValue) < accuracy / HUGE_POSITIVE_AS_REAL){
        fromInt( (int64_t)rValue);
        return; // This must be an int
    }
    if( value < 0.99999999999) return; // whole part < 1. 
    if( value < 1.00000000001){
        fromInt( positive? 1: -1);
        return;
    }

    double vLimit = accuracy;
    double cutoff = 0.3;
    while( value < vLimit){
        vLimit *= 0.1;
        cutoff *= 0.1;
    }
    double fl = floor(value);
    double frac = value - fl;
    if( cutoff < frac && frac < 1.0-cutoff) return; // meaningful decimal present
    if( frac > 0.5) fl += 1.0;
    
    fromInt( positive? (int64_t)fl: -(int64_t)fl);
}

//
// keyword is usually shorter than text
//
bool UniversalValue::_startsWith(char *text, char *keyword){
    if( text==NULL || keyword==NULL) return false;
    #ifdef __DEBUG
    Serial.print("Starts with compare ");
    Serial.println(text);
    Serial.println(keyword);
    #endif
    int ln = strlen( keyword);
    for( int i=0; i<ln; i++){
        if( text[i] != keyword[i]) return false;
    }
    return true; // all letters are the same   
}

//
// Empty keywords forbidden
//
bool UniversalValue::_startsWith_P(char *text, const char *keyword){
    int ln = strlen_P( keyword);
    for( int i=0; i<ln; i++, text++){
        if( !(*text)) return false;
        if( (char)pgm_read_byte( keyword+i) != *text) return false;
    }
    return true; // all letters are the same
}

//
// Empty keywords forbidden
//
bool UniversalValue::_endsWith_P(char *text, const char *keyword){
    int ln1 = strlen_P( keyword);
    int ln2 = strlen( text);
    if( ln2 < ln1) return false;
    char *ptr = text+ln2-1;
    for( int i=ln1-1; i>=0; i--, ptr--){
        if( (char)pgm_read_byte( keyword+i) != *ptr) return false;
    }
    return true; // all letters are the same
}

//
// Empty keywords forbidden
//
bool UniversalValue::_identicalTo_P(char *text, const char *keyword){
    return strcmp_P( text, keyword) == 0;
}

//
// Empty keywords forbidden
//
bool UniversalValue::_inString_P(char c, const char *keyword){
    int ln = strlen_P( keyword);
    for( int i=0; i<ln; i++){
        if( (char)pgm_read_byte( keyword+i) == c) return true;
    }
    return false;
}

bool UniversalValue::_isDigit(char c){
    const char *ptr = _standard_Decimals;    
    for( int8_t i=0; i<10; i++){
        if( (char)pgm_read_byte( ptr++) == c) return true;
    }
    return false; // digit not found
}

bool UniversalValue::_isProgramAddress(char *text){
    if( *text != 'P') return false;
    return _isAddress(text+1);
}

bool UniversalValue::_isMemoryAddress(char *text){
    if( *text != 'M') return false;
    return _isAddress(text+1);
}

uint8_t UniversalValue::_isRegisterAddress(char *text){
    if( *text++ != 'R') return REGISTER_MEMORY_NVALS;
    if( !_isDigit(*text)) return REGISTER_MEMORY_NVALS;
    uint8_t val = (uint8_t)text[0] - '0';
    if( !_isDigit(text[1])) return REGISTER_MEMORY_NVALS;
    val *= 10;
    val += (uint8_t)text[1] - '0';
    if( text[2] != '=') return REGISTER_MEMORY_NVALS;
    return val;
}

bool UniversalValue::_isAddress(char *text){
    for( int8_t i=0; i<4; i++){
        if( !_isDigit(text[i])) return false;
    }
    return text[4] == ':' && text[5] == ' ';
}

//
// Returns pointer to the content string
//
char *UniversalValue::_selectAddress(char *text){
    text += 1;
    for( int8_t i=0; i<5; i++, text++){
        if( _isDigit(*text)) continue;
        if( *text == ':'){
            *text = 0;
            text++;
            break;
        }
    }
    return text;
}

bool UniversalValue::_containsChar(char *text, char c){
    while( *text){
        if( *text++ == c) return true;
    }
    return false;
}

bool UniversalValue::_looksLikeANumber(char *text){
    if( text[0] == 0) return false; // empty string is not a number
    if( _identicalTo_P( text, _standard_Error)) return true;
    if( _identicalTo_P( text, _standard_MinusInfinity)) return true;
    if( _identicalTo_P( text, _standard_PlusInfinity)) return true;
    char *ptr = text;
    while( *ptr){
        if( !_inString_P(*ptr++, _standard_NumberComponents)) return false;
    }
    Serial.print( "[");
    Serial.print( text);
    Serial.println( "] is a number");
    return true;
}
