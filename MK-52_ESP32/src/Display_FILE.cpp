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
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    return Display::init( components);
}

void Display_FILE::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    char **Lines = _rpnf->getOutputLines();
    _sd->getFolderListing( Lines, 11, SCREEN_COLS-1);
    _lcd->outputStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(), "DSK", "   ");
    for( int i=0; i<11; i++){
        _lcd->outputTerminalLine( i, Lines[i]);
    }
    _setCurrentReceiver( COMPONENT_RECEIVER_FILE_N);
    _lcd->undimScreen();

    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("FILE display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
    return;
}

int Display_FILE::tick(){
    uint8_t scancode = _kbd->scan();
    if( current_Receiver == NULL) return NO_CHANGE;
    int newReceiver = current_Receiver->tick( scancode);
    if( newReceiver < -1) return newReceiver;
    switch( newReceiver){
        case COMPONENT_DISPLAY_AUTO:
        case COMPONENT_DISPLAY_PROG:
        case COMPONENT_DISPLAY_DATA:
            Serial.println("Display change requested");
            return newReceiver;
        case 0:
        case -1:
            break;
        default:
            Serial.println("Receiver change requested");
            _setCurrentReceiver( newReceiver, 0, COMPONENT_RECEIVER_FILE_N);
            break;
    }
    unsigned long start = millis();
    char **Lines = _rpnf->getOutputLines();
    _sd->getFolderListing( Lines, 11, SCREEN_COLS-1);
    int nlines = 11;
    if( _tr->isActive()){
        _lcd->updateTerminalLine( 9, "> Name?");
        _lcd->updateTerminalLine( 10, _tr->toScreenString());
        nlines -= 2;
    }
    //_lcd->updateTerminalLine( 0, _sd->getFolderNameTruncated( SCREEN_COLS-1));
    for( int i=0; i<nlines; i++){
        _lcd->updateTerminalLine( i, Lines[i]);
        // if( i>_sd->_nItems){
        //     _lcd->updateTerminalLine( i, "");
        //     continue;
        // }
        // char *line = _sd->getItemString( i-1);
        // _lcd->updateTerminalLine( i, line);
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return NO_CHANGE;
}
