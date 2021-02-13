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
void Program_Memory::init( void *components[]) {
    _buffer = (uint8_t *)malloc( PROGRAM_MEMORY_SIZE);
    _returnStack = (uint32_t *)malloc( RETURN_STACK_SIZE * 8);
    #ifdef __DEBUG
    if( _buffer == NULL || _returnStack == NULL){
        Serial.println("Program Memory malloc busted!");
    }
    #endif
    clear();
    setEMode( EMODE_OWERWRITE);

    #ifdef __DEBUG
    //appendLine_P( PSTR("-1.2345678e-004"));
    //appendLine_P( PSTR("9"));
    //appendLine_P( PSTR("*"));
    //appendLine_P( PSTR("X->M A"));
    //appendLine_P( PSTR("X->M B"));
    //appendLine_P( PSTR("X->M C"));
    //appendLine_P( PSTR("Cx"));
    //appendLine_P( PSTR("M->X A"));
    //appendLine_P( PSTR("STOP"));
    //appendLine_P( PSTR("GOTO 0001"));
    Serial.print("Free program memory: ");
    Serial.println( getFree());
    Serial.print("ProgMem init with: ");
    Serial.println( getEModeName());
    #endif
}

void Program_Memory::clear(){
    memset( _buffer, 0, PROGRAM_MEMORY_SIZE);
    _bottom = 0;
    resetCounter();
}

void Program_Memory::resetCounter(){
    _current = 0;
    _counter = 0;
    _returnStackPtr = 0;
}

char *Program_Memory::getNextLine(){
    char *ptr = getCurrentLine();
    return ptr + strlen(ptr) + 1;
}

//
// Returns true if not enough memory
//
bool Program_Memory::appendLine(char *line){
    size_t ln = strlen( (line));
    if( ln >= getFree()) return true;
    strcpy( getBottom(), line);
    _bottom += ln+1;
    return false;
}
bool Program_Memory::appendLine_P(const char *line){
    size_t ln = strlen_P( (line));
    if( ln >= getFree()) return true;
    strcpy_P( getBottom(), line);
    _bottom += ln+1;
    return false;
}

