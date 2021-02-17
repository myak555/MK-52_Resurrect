//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"
#include "../functions/functions.h"

#define __DEBUG

using namespace MK52_Interpreter;

void Receiver_FILE_A::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init FILE_A");
    #endif
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    Receiver::init(components);
}

void Receiver_FILE_A::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver FILE_A");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " A ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_FILE_A::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_FILE_N;
    int r = _completeSubentry(scancode);
    if( r < NO_CHANGE) return return_value;
    if( r <= 0) return NO_CHANGE;
    scancode = (uint8_t)r;
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_FILE_F;
            break;
        case 2:
            return_value = COMPONENT_RECEIVER_FILE_K;
            break;

        case 24:
            #ifdef __DEBUG
            Serial.println("Already in FILE Display");
            #endif
            break;

        case 28:
            #ifdef __DEBUG
            Serial.println("Going to DATA Display");
            #endif
            return_value = COMPONENT_DISPLAY_DATA;
            break;

        case 32:
            return_value = SHUTDOWN_REQUESTED;
            break;

        default: // all other buttons do nothing - keep A-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}

int Receiver_FILE_A::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    // switch( _mode){
    //     default:
    //         break;
    // }
    _mode = 0;
    return r;
}
