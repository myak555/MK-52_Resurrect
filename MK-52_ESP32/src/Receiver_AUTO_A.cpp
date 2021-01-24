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

unsigned long Receiver_AUTO_A::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_A");
    #endif
    _ar = (Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    //_rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    return Receiver::init(components);
}

void Receiver_AUTO_A::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " A ");
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_AUTO_A::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendButton( scancode);
}

int Receiver_AUTO_A::_appendButton(uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_AUTO_N;
    int r = _completeSubentry(scancode);
    if( r < -1) return return_value;
    if( r <= 0) return NO_CHANGE;
    scancode = (uint8_t)r;
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_AUTO_F;
            break;
        case 2:
            return_value = COMPONENT_RECEIVER_AUTO_K;
            break;

        // Column 1 does nothing

        // Column 2
        case 9:
            _mode = 2;
            _ar->activate(0, 0);
            _lcd->updateStatusMC( _ar->toString());
            return NO_CHANGE;
        case 10:
            _mode = 3;
            _ar->activate(0, 0);
            _lcd->updateStatusMC( _ar->toString());
            return NO_CHANGE;

        // Column 3 does nothing
        // Column 4 does nothing

        // Column 5
        case 21:
            //_rpnf->execute( FUNC_TG);
            break;
        case 22:
            _rpnf->execute( FUNC_D2RAD);
            break;
        case 23:
            _rpnf->execute( FUNC_MM2IN);
            break;
        case 24:
            //_rpnf->execute( FUNC_NEGATE);
            break;

        // Column 6
        case 25:
            //_rpnf->execute( FUNC_COS);
            break;
        case 26:
            _rpnf->execute( FUNC_RAD2D);
            break;
        case 27:
            _rpnf->execute( FUNC_IN2MM);
            break;
        case 28:
            //_rpnf->execute( FUNC_ROT);
            break;

        // Column 7
        case 29:
            //_rpnf->execute( FUNC_COS);
            break;
        case 30:
            //_rpnf->execute( FUNC_ARCCOS);
            break;
        case 31:
            _rpnf->execute( FUNC_SEED);
            break;
        case 32:
            break;

        default: // all other buttons do nothing - keep A-mode
           //delay(KBD_IDLE_DELAY);
           return NO_CHANGE;
    }
    _mode = 0;
    //delay(KBD_IDLE_DELAY);
    return return_value;
}

int Receiver_AUTO_A::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
        case 3:
            r = _ar->tick( scancode);
            if( r <= 0){
                _lcd->updateStatusMC( _ar->toString());
                return NO_CHANGE;
            }
            _rpnf->execute( (_mode==2)? FUNC_A_M2X : FUNC_A_X2M, _ar->toString());
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            r = -3;
            break;
        default:
            break;
    }
    _mode = 0;
    return r;
}
