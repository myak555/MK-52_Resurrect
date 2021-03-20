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

void Receiver_DATA_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init DATA_N");
    #endif
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    _ar = (Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    _rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    Receiver::init(components);
}

void Receiver_DATA_N::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver DATA_N");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "   ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_DATA_N::tick( uint8_t scancode){
    int return_value = NO_CHANGE;
    int r = _completeSubentry(scancode);
    if( r <= 0) return return_value;
    scancode = (uint8_t)r;
    switch( scancode){
        case 0: // keyboard inactive
            break;

        // Column 0
        case 1:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_DATA_F;
            break;
        case 2:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_DATA_K;
            break;
        case 3:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_DATA_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            break;

        // Column 1
        case 5:
            _rpnf->execute( FUNC_INCREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;
        case 6:
            _rpnf->execute( FUNC_DECREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;
        case 7:
            _rpnf->execute( FUNC_RESET_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;
        case 8:
            _rpnf->execute( FUNC_MEXTOX);
            break;

        // Column 2
        case 9:
            _mode = 3;
            _rr->activate(0, 0);
            break;
        case 10:
            _mode = 4;
            _rr->activate(0, 0);
            break;
        case 11:
            _mode = 5;
            _ar->activate(0, 0);
            _lcd->updateStatusMC( _ar->toString());
            break;
        case 12:
            _rpnf->execute( FUNC_XTOMEX);
            _rpnf->execute( FUNC_INCREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;

        // Columns 3-5 - number entry
 
        // Column 6
        case 25: // minus
        case 26: // plus
            break;
        case 27:
            _rpnf->execute( FUNC_MEMSWP);
            _rpnf->execute( FUNC_INCREMENT_MC);
            break;

        // Column 7
        case 29: // divide
        case 30: // multiply
            break;
        case 31:
            _rpnf->execute( FUNC_MEMSET, _nr->toTrimmedString());
            _rpnf->execute( FUNC_INCREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;
        case 32:
            _rpnf->execute( FUNC_MEXCLR);
            _rpnf->execute( FUNC_INCREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;

        default: // all other buttons activate number entry
            _mode = 2;
            _nr->activate( scancode, COMPONENT_RECEIVER_DATA_N);
            break;
    }
    return return_value;
}

int Receiver_DATA_N::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
            r = _nr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            #ifdef __DEBUG
            Serial.print("Received number: ");
            Serial.println(_nr->toTrimmedString());
            #endif 
            _rpnf->execute( FUNC_MEMSET, _nr->toTrimmedString());
            _rpnf->execute( FUNC_INCREMENT_MC);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            break;
        case 3:
        case 4:
            r = _rr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            _rpnf->execute( (_mode==4)? FUNC_MEXTOR : FUNC_RTOMEX, _rr->toString());
            #ifdef __DEBUG
            Serial.print("Registers updated, returning ");
            Serial.println(r);
            #endif 
            break;
        case 5:
            r = _ar->tick( scancode);
            if( r == NO_CHANGE){
                _lcd->updateStatusMC( _ar->toString());
                return NO_CHANGE;
            }
            _rpnf->extMem->setCounter(_ar->toString());
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            #ifdef __DEBUG
            Serial.print("GOTO done, returning ");
            Serial.println(r);
            #endif 
            break;
        default:
            break;
    }
    _mode = 1;
    _lcd->updateStatusFMODE( "   ");
    return r;
}
