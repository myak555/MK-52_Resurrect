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
void Register_Memory::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Register memory init");
    #endif
    _rst = (RPN_Stack*)components[COMPONENT_STACK];
    _emem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    _buffer = (uint8_t *)malloc( REGISTER_MEMORY_SIZE + 9);
    #ifdef __DEBUG
    if( _buffer == NULL){
        Serial.println("Register Memory malloc busted!");
    }
    #endif
    _uv = new UniversalValue( _buffer + REGISTER_MEMORY_SIZE);
    clear();
}

void Register_Memory::clear(){
    memset(_buffer, 0, REGISTER_MEMORY_SIZE);
    for( int i=0; i<REGISTER_MEMORY_SIZE; i+=9) _buffer[i] = VALUE_TYPE_INTEGER;
}

void Register_Memory::MtoX(int8_t n){
    _rst->storeBx();
    _rst->push();
    if( n<0 || n>=REGISTER_MEMORY_NVALS){
        _rst->X->fromInt(0);
        return;
    }
    _rst->X->fromLocation( _registerAddress(n));
}

void Register_Memory::XtoM(int8_t n){
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    if( n<16)
        _uv->fromLocation( _rst->X->toBytes());
    else
        _uv->fromInt( _rst->X->toInt());
    _uv->toLocation(_registerAddress(n));
}

void Register_Memory::K_MtoX(int8_t n){
    _rst->storeBx();
    _rst->push();
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    _uv->fromLocation(_registerAddress(n));
    if( _uv->isEmpty()){
        _rst->X->fromInt(0);
        return;
    }
    int64_t index = _uv->toInt();
    _autoIncrement( n);
    if( index<0 || index>=EXTENDED_MEMORY_NVALS){
        _rst->X->fromInt(0);
        return;
    }
    _emem->setCounter(index);
    uint8_t *ptr = _emem->getCurrentLine();
    if( *ptr == VALUE_TYPE_EMPTY) _rst->X->fromInt(0);
    else _rst->X->fromLocation( ptr);
}

void Register_Memory::K_XtoM(int8_t n){
    if( n<0 || n>=REGISTER_MEMORY_NVALS) return;
    _uv->fromLocation(_registerAddress(n));
    if( _uv->isEmpty()) return;
    int64_t index = _uv->toInt();
    _autoIncrement( n);
    A_XtoM( index);
}

void Register_Memory::A_MtoX(int64_t index){
    _rst->storeBx();
    _rst->push();
    if( index<0 || index>=EXTENDED_MEMORY_NVALS){
        _rst->X->fromInt(0);
        return;
    }
    _emem->setCounter(index);
    uint8_t *ptr = _emem->getCurrentLine();
    if( *ptr == VALUE_TYPE_EMPTY) _rst->X->fromInt(0);
    else _rst->X->fromLocation( ptr);
}

void Register_Memory::A_XtoM(int64_t index){
    if( index<0 || index>=EXTENDED_MEMORY_NVALS){
        _rst->setLabel_P(0, "No such address");
        return;
    }
    _emem->setCounter(index);
    uint8_t *ptr = _emem->getCurrentLine();
    _rst->X->toLocation( ptr);
}

void Register_Memory::A_MtoX(char *address){
    _rst->storeBx();
    _rst->push();
    _emem->setCounter(address);
    uint8_t *ptr = _emem->getCurrentLine();
    if( *ptr == VALUE_TYPE_EMPTY) _rst->X->fromInt(0);
    else _rst->X->fromLocation( ptr);
}

void Register_Memory::A_XtoM(char *address){
    _emem->setCounter(address);
    uint8_t *ptr = _emem->getCurrentLine();
    _rst->X->toLocation( ptr);
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

//
// TODO: For compatibility, registers are converted to int!
// Not sure, if this must be supported or changed
//
void Register_Memory::_autoIncrement( int8_t n){
    if( n<0) return;
    if( n>6) return;
    int delta = (n > 3)? 1: -1;
    if( _uv->isInt())
        _uv->fromInt( _uv->toInt() + delta);
    if( _uv->isReal())
        // _uv->fromReal( _uv->toReal() + (double)delta);
        _uv->fromInt( _uv->toInt() + delta);
    _uv->toLocation( _registerAddress(n));
}
