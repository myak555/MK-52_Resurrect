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

void Receiver_DATA_A::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init DATA_A");
    #endif
    Receiver::init(components);
}

void Receiver_DATA_A::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver DATA_A");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " A ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_DATA_A::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_DATA_N;
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_DATA_F;
            break;
        case 2:
            return_value = COMPONENT_RECEIVER_DATA_K;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing
        // Column 2 does nothing
        // Column 3 does nothing
        // Column 4 does nothing

        // Column 5
        case 24:
            #ifdef __DEBUG
            Serial.println("Going to FILE Display");
            #endif
            return_value = COMPONENT_DISPLAY_FILE;
            break;

        // Column 6
        case 28:
            #ifdef __DEBUG
            Serial.println("Already in DATA Display");
            #endif
            break;

        // Column 7
        case 32:
            return_value = SHUTDOWN_REQUESTED;
            break;

        default: // all other buttons do nothing - keep A-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}
