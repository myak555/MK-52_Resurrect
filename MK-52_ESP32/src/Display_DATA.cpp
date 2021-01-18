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
// Inits LIST display
//
unsigned long Display_DATA::init( void *components[]) {
    _nr = (MK52_Interpreter::Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Display::init( components);
}

int Display_DATA::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( _pmem->getCounter(), 5678, "GRD", " F ");
    for( int i=10; i>=0; i--){
        if(i<10)
            snprintf(buff, 30, "%04d  %18.11E", i, _fakeData);
        else
            snprintf(buff, 30, "%04d: %18.11E", i, _fakeData);
        buff[29] = 0;
        _lcd->outputTerminalLine( i, buff);
    }
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("DATA display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    delay( DEBUG_SHOW_DELAY);
    #endif
    return -1;
}

void Display_DATA::tick(){
}
