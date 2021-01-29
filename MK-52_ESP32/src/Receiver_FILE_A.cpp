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

unsigned long Receiver_FILE_A::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init FILE_A");
    #endif
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    return Receiver::init(components);
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
        case 4:
            //_rpnf->execute(FUNC_TOGGLE_DMOD);
            //_lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing

        // Column 2
        case 9:
            //_mode = 2;
            //_ar->activate(0, -2);
            //_lcd->updateStatusMC( _ar->toString());
            return NO_CHANGE;
        case 10:
            //_mode = 3;
            //_ar->activate(0, -3);
            //_lcd->updateStatusMC( _ar->toString());
            return NO_CHANGE;

        // Column 3 does nothing
        // Column 4 does nothing

        // Column 5
        case 21:
            //_rpnf->execute( FUNC_TG);
            break;
        case 22:
            //_rpnf->execute( FUNC_D2RAD);
            break;
        case 23:
            //_rpnf->execute( FUNC_MM2IN);
            break;
        case 24:
            #ifdef __DEBUG
            Serial.println("Already in FILE Display");
            #endif
            break;

        // Column 6
        case 25:
            //_rpnf->execute( FUNC_COS);
            break;
        case 26:
            //_rpnf->execute( FUNC_RAD2D);
            break;
        case 27:
            //_rpnf->execute( FUNC_IN2MM);
            break;
        case 28:
            #ifdef __DEBUG
            Serial.println("Going to DATA Display");
            #endif
            return_value = COMPONENT_DISPLAY_DATA;
            break;

        // Column 7
        case 29:
            //_rpnf->execute( FUNC_COS);
            break;
        case 30:
            //_rpnf->execute( FUNC_ARCCOS);
            break;
        case 31:
            //_rpnf->execute( FUNC_SEED);
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
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
        case 3:
            // r = _ar->tick( scancode);
            // if( r == NO_CHANGE){
            //     _lcd->updateStatusMC( _ar->toString());
            //     return NO_CHANGE;
            // }
            // Serial.print("Accessing extended memory at ");
            // Serial.println( _ar->toString());
            // _rpnf->execute( (_mode==2)? FUNC_A_M2X : FUNC_A_X2M, _ar->toString());
            // _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            // Serial.print("Memory setting done... returning ");
            // Serial.println(r);
            break;
        default:
            break;
    }
    _mode = 0;
    return r;
}
