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
    #ifdef __DEBUG
    Serial.println( "Init Display DATA");
    #endif
    _nr = (MK52_Interpreter::Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Display::init( components);
}

void Display_DATA::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    char *buff = _rpnf->getOutputBuffer();
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(), _rpnf->rpnStack->getDModeName(), "   ");
    int cnt = (int)_rpnf->extMem->getCounter();
    for( int32_t i=10, j=cnt; i>=0; i--, j--){
        _lcd->outputTerminalLine( i, _rpnf->extMem->toString(buff, j));
    }
    _setCurrentReceiver( COMPONENT_RECEIVER_DATA_N);
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("DATA display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
}

int Display_DATA::tick(){
    // keyboard serve part
    uint8_t scancode = _kbd->scan();
    if( current_Receiver == NULL) return NO_CHANGE;
    int newReceiver = current_Receiver->tick( scancode);
    if( newReceiver < -1) return newReceiver;
    switch( newReceiver){
        case COMPONENT_DISPLAY_AUTO:
        case COMPONENT_DISPLAY_FILE:
        case COMPONENT_DISPLAY_PROG:
            return newReceiver;
        case 0:
        case -1:
            break;
        default:
            Serial.print( "Setting receiver ");
            Serial.println( newReceiver);
            _setCurrentReceiver( newReceiver, 0, COMPONENT_RECEIVER_DATA_N);
            break;
    }
    
    // display update part
    unsigned long start = millis();
    char *buff = _rpnf->getOutputBuffer();
    int cnt = (int)_rpnf->extMem->getCounter();
    if( _nr->isActive()){
        snprintf_P( buff, SCREEN_COLS, PSTR("%04u> %s"), _rpnf->extMem->getCounter(), _nr->toString());
        buff[SCREEN_COLS] = 0;
        _lcd->updateTerminalLine( 10, buff);
    }
    else{
        _lcd->outputTerminalLine( 10, _rpnf->extMem->toString(buff, cnt));
    }
    for( int32_t i=9, j=cnt-1; i>=0; i--, j--){
        _lcd->updateTerminalLine( i, _rpnf->extMem->toString(buff, j));
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return NO_CHANGE;
}
