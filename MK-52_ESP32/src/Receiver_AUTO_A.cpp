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
        case 2:
            return_value = COMPONENT_RECEIVER_AUTO_K;
            break;

        // Column 1 does nothing
        // Column 2 does nothing
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
           delay(KBD_IDLE_DELAY);
           return NO_CHANGE;
    }
    _mode = 0;
    delay(KBD_IDLE_DELAY);
    return return_value;
}

void Receiver_AUTO_A::_completeSubentry(){
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
