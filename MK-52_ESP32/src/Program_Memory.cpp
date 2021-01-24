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

//
// Inits the calculator program memory
//
unsigned long Program_Memory::init( void *components[]) {
    clearText();
    setInputMode(PSTR("   "));
    _buffer = (uint8_t *)malloc( PROGRAM_MEMORY_SIZE);
    #ifdef __DEBUG
    if( _buffer == NULL){
        Serial.println("Program Memory malloc busted!");
        return millis();
    }
    #endif
    _limit = _buffer + PROGRAM_MEMORY_SIZE;
    clear();

    #ifdef __DEBUG
    Serial.print("Free program memory: ");
    Serial.println( getFree());
    #endif
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
    if( line == NULL) line = _text;
    size_t ln = strlen( (line));
    if( ln >= getFree()) return true;
    strcpy( (char *)_bottom, line);
    _bottom += ln+1;
    return false;
}
bool Program_Memory::appendLine_P(const char *line){
    size_t ln = strlen_P( (line));
    if( ln >= getFree()) return true;
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
uint32_t Program_Memory::setCounter(char *s){
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
    if( _pointer == _buffer) return true; // already at top

    // Skip to end of previous line
    uint8_t *tmp = _pointer;
    _pointer--;
    if( _pointer == _buffer){ // top reached
        _counter = 0;
        return false;
    }

    // Skip to beginning of previous line
    _pointer--;
    while( _pointer > _buffer && *_pointer != 0) _pointer--;
    if( _pointer == _buffer){ // top reached
        _counter = 0;
        return false;
    }
    _pointer++;
    _counter--;
    return false;
}

bool Program_Memory::replaceLine(char *line){
    if( line == NULL) line = _text;
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

bool Program_Memory::insertLine(char *line){
    if( line == NULL) line = _text;
    size_t toCopy = strlen(line) + 1;
    if( _pointer + toCopy >= _limit) return false; // no space
    if( _pointer >= _bottom){
        if( _pointer+toCopy >= _limit) return false;
        memcpy( _pointer, line, toCopy);
        _bottom = _pointer + toCopy;
        return true;
    }
    size_t toMove = _bottom - _pointer;
    memmove( _pointer+toCopy, _pointer, toMove+1);
    _bottom += toCopy;
    *_bottom = 0;
    memcpy( _pointer, line, toCopy);
    return true;
}
bool Program_Memory::insertLine_P(const char *line){
    size_t toCopy = strlen(line) + 1;
    if( _pointer + toCopy >= _limit) return false; // no space
    if( _pointer >= _bottom){
        if( _pointer+toCopy >= _limit) return false;
        memcpy_P( _pointer, line, toCopy);
        _bottom = _pointer + toCopy;
        return true;
    }
    size_t toMove = _bottom - _pointer;
    memmove( _pointer+toCopy, _pointer, toMove+1);
    _bottom += toCopy;
    *_bottom = 0;
    memcpy_P( _pointer, line, toCopy);
    return true;
}

bool Program_Memory::updateLine(char *line){
    if( EditOverwrite) replaceLine(line);
    else insertLine(line);
}

bool Program_Memory::updateLine_P(const char *line){
    if( EditOverwrite) replaceLine_P(line);
    else insertLine_P(line);
}


void Program_Memory::deleteLine(){
    if( _pointer >= _bottom) return;
    size_t toCopy = strlen(getCurrentLine()) + 1;
    uint8_t *source = _pointer + toCopy;
    memmove( _pointer, source, toCopy);
    memset( _bottom, 0, toCopy);
    _bottom -= toCopy;
}

char *Program_Memory::appendText( char *text){
    int8_t ln = strlen(_text);
    char *ptr = _text + ln;
    while( ln<PROGRAM_LINE_LENGTH && *text){
        *ptr++ = *text++;
        ln++;
    }
    *ptr = 0;
    return ptr;
}

char *Program_Memory::appendText_P( const char *text){
    int8_t ln = strlen(_text);
    char *ptr = _text + ln;
    char c = (char)pgm_read_byte(text++);
    while( ln<PROGRAM_LINE_LENGTH && c){
        *ptr++ = c;
        c = (char)pgm_read_byte(text++);
        ln++;
    }
    *ptr = 0;
    return ptr;
}
