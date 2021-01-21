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

//
// Inits the calculator program memory
//
unsigned long Register_Memory::init( void *components[]) {
    // clearText();
    // setInputMode(PSTR("   "));
    // _buffer = (uint8_t *)malloc( PROGRAM_MEMORY_SIZE);
    // #ifdef __DEBUG
    // if( _buffer == NULL){
    //     Serial.println("Register Memory malloc busted!");
    //     return millis();
    // }
    // #endif
    // _limit = _buffer + PROGRAM_MEMORY_SIZE;
    // clear();

    #ifdef __DEBUG
    Serial.println("Register memory stub init");
    #endif
    return millis();
}
