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

unsigned long Receiver_AUTO_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_K");
    #endif
    return Receiver::init(components);
}

void Receiver_AUTO_K::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " K ");
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_AUTO_K::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendButton( scancode);
}

int Receiver_AUTO_K::_appendButton(uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_AUTO_N;
//     if( _ar->isActive()){
//         if( _ar->tick( scancode) == NO_CHANGE) return NO_CHANGE;
//         char *tmp = _ar->toString();
//         if( *tmp == 0){
//             _pmem->deleteLine();
//             return NO_CHANGE;
//         }
//         _pmem->appendText( tmp);
//         _pmem->updateLine();
//         _pmem->incrementCounter();
//         return NO_CHANGE;
//     }
//     if( _rr->isActive()){
//         if( _rr->tick( scancode) == NO_CHANGE) return NO_CHANGE;
//         _pmem->appendText( _rr->toString());
//         _pmem->updateLine();
//         _pmem->incrementCounter();
//         return NO_CHANGE;
//     }
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_AUTO_F;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_AUTO_A;
            break;

        // Column 1 does nothing
        
        // Column 2
        case 9:
            _rpnf->execute( FUNC_K_M2X);
            break;
        case 10:
            _rpnf->execute( FUNC_K_X2M);
            break;
        case 11:
            _rpnf->Stack->setStackLabel_P(0, PSTR("K-GOTO is bad for you!"));
            break;
        case 12:
            _rpnf->Stack->setStackLabel_P(0, PSTR("K-GOSUB is bad for you!"));
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
           delay(KBD_IDLE_DELAY);
           return NO_CHANGE;
    }
    _mode = 0;
    delay(KBD_IDLE_DELAY);
    return return_value;
}

void Receiver_AUTO_K::_completeSubentry(){
    switch( _mode){
        case 0:
        case 1:
            return;
        case 2:
            _mode = 1;
            break;
        default:
            break;
    }
    _lcd->updateStatusFMODE( "   ");
}
