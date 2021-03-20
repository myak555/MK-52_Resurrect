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

void Receiver_AUTO_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_K");
    #endif
    _rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    Receiver::init(components);
}

void Receiver_AUTO_K::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver AUTO_K");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " K ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_AUTO_K::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_AUTO_N;
    int r = _completeSubentry(scancode);
    if( r < NO_CHANGE) return return_value;
    if( r <= 0) return NO_CHANGE;
    scancode = (uint8_t)r;
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_AUTO_F;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_AUTO_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing
        
        // Column 2
        case 9:
            _mode = 2;
            _rr->activate(0 , -2);
            return NO_CHANGE;
        case 10:
            _mode = 3;
            _rr->activate(0 , -3);
            return NO_CHANGE;
        case 11:
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-GOTO is bad for you!"));
            break;
        case 12:
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-GOSUB is bad for you!"));
            break;

        // Column 3
        case 13:
            _rpnf->execute( FUNC_WHOLE);
            break;
        case 14:
            _rpnf->execute( FUNC_ABS);
            break;
        case 15:
            _rpnf->execute( FUNC_EE);
            break;
        case 16:
            // NOP
            break;

        // Column 4
        case 17:
            _rpnf->execute( FUNC_FRAC);
            break;
        case 18:
            _rpnf->execute( FUNC_SIGN);
            break;
        case 19:
            _rpnf->execute( FUNC_LOG);
            break;
        case 20:
            _rpnf->execute( FUNC_AND);
            break;

        // Column 5
        case 21:
            _rpnf->execute( FUNC_MAX);
            break;
        case 22:
            _rpnf->execute( FUNC_DM2D);
            break;
        case 23:
            _rpnf->execute( FUNC_DMS2D);
            break;
        case 24:
            _rpnf->execute( FUNC_OR);
            break;

        // Column 6
        case 25:
            #ifdef __DEBUG
            Serial.println("Put something for K-SQRT");
            #endif
            //_rpnf->execute( FUNC_SQRT);
            break;
        case 26:
            _rpnf->execute( FUNC_D2DM);
            break;
        case 27:
            _rpnf->execute( FUNC_D2DMS);
            break;
        case 28:
            _rpnf->execute( FUNC_XOR);
            break;

        // Column 7
        case 29:
            #ifdef __DEBUG
            Serial.println("Put something for K-1/X");
            #endif
            //_rpnf->execute( FUNC_COS);
            break;
        case 30:
            #ifdef __DEBUG
            Serial.println("Put something for K-X2");
            #endif
            //_rpnf->execute( FUNC_ARCCOS);
            break;
        case 31:
            _rpnf->execute( FUNC_RAND);
            break;
        case 32:
            _rpnf->execute( FUNC_NOT);
            break;

        default: // all other buttons do nothing - keep K-mode
           return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}

int Receiver_AUTO_K::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
        case 3:
            r = _rr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            _rpnf->execute( (_mode==2)? FUNC_K_M2X : FUNC_K_X2M, _rr->toString());
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            #ifdef __DEBUG
            Serial.println("Memory updated, returning ");
            Serial.print(r);
            #endif 
            break;
        default:
            break;
    }
    _mode = 0;
    return r;
}
