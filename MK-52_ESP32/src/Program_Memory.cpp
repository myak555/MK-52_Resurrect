//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Program_Memory.hpp"

//#define __DEBUG
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
    Serial.print("Free program memory: ");
    Serial.println( getFree());
    Serial.print("ProgMem init with: ");
    Serial.println( getEModeName());
    #endif
}

void Program_Memory::clear(){
    memset( _buffer, 0, PROGRAM_MEMORY_SIZE);
    _bottom = 1; // one empty line is at the top
    resetCounter();
}

void Program_Memory::resetCounter(){
    _current = 0;
    _counter = 0;
    _returnStackPtr = 0;
}

// char *Program_Memory::getNextLine(){
//     char *ptr = getCurrentLine();
//     return ptr + strlen(ptr) + 1;
// }

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
uint32_t Program_Memory::setCounter(char *text){
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
    #ifdef __DEBUG
    Serial.print("Counter increment: ");
    Serial.print(_counter);
    Serial.print(" / ");
    Serial.println(_current);
    #endif
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
        _counter = 0;
        _current = 0;
        return false;
    }

    // Skip to beginning of previous line
    tmp--;
    while( tmp >= 0 && _buffer[tmp] != 0) tmp--;
    if( tmp < 0){ // top passed
        _counter = 0;
        _current = 0;
        return false;
    }
    _current = tmp+1;
    _counter--;
    #ifdef __DEBUG
    Serial.print("Counter decrement: ");
    Serial.print(_counter);
    Serial.print(" / ");
    Serial.println(_current);
    #endif
    return false;
}

//
// Returns true if stack is busted
//
bool Program_Memory::goSub( uint32_t address){
    if( _returnStackPtr >= RETURN_STACK_SIZE*2) return true;
    _returnStack[_returnStackPtr++] = _counter;
    _returnStack[_returnStackPtr++] = _current;
    setCounter( address);
    #ifdef __DEBUG
    Serial.print("Gone to sub: ");
    Serial.print(_returnStackPtr);
    Serial.print(" / ");
    Serial.println(_current);
    #endif
    return false;
}
bool Program_Memory::goSub( char *text){
    if( _returnStackPtr >= RETURN_STACK_SIZE*2) return true;
    _returnStack[_returnStackPtr++] = _counter;
    _returnStack[_returnStackPtr++] = _current;
    setCounter( text);
    #ifdef __DEBUG
    Serial.print("Gone to sub: ");
    Serial.print(_returnStackPtr);
    Serial.print(" / ");
    Serial.println(_current);
    #endif
    return false;
}

//
// Returns true if stack is busted
//
bool Program_Memory::returnFromSub(){
    if( _returnStackPtr == 0) return true;
    _current = _returnStack[--_returnStackPtr];
    _counter = _returnStack[--_returnStackPtr];
    #ifdef __DEBUG
    Serial.print("Returned from sub: ");
    Serial.print(_returnStackPtr);
    Serial.print(" / ");
    Serial.println(_current);
    #endif
    incrementCounter(); // go to the next line after call
    return false;
}

//
// Returns true if not enough memory
//
bool Program_Memory::appendLine(char *line){
    size_t toAppend = strlen( (line)) + 1;
    if( _current + toAppend >= PROGRAM_MEMORY_SIZE) return true;
    memcpy( getCurrentLine(), line, toAppend);
    _bottom = _current + toAppend;
    #ifdef __DEBUG
    Serial.print("Appended: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}
bool Program_Memory::appendLine_P(const char *line){
    size_t toAppend = strlen_P( (line)) + 1;
    if( _current + toAppend >= PROGRAM_MEMORY_SIZE) return true;
    memcpy_P( getCurrentLine(), line, toAppend);
    _bottom = _current + toAppend;
    #ifdef __DEBUG
    Serial.print("Appended: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}

//
// Returns true if not enough memory
//
bool Program_Memory::replaceLine(char *line){
    if (_current >= _bottom) return appendLine(line);
    int toCopy = strlen(line) + 1;
    char *ptrC = getCurrentLine();
    int toReplace = strlen(ptrC) + 1;
    if( _moveStringsFromCurrent(toCopy - toReplace)) return true;
    memcpy( ptrC, line, toCopy);
    #ifdef __DEBUG
    Serial.print("Replaced: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}
bool Program_Memory::replaceLine_P(const char *line){
    if (_current >= _bottom) return appendLine_P(line);
    int toCopy = strlen_P(line) + 1;
    char *ptrC = getCurrentLine();
    int toReplace = strlen(ptrC) + 1;
    if(_moveStringsFromCurrent(toCopy - toReplace)) return true;
    memcpy_P( ptrC, line, toCopy);
    #ifdef __DEBUG
    Serial.print("Replaced: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}

bool Program_Memory::insertLine(char *line){
    if (_current >= _bottom) return appendLine(line);
    int toInsert = strlen( line) + 1;
    if (_moveStringsFromCurrent(toInsert)) return true;
    memcpy( getCurrentLine(), line, toInsert);
    #ifdef __DEBUG
    Serial.print("Inserted: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}

bool Program_Memory::insertLine_P(const char *line){
    if (_current >= _bottom) return appendLine_P(line);
    int toInsert = strlen_P( line) + 1;
    if (_moveStringsFromCurrent(toInsert)) return true;
    memcpy_P( getCurrentLine(), line, toInsert);
    #ifdef __DEBUG
    Serial.print("Inserted: ");
    Serial.print( line);
    Serial.print(" / ");
    Serial.print(getCurrentLine());
    Serial.print(" / ");
    Serial.println(_bottom);
    #endif
    return false;
}

bool Program_Memory::updateLine(char *line){
    if( _eMode == EMODE_OWERWRITE) return replaceLine(line);
    return insertLine(line);
}

bool Program_Memory::updateLine_P(const char *line){
    if( _eMode == EMODE_OWERWRITE) return replaceLine_P(line);
    return insertLine_P(line);
}

void Program_Memory::deleteLine(){
    if( _current >= _bottom) return;
    int toDelete = strlen( getCurrentLine()) + 1;
    _moveStringsFromCurrent( -toDelete );
}

bool Program_Memory::commentLine(){
    if( _current >= _bottom) return appendLine_P( PSTR("#"));
    char *ptrC = getCurrentLine();
    if( *ptrC == '#') return _moveStringsFromCurrent( -1 );
    if( _moveStringsFromCurrent( 1 )) return true;
    *ptrC = '#';
    return false;
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
    return UniversalValue::_identicalTo_P( getCurrentLine(), PSTR("STOP"));
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

bool Program_Memory::_moveStringsFromCurrent(int32_t shift)
{
    char *ptr = getCurrentLine();
    int32_t toMove = (int32_t)(_bottom-_current);
    if( toMove <= 0) return false;
    if (shift > 0){
        if (_bottom + (uint32_t)shift >= PROGRAM_MEMORY_SIZE) return true;
        memmove( ptr + shift, ptr, toMove);  
        _bottom += shift;
    }
    if (shift < 0) {
        toMove += shift;
        if( toMove <= 0) return false;
        memmove( ptr, ptr-shift, toMove);
        _bottom += shift;
        memset( getBottom(), 0, -shift);
    }
    return false;
}
