//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Register_Memory.hpp"

#define __DEBUG

using namespace MK52_Interpreter;

const char _RM_NameConversion[] PROGMEM = "0123456789ABCDEFL";

//
// Inits the calculator program memory
//
unsigned long Register_Memory::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Register memory init");
    #endif
    _rst = (RPN_Stack*)components[COMPONENT_STACK];
    _emem = (Extended_Memory *)components[COMPONENT_STACK];
    _buffer = (uint8_t *)malloc( REGISTER_MEMORY_SIZE);
    #ifdef __DEBUG
    if( _buffer == NULL){
        Serial.println("Register Memory malloc busted!");
        return millis();
    }
    #endif
    clear();
    return millis();
}

void Register_Memory::clear(){
    memset(_buffer, 0, REGISTER_MEMORY_SIZE);
    for( int i=0; i<REGISTER_MEMORY_SIZE; i+=9) _buffer[i] = VALUE_TYPE_INTEGER;
}

void Register_Memory::MtoX(int8_t n){
    _rst->storeBx();
    _rst->push();
    if( n<0 || n>=20){
        _rst->X->fromInt(0);
        return;
    }
    _rst->X->fromLocation( _registerAddress(n));
}

void Register_Memory::XtoM(int8_t n){
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    UniversalValue *uv = new UniversalValue( _registerAddress(n));
    if( n<16)
        uv->fromLocation( _rst->X->toBytes());
    else
        uv->fromInt( _rst->X->toInt());
    delete( uv);
}

void Register_Memory::K_MtoX(int8_t n){
    _rst->storeBx();
    _rst->push();
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    UniversalValue *uv = new UniversalValue( _registerAddress(n));
    int64_t index = uv->toInt();
    delete(uv);
    if( index<0 || index>=EXTENDED_MEMORY_NVALS){
        _rst->X->fromInt(0);
        return;
    }
    // TODO
    _emem->setCounter(index);
    _rst->X->fromInt(0);
}

void Register_Memory::K_XtoM(int8_t n){
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    UniversalValue *uv = new UniversalValue( _registerAddress(n));
    int64_t index = uv->toInt();
    delete(uv);
    if( index<0 || index>=EXTENDED_MEMORY_NVALS){
        _rst->setStackLabel(0, "No such address");
        return;
    }
    _emem->setCounter(index);
    // TODO - memory writing
}

//
// Returns the register address:
// 0-15 are registers 0-F
// 16-19 are registers L0-L3
// -1 - no such register
//
int8_t Register_Memory::registerByName( char *name){
    int8_t index = _chrfind_P(name[0]);
    if( index < 0) return -1;
    if( index < 16) return index;
    index = _chrfind_P(name[1]);
    if( index < 0) return -1;
    if( index >= 4) return -1;
    return index+16;
}

int8_t Register_Memory::_chrfind_P( char c){
    if( !c) return -1;
    for( int8_t i=0; i<127; i++){
        char b = (char)pgm_read_byte( _RM_NameConversion+i);
        if( !b) break;
        if( b==c) return i;
    }
    return -1;
}
