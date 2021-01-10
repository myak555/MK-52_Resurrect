//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"

#define __DEBUG

using namespace MK52_Interpreter;

//
// Inits display for PROG mode
//
unsigned long PROG_Display::init( void *components[]) {
    return Display::init( components);
}

void PROG_Display::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( "0000", "9999", "RAD", "   ");
    for( int i=10; i>=0; i--){
        if(i<10)
            snprintf(buff, 30, "%04d  %s", i, _fakeData);
        else
            snprintf(buff, 30, "%04d: %s", i, _fakeData);
        buff[29] = 0; // safety zero
        _lcd->outputTerminalLine( i, buff);
    }
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("PROG display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    delay( DEBUG_SHOW_DELAY);
    #endif
}

void PROG_Display::tick(){
}
