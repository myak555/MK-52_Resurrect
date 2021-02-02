//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//#include "SD_Manager.hpp"
#include "Extended_Memory.hpp"

#define __DEBUG
using namespace MK52_Interpreter;

//
// Inits the calculator program memory
//
unsigned long Extended_Memory::init( void *components[]) {
    _buffer = (uint8_t *)malloc( EXTENDED_MEMORY_SIZE);
    #ifdef __DEBUG
    if( _buffer == NULL){
        Serial.println("Extended Memory malloc busted!");
        return millis();
    }
    #endif
    clear();

    #ifdef __DEBUG
    Serial.print("Extended memory available: ");
    Serial.println( EXTENDED_MEMORY_SIZE);
    #endif
    return millis();
}

void Extended_Memory::clear(){
    memset( _buffer, 0, EXTENDED_MEMORY_SIZE);
    resetCounter();
}

void Extended_Memory::resetCounter(){
    _counter = 0;
}

//
// Returns the counter actually set
//
uint32_t Extended_Memory::setCounter(uint32_t c){
    if( c >= EXTENDED_MEMORY_NVALS) c = EXTENDED_MEMORY_NVALS-1;
    _counter = c;  
    #ifdef __DEBUG
    Serial.print( "Counter setting to: ");
    Serial.println( _counter);
    #endif
    return _counter;
}
uint32_t Extended_Memory::setCounter(char *s){
    #ifdef __DEBUG
    Serial.print( "Processing address: ");
    Serial.println( s);
    #endif
    int ln = strlen(s);
    if( ln <= 0) return _counter;
    if( s[0]==' ') return _counter;
    uint32_t n = 0;
    while( *s){
        if( *s == ' '){
            s++;
            continue;
        }
        n = n*10 + *s - '0';
        s++; 
    }
    return setCounter(n);
}

//
// Returns true if the counter is not moving
//
bool Extended_Memory::incrementCounter(){
    if(_counter >= EXTENDED_MEMORY_NVALS-1) return true;
    _counter++;
    return false;
}

//
// Returns true if the counter is not moving
//
bool Extended_Memory::decrementCounter(){
    if(_counter == 0) return true;
    _counter--;
    return false;
}

char *Extended_Memory::toString( char *buff, int32_t n){
    memset( buff, 0, 2*SCREEN_COLS);
    buff[0] = ' ';
    if( n<0 || EXTENDED_MEMORY_NVALS<=n) return buff;
    snprintf_P( buff, 5, PSTR("%04u"), (uint32_t)n);
    buff[4] = (n == _counter)? '>': ' ';
    buff[5] = ' ';
    UniversalValue *uv = new UniversalValue( _memoryAddress(n));
    if( uv->isEmpty()){
         delete( uv);
         return buff;
    }
    uv->toString(buff+6);
    delete(uv);
    return buff;
}
