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

unsigned long Receiver_FILE_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init FILE_K");
    #endif
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    return Receiver::init(components);
}

void Receiver_FILE_K::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver FILE_K");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " K ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_FILE_K::tick( uint8_t scancode){
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
        case 3:
            return_value = COMPONENT_RECEIVER_FILE_A;
            break;
            
        default: // all other buttons do nothing - keep K-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}

int Receiver_FILE_K::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    // switch( _mode){
    //     default:
    //         break;
    // }
    _mode = 0;
    return r;
}
