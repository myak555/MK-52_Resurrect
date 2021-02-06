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

unsigned long Receiver_DATA_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init DATA_K");
    #endif
    return Receiver::init(components);
}

void Receiver_DATA_K::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver DATA_K");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " K ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_DATA_K::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_DATA_N;
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_DATA_F;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_DATA_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing
        // Column 2 does nothing
        // Column 3 does nothing
        // Column 4 does nothing
        // Column 5 does nothing
        // Column 6 does nothing
        // Column 7
        case 32:
            // erase program memory
            _lcd->outputTerminalLine( 10, "ERASE memory? (\030)");
            if( _getConfirmation( 31)) _rpnf->extMem->clear();

        default: // all other buttons do nothing - keep K-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}