//
// Returns the counter actually set
//
uint32_t Program_Memory::setCounter(uint32_t address){
    #ifdef __DEBUG
    Serial.print( "PC setting to: ");
    Serial.println( address);
    #endif
    while( _counter < address ){
        if( incrementCounter()) break;
    }
    while( _counter > address ){
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
    uint32_t tmp = _current;
    while( _current < PROGRAM_MEMORY_SIZE && currentChar() != 0) _current++;
    
    // End of memory reached - nothing changes
    if( _current >= PROGRAM_MEMORY_SIZE){
        _current = tmp;
        return true;
    }
    _current++; // next line
    _counter++;
    return false;
}

//
// Returns true if the counter is not moving
//
bool Program_Memory::decrementCounter(){
    if( _current == 0) return true; // already at top

    // Skip to end of previous line
    int32_t tmp = (int32_t)_current;
    tmp--;
    if( tmp <= 0){ // top reached
        resetCounter();
        return false;
    }

    // Skip to beginning of previous line
    tmp--;
    while( tmp >= 0 && _buffer[tmp] != 0) tmp--;
    if( tmp <= 0){ // top reached
        resetCounter();
        return false;
    }
    _current = tmp+1;
    _counter--;
    return false;
}

//
// Returns true if stack is busted
//
bool Program_Memory::goSub( uint32_t address){
    if( _returnStackPtr >= RETURN_STACK_SIZE) return true;
    *_returnStack++ = _counter;
    *_returnStack++ = _current;
    setCounter( address);
    return false;
}

bool Program_Memory::goSub( char *s){
    if( _returnStackPtr >= RETURN_STACK_SIZE) return true;
    *_returnStack++ = _counter;
    *_returnStack++ = _current;
    setCounter( s);
    return false;
}

//
// Returns true if stack is busted
//
bool Program_Memory::returnFromSub(){
    if( _returnStackPtr == 0) return true;
    _current = *(--_returnStack);
    _counter = *(--_returnStack);
    incrementCounter(); // go to the next line after call
    return false;
}

bool Program_Memory::replaceLine(char *line){
    size_t toCopy = strlen(line) + 1;
    char *ptrC = getCurrentLine();
    if( _current + toCopy >= PROGRAM_MEMORY_SIZE) return false; // no space
    if( _current >= _bottom){
        if( _current+toCopy >= PROGRAM_MEMORY_SIZE) return false;
        memcpy( ptrC, line, toCopy);
        _bottom = _current + toCopy;
        return true;
    }
    size_t toReplace = strlen(ptrC) + 1;
    if( toCopy == toReplace){
        memcpy( ptrC, line, toCopy);
        return true;
    }
    size_t toMove = 0;
    if( toCopy < toReplace){
        toMove = toReplace - toCopy;
        memcpy( ptrC, line, toCopy);
        memmove( ptrC+toCopy, ptrC+toReplace, toMove);
        memset( getBottom(), 0, toMove);
        _bottom -= toMove;
        return true;
    }
    toMove = toCopy - toReplace;
    if( _bottom + toMove >= PROGRAM_MEMORY_SIZE) toMove = PROGRAM_MEMORY_SIZE - _bottom - 1;
    if( toMove > 0) memmove( ptrC + toMove, ptrC, toMove);
    _bottom += toMove;
    memcpy( ptrC, line, toCopy);
    getBottom()[0] = 0;
    return true;
}

bool Program_Memory::replaceLine_P(const char *line){
    size_t toCopy = strlen_P(line) + 1;
    char *ptrC = getCurrentLine();
    if( _current + toCopy >= PROGRAM_MEMORY_SIZE) return false; // no space
    if( _current >= _bottom){
        if( _current+toCopy >= PROGRAM_MEMORY_SIZE) return false;
        memcpy_P( ptrC, line, toCopy);
        _bottom = _current + toCopy;
        return true;
    }
    size_t toReplace = strlen(ptrC) + 1;
    if( toCopy == toReplace){
        memcpy_P( ptrC, line, toCopy);
        return true;
    }
    size_t toMove = 0;
    if( toCopy < toReplace){
        toMove = toReplace - toCopy;
        memcpy_P( ptrC, line, toCopy);
        memmove( ptrC+toCopy, ptrC+toReplace, toMove);
        memset( getBottom(), 0, toMove);
        _bottom -= toMove;
        return true;
    }
    toMove = toCopy - toReplace;
    if( _bottom + toMove >= PROGRAM_MEMORY_SIZE) toMove = PROGRAM_MEMORY_SIZE - _bottom - 1;
    if( toMove > 0) memmove( ptrC + toMove, ptrC, toMove);
    _bottom += toMove;
    memcpy_P( ptrC, line, toCopy);
    getBottom()[0] = 0;
    return true;
}

bool Program_Memory::insertLine(char *line){
    size_t toCopy = strlen(line) + 1;
    char *ptrC = getCurrentLine();
    if( _current + toCopy >= PROGRAM_MEMORY_SIZE) return false; // no space
    if( _current >= _bottom){
        if( _current+toCopy >= PROGRAM_MEMORY_SIZE) return false;
        memcpy( ptrC, line, toCopy);
        _bottom = _current + toCopy;
        return true;
    }
    size_t toMove = _bottom - _current;
    if( _bottom + toCopy >= PROGRAM_MEMORY_SIZE) toMove = PROGRAM_MEMORY_SIZE - _bottom - 1;
    if( toMove > 0) memmove( ptrC + toCopy, ptrC, toMove);
    _bottom += toCopy;
    memcpy( ptrC, line, toCopy);
    getBottom()[0] = 0;
    return true;
}

bool Program_Memory::insertLine_P(const char *line){
    size_t toCopy = strlen(line) + 1;
    char *ptrC = getCurrentLine();
    if( _current + toCopy >= PROGRAM_MEMORY_SIZE) return false; // no space
    if( _current >= _bottom){
        if( _current+toCopy >= PROGRAM_MEMORY_SIZE) return false;
        memcpy_P( ptrC, line, toCopy);
        _bottom = _current + toCopy;
        return true;
    }
    size_t toMove = _bottom - _current;
    if( _bottom + toCopy >= PROGRAM_MEMORY_SIZE) toMove = PROGRAM_MEMORY_SIZE - _bottom - 1;
    if( toMove > 0) memmove( ptrC + toCopy, ptrC, toMove);
    _bottom += toCopy;
    memcpy_P( ptrC, line, toCopy);
    getBottom()[0] = 0;
    return true;
}

bool Program_Memory::updateLine(char *line){
    if( _eMode == EMODE_OWERWRITE) replaceLine(line);
    else insertLine(line);
}

bool Program_Memory::updateLine_P(const char *line){
    if( _eMode == EMODE_OWERWRITE) replaceLine_P(line);
    else insertLine_P(line);
}

void Program_Memory::deleteLine(){
    if( _current >= _bottom) return;
    char *ptrC = getCurrentLine();
    size_t toCopy = strlen(ptrC) + 1;
    char *source = ptrC + toCopy;
    memmove( ptrC, source, toCopy);
    memset( getBottom(), 0, toCopy);
    _bottom -= toCopy;
}

void Program_Memory::getPreviousLines( char *lines[], uint8_t n){
    lines[0] = getCurrentLine();
    memset( lines+1, 0, (n-1)*sizeof( char *));
    if( _current == 0) return;

    uint8_t i = 1;
    char *ptr = lines[0];
    ptr--;
    while( i<n){
        ptr--;
        while( *ptr != 0) ptr--;
        lines[i++] = ptr+1;
        // at this point, the pointer is at the end of previous line
        if( ptr == (char*)_buffer && i<n-1){
            lines[i] = ptr;
            break;
        }
    } 
}

bool Program_Memory::isAtStop(){
    return UniversalValue::_startsWith_P( getCurrentLine(), PSTR("STOP"));
}

void Program_Memory::setEMode(uint8_t m){
    switch(m){
        case 1:
            _eMode = EMODE_INSERT;
            strncpy_P( _eModeName, PSTR("INS"), 3);
            break;
        case 2:
            _eMode = EMODE_SHIFT;
            strncpy_P( _eModeName, PSTR("SHF"), 3);
            break;
        default:
            _eMode = EMODE_OWERWRITE;
            strncpy_P( _eModeName, PSTR("OVR"), 3);
            break;
    }
    _eModeName[3] = 0;
} 

uint8_t Program_Memory::toggleEditMode(){
    setEMode( _eMode+1);
    return _eMode;
} 
