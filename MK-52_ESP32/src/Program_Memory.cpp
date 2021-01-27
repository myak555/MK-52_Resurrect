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
    _buffer = (uint8_t *)malloc( PROGRAM_MEMORY_SIZE);
    _returnStack = (uint32_t *)malloc( RETURN_STACK_SIZE * 8);
    #ifdef __DEBUG
    if( _buffer == NULL || _returnStack == NULL){
        Serial.println("Program Memory malloc busted!");
        return millis();
    }
    #endif
    clear();
    setEMode( EMODE_OWERWRITE);

    #ifdef __DEBUG
    appendLine_P( PSTR("-1.2345678e-004"));
    appendLine_P( PSTR("9"));
    appendLine_P( PSTR("*"));
    appendLine_P( PSTR("X->M A"));
    appendLine_P( PSTR("X->M B"));
    appendLine_P( PSTR("X->M C"));
    appendLine_P( PSTR("Cx"));
    appendLine_P( PSTR("M->X A"));
    appendLine_P( PSTR("STOP"));
    Serial.print("Free program memory: ");
    Serial.println( getFree());
    Serial.print("ProgMem init with: ");
    Serial.println( getEModeName());
    #endif
    return millis();
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

// bool Program_Memory::replaceLine(char *line){
//     if( line == NULL) line = _text;
//     size_t toCopy = strlen(line) + 1;
//     if( _pointer + toCopy >= _limit) return false; // no space
//     if( _pointer >= _bottom){
//         if( _pointer+toCopy >= _limit) return false;
//         memcpy( _pointer, line, toCopy);
//         _bottom = _pointer + toCopy;
//         return true;
//     }
//     size_t toReplace = strlen(getCurrentLine()) + 1;
//     if( toCopy == toReplace){
//         memcpy( _pointer, line, toCopy);
//         return true;
//     }
//     size_t toMove = 0;
//     if( toCopy < toReplace){
//         toMove = toReplace - toCopy;
//         memcpy( _pointer, line, toCopy);
//         memmove( _pointer+toCopy, _pointer+toReplace, toMove);
//         memset( _bottom, 0, toMove);
//         _bottom -= toMove;
//         return true;
//     }
//     toMove = toCopy - toReplace;
//     if( _bottom + toMove >= _limit) toMove = _limit - _bottom - 1;
//     if( toMove > 0) memmove( _pointer + toMove, _pointer, toMove);
//     _bottom += toMove;
//     memcpy( _pointer, line, toCopy);
//     *_bottom = 0;
//     return true;
// }

// bool Program_Memory::replaceLine_P(const char *line){
//     size_t toCopy = strlen_P(line) + 1;
//     if( _pointer + toCopy >= _limit) return false; // no space
//     if( _pointer >= _bottom){
//         if( _pointer+toCopy >= _limit) return false;
//         memcpy_P( _pointer, line, toCopy);
//         _bottom = _pointer + toCopy;
//         return true;
//     }
//     size_t toReplace = strlen(getCurrentLine()) + 1;
//     if( toCopy == toReplace){
//         memcpy_P( _pointer, line, toCopy);
//         return true;
//     }
//     size_t toMove = 0;
//     if( toCopy < toReplace){
//         toMove = toReplace - toCopy;
//         memcpy_P( _pointer, line, toCopy);
//         memmove( _pointer+toCopy, _pointer+toReplace, toMove);
//         memset( _bottom, 0, toMove);
//         _bottom -= toMove;
//         return true;
//     }
//     toMove = toCopy - toReplace;
//     if( _bottom + toMove >= _limit) toMove = _limit - _bottom - 1;
//     if( toMove > 0) memmove( _pointer + toMove, _pointer, toMove);
//     _bottom += toMove;
//     memcpy_P( _pointer, line, toCopy);
//     *_bottom = 0;
//     return true;
// }

// bool Program_Memory::insertLine(char *line){
//     if( line == NULL) line = _text;
//     size_t toCopy = strlen(line) + 1;
//     if( _pointer + toCopy >= _limit) return false; // no space
//     if( _pointer >= _bottom){
//         if( _pointer+toCopy >= _limit) return false;
//         memcpy( _pointer, line, toCopy);
//         _bottom = _pointer + toCopy;
//         return true;
//     }
//     size_t toMove = _bottom - _pointer;
//     memmove( _pointer+toCopy, _pointer, toMove+1);
//     _bottom += toCopy;
//     *_bottom = 0;
//     memcpy( _pointer, line, toCopy);
//     return true;
// }

// bool Program_Memory::insertLine_P(const char *line){
//     size_t toCopy = strlen(line) + 1;
//     if( _pointer + toCopy >= _limit) return false; // no space
//     if( _pointer >= _bottom){
//         if( _pointer+toCopy >= _limit) return false;
//         memcpy_P( _pointer, line, toCopy);
//         _bottom = _pointer + toCopy;
//         return true;
//     }
//     size_t toMove = _bottom - _pointer;
//     memmove( _pointer+toCopy, _pointer, toMove+1);
//     _bottom += toCopy;
//     *_bottom = 0;
//     memcpy_P( _pointer, line, toCopy);
//     return true;
// }

bool Program_Memory::updateLine(char *line){
//     if( EditOverwrite) replaceLine(line);
//     else insertLine(line);
}

bool Program_Memory::updateLine_P(const char *line){
//     if( EditOverwrite) replaceLine_P(line);
//     else insertLine_P(line);
}


// void Program_Memory::deleteLine(){
//     if( _pointer >= _bottom) return;
//     size_t toCopy = strlen(getCurrentLine()) + 1;
//     uint8_t *source = _pointer + toCopy;
//     memmove( _pointer, source, toCopy);
//     memset( _bottom, 0, toCopy);
//     _bottom -= toCopy;
// }

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
