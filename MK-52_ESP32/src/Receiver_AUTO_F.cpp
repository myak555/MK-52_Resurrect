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
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Receiver::init(components);
}

void Receiver_AUTO_F::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " F ");
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_AUTO_F::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendButton( scancode);
}

int Receiver_AUTO_F::_appendButton(uint8_t scancode){
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
        case 0:
        case 1:
            delay(KBD_IDLE_DELAY);
            return NO_CHANGE;

        // Column 0
        case 2:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_K;
        case 3:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_A;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->Stack->getDModeName());
            return NO_CHANGE;

        // Column 1 does nothing
        // Column 2 does nothing

        // Column 3
        case 13:
            _rpnf->execute( FUNC_SIN);
            _mode = 0;
            Serial.println("SIN Called");
            return COMPONENT_RECEIVER_AUTO_N;
        case 14:
            Serial.println("ArcSIN");
            //_rpnf->execute( FUNC_NEGATE);
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_N;
        case 15:
            Serial.println("Exp");
            //_rpnf->execute( FUNC_NEGATE);
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_N;
        case 16:
            Serial.println("10^x");
            //_rpnf->execute( FUNC_NEGATE);
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_N;

        case 32:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_N;

        default: // all other buttons do nothing
           delay(KBD_IDLE_DELAY);
           return NO_CHANGE;
    }
    return NO_CHANGE;
}

void Receiver_AUTO_F::_completeSubentry(){
    switch( _mode){
        case 0:
        case 1:
            return;
        case 2:
            _mode = 1;
            _rpnf->execute( _nr->toTrimmedString());
            break;
        default:
            break;
    }
    _lcd->updateStatusFMODE( "   ");
}
