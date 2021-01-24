//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

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
    return _counter;
}
uint32_t Extended_Memory::setCounter(char *s){
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
