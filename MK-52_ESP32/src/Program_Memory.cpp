//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Program_Memory.hpp"

#define __DEBUG
using namespace MK52_Interpreter;

const char _Test_Command_1[] PROGMEM = "TEST LINE 1";
const char _Test_Command_2[] PROGMEM = "TEST LINE 2";
const char _Test_Command_3[] PROGMEM = "TEST LINE 3";

//
// Inits the calculator program memory
//
unsigned long Program_Memory::init( void *components[]) {
    _buffer = (uint8_t *)malloc( PROGRAM_MEMORY_SIZE);
    _limit = _buffer + PROGRAM_MEMORY_SIZE;
    clear();

    // TODO: Testing only
    appendLine_P( _Test_Command_1 );
    appendLine_P( _Test_Command_2 );
    appendLine_P( _Test_Command_3 );
    incrementCounter();
    incrementCounter();
    incrementCounter();
    incrementCounter();
    Serial.print("Counter1 [4]: ");
    Serial.println( getCounter());
    Serial.print("Position1: ");
    Serial.println( (uint32_t)(_pointer-_buffer));
    Serial.print("Free1: ");
    Serial.println( free());
    // setCounter( 100);
    // Serial.print("Counter2 [100]: ");
    // Serial.println( getCounter());
    // Serial.print("Position2: ");
    // Serial.println( (uint32_t)(_pointer-_buffer));
    // Serial.print("Free2: ");
    // Serial.println( free());
    // setCounter( 1);
    // Serial.print("Counter3 [1]: ");
    // Serial.println( getCounter());
    // Serial.print("Position3: ");
    // Serial.println( (uint32_t)(_pointer-_buffer));
    // Serial.print("Free3: ");
    // Serial.println( free());
    // setCounter( 0);
    // Serial.print("Counter4 [0]: ");
    // Serial.println( getCounter());
    // Serial.print("Position4: ");
    // Serial.println( (uint32_t)(_pointer-_buffer));
    // Serial.print("Free4: ");
    // Serial.println( free());
    return millis();
}

void Program_Memory::clear(){
    memset( _buffer, 0, PROGRAM_MEMORY_SIZE);
    _bottom = _buffer;
    resetCounter();
}

void Program_Memory::resetCounter(){
    _pointer = _buffer;
    _counter = 0;
}

//
// Returns true if not enough memory
//
bool Program_Memory::appendLine(char *line){
    size_t ln = strlen( (line));
    if( ln >= free()) return true;
    strcpy( (char *)_bottom, line);
    _bottom += ln+1;
    return false;
}
bool Program_Memory::appendLine_P(const char *line){
    size_t ln = strlen_P( (line));
    if( ln >= free()) return true;
    strcpy_P( (char *)_bottom, line);
    _bottom += ln+1;
    return false;
}

//
// Returns the counter actually set
//
uint32_t Program_Memory::setCounter(uint32_t c){
    while( _counter < c ){
        if( incrementCounter()) break;
    }
    while( _counter > c ){
        if( decrementCounter()) break;
    }
    return _counter;
}

//
// Returns true if the counter is not moving
//
bool Program_Memory::incrementCounter(){
    // Skip to end of line
    uint8_t *tmp = _pointer;
    while( _pointer < _limit-1 && *_pointer != 0) _pointer++;
    
    // End of memory reached - nothing changes
    if( _pointer == _limit-1){
        _pointer = tmp;
        return true;
    }
    _pointer++; // next line
    _counter++;
    return false;
}

//
// Returns true if the counter is not moving
//
bool Program_Memory::decrementCounter(){
    if( _pointer == _buffer) return true;

    // Skip to end of previous line
    uint8_t *tmp = _pointer;
    _pointer--;
    if( _pointer == _buffer){
        _counter--;
        return false;
    }

    // Skip to beginning of previous line
    _pointer--;
    while( _pointer > _buffer && *_pointer != 0) _pointer--;
    if( _pointer > _buffer) _pointer++;
    _counter--;
    return false;
}

bool Program_Memory::replaceLine(char *line){
    size_t toCopy = strlen(line) + 1;
    if( _pointer + toCopy >= _limit) return false; // no space
    if( _pointer >= _bottom){
        if( _pointer+toCopy >= _limit) return false;
        memcpy( _pointer, line, toCopy);
        _bottom = _pointer + toCopy;
        return true;
    }
    size_t toReplace = strlen(getCurrentLine()) + 1;
    if( toCopy == toReplace){
        memcpy( _pointer, line, toCopy);
        return true;
    }
    size_t toMove = 0;
    if( toCopy < toReplace){
        toMove = toReplace - toCopy;
        memcpy( _pointer, line, toCopy);
        memmove( _pointer+toCopy, _pointer+toReplace, toMove);
        memset( _bottom, 0, toMove);
        _bottom -= toMove;
        return true;
    }
    toMove = toCopy - toReplace;
    if( _bottom + toMove >= _limit) toMove = _limit - _bottom - 1;
    if( toMove > 0) memmove( _pointer + toMove, _pointer, toMove);
    _bottom += toMove;
    memcpy( _pointer, line, toCopy);
    *_bottom = 0;
    return true;
}

bool Program_Memory::replaceLine_P(const char *line){
    size_t toCopy = strlen_P(line) + 1;
    if( _pointer + toCopy >= _limit) return false; // no space
    if( _pointer >= _bottom){
        if( _pointer+toCopy >= _limit) return false;
        memcpy_P( _pointer, line, toCopy);
        _bottom = _pointer + toCopy;
        return true;
    }
    size_t toReplace = strlen(getCurrentLine()) + 1;
    if( toCopy == toReplace){
        memcpy_P( _pointer, line, toCopy);
        return true;
    }
    size_t toMove = 0;
    if( toCopy < toReplace){
        toMove = toReplace - toCopy;
        memcpy_P( _pointer, line, toCopy);
        memmove( _pointer+toCopy, _pointer+toReplace, toMove);
        memset( _bottom, 0, toMove);
        _bottom -= toMove;
        return true;
    }
    toMove = toCopy - toReplace;
    if( _bottom + toMove >= _limit) toMove = _limit - _bottom - 1;
    if( toMove > 0) memmove( _pointer + toMove, _pointer, toMove);
    _bottom += toMove;
    memcpy_P( _pointer, line, toCopy);
    *_bottom = 0;
    return true;
}

bool Program_Memory::insertLine(char *line){}
bool Program_Memory::insertLine_P(const char *line){}

void Program_Memory::deleteLine(){
    if( _pointer >= _bottom) return;
    size_t toCopy = strlen(getCurrentLine()) + 1;
    uint8_t *source = _pointer + toCopy;
    memmove( _pointer, source, toCopy);
    memset( _bottom, 0, toCopy);
    _bottom -= toCopy;
}
