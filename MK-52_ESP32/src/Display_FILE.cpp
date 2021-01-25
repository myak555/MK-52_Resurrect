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
// Inits FILE display
//
unsigned long Display_FILE::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init Display FILE");
    #endif
    _sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    return Display::init( components);
}

void Display_FILE::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);

    char *strs[10];
    char *tmp = (char *)malloc( 300);
    for( int i=0; i<10; i++, tmp+=30) strs[i] = tmp;
    _sd->startFolderListing( strs, 10, 29);

    _lcd->outputStatus( _pmem->getCounter(), _emem->getCounter(), "DSK", "   ");
    for( int i=0; i<10; i++)
        _lcd->outputTerminalLine( i, strs[i]);

    _lcd->undimScreen();
    free(strs[0]);

    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("FILE display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    delay( DEBUG_SHOW_DELAY);
    #endif
    return;
}

int Display_FILE::tick(){
    delay( 10000);
    return COMPONENT_DISPLAY_AUTO;
}
