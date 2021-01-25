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

unsigned long Receiver_AUTO_F::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_F");
    #endif
    return Receiver::init(components);
}

void Receiver_AUTO_F::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver AUTO_F");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " F ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_AUTO_F::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_AUTO_N;
    switch( scancode){
        // Column 0
        case 2:
            return_value = COMPONENT_RECEIVER_AUTO_K;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_AUTO_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->Stack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing
        // Column 2 does nothing

        // Column 3
        case 13:
            _rpnf->execute( FUNC_SIN);
            break;
        case 14:
            _rpnf->execute( FUNC_ARCSIN);
            break;
        case 15:
            _rpnf->execute( FUNC_EXP);
            break;
        case 16:
            _rpnf->execute( FUNC_10X);
            break;

        // Column 4
        case 17:
            _rpnf->execute( FUNC_COS);
            break;
        case 18:
            _rpnf->execute( FUNC_ARCCOS);
            break;
        case 19:
            _rpnf->execute( FUNC_LG);
            break;
        case 20:
            _rpnf->execute( FUNC_ROT);
            break;

        // Column 5
        case 21:
            _rpnf->execute( FUNC_TG);
            break;
        case 22:
            _rpnf->execute( FUNC_ARCTG);
            break;
        case 23:
            _rpnf->execute( FUNC_LN);
            break;
        case 24:
            #ifdef __DEBUG
            Serial.println("AUTO display already activated");
            #endif
            break;

        // Column 6
        case 25:
            _rpnf->execute( FUNC_SQRT);
            break;
        case 26:
            _rpnf->execute( FUNC_PI);
            break;
        case 27:
            _rpnf->execute( FUNC_POW);
            break;
        case 28:
            return COMPONENT_DISPLAY_PROG;

        // Column 7
        case 29:
            _rpnf->execute( FUNC_1X);
            break;
        case 30:
            _rpnf->execute( FUNC_X2);
            break;
        case 31:
            _rpnf->execute( FUNC_BX);
            break;
        case 32:
            break;

        default: // all other buttons do nothing, keeping F-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}
