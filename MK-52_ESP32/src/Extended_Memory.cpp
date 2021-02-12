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
    _buffer = (uint8_t *)malloc( EXTENDED_MEMORY_SIZE + 9);
    #ifdef __DEBUG
    if( _buffer == NULL){
        Serial.println("Extended Memory malloc busted!");
        return millis();
    }
    #endif
    _uv = new UniversalValue( _buffer + EXTENDED_MEMORY_SIZE);
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

void Extended_Memory::clearCurrent(){
    memset( getCurrentLine(), 0, 9);
}

void Extended_Memory::resetCounter(){
    _counter = 0;
}

//
// Returns the counter actually set
//
uint32_t Extended_Memory::setCounter(uint32_t address){
    if( address >= EXTENDED_MEMORY_NVALS) address = EXTENDED_MEMORY_NVALS-1;
    _counter = address;  
    #ifdef __DEBUG
    Serial.print( "MC setting to: ");
    Serial.println( _counter);
    #endif
    return _counter;
}
uint32_t Extended_Memory::setCounter(char *text){
    #ifdef __DEBUG
    Serial.print( "Processing address: ");
    Serial.println( text);
    #endif
    int ln = strlen(text);
    if( ln <= 0) return _counter;
    if( text[0]==' ') return _counter;
    uint32_t n = 0;
    while( *text){
        if( *text == ' '){
            text++;
            continue;
        }
        n = n*10 + *text - '0';
        text++;
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

char *Extended_Memory::toString( char *text, int32_t n){
    memset( text, 0, 2*SCREEN_COLS);
    text[0] = ' ';
    if( n<0 || EXTENDED_MEMORY_NVALS<=n) return text;
    snprintf_P( text, 5, PSTR("%04u"), (uint32_t)n);
    text[4] = (n == _counter)? '>': ' ';
    text[5] = ' ';
    _uv->fromLocation( _memoryAddress(n));
    if( _uv->isEmpty()) return text;
    _uv->toString(text+6);
    return text;
}

void Extended_Memory::fromString( char *text){
    _uv->fromString( text);
    _uv->toLocation( getCurrentLine());
}

void Extended_Memory::fromUV( UniversalValue *uv){ 
    uv->toLocation(getCurrentLine());
}

void Extended_Memory::toUV( UniversalValue *uv){
    uv->fromLocation(getCurrentLine());
}

void Extended_Memory::swapWithUV( UniversalValue *uv){
    uint8_t *ptr = getCurrentLine();
    _uv->fromLocation( uv->toBytes());
    uv->fromLocation( ptr);
    _uv->toLocation( ptr);
}
