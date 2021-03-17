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

void Receiver_AUTO_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_N");
    #endif
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    _ar = (Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    _rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    Receiver::init(components);
}

void Receiver_AUTO_N::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver AUTO_N");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "   ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_AUTO_N::tick( uint8_t scancode){
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
            return COMPONENT_RECEIVER_AUTO_F;
        case 2:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_K;
        case 3:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_A;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->rpnStack->getDModeName());
            break;

        // Column 1
        case 5:
            _rpnf->execute( FUNC_INCREMENT_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            break;
        case 6:
            _rpnf->execute( FUNC_DECREMENT_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            break;
        case 7:
            _rpnf->execute( FUNC_RESET_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            break;
        case 8:
            // no need to wait on keyboard
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_R;

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
            _lcd->updateStatusPC( _ar->toString());
            break;
        case 12:
            _rpnf->executeStep();
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            break;

        // Column 5
        case 24:
            _rpnf->execute( FUNC_NEGATE);
            break;

        // Column 6
        case 25:
            _rpnf->execute( FUNC_MINUS);
            break;
        case 26:
            _rpnf->execute( FUNC_PLUS);
            break;
        case 27:
            _rpnf->execute( FUNC_SWAP);
            break;

        // Column 7
        case 29:
            _rpnf->execute( FUNC_DIVIDE);
            break;
        case 30:
            _rpnf->execute( FUNC_MULTIPLY);
            break;
        case 31:
            _rpnf->execute( FUNC_ENTER);
            break;
        case 32:
            if(_rpnf->rpnStack->customLabels()) _rpnf->rpnStack->resetLabels();              
            else _rpnf->execute( FUNC_CLEAR_X);
            break;

        default: // all other buttons activate number entry
            _rpnf->execute( FUNC_ENTER);
            _mode = 2;
            _nr->activate( scancode, COMPONENT_RECEIVER_AUTO_N);
            break;
    }
    return return_value;
}

int Receiver_AUTO_N::_completeSubentry( uint8_t scancode){
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
            // execute not needed here, as it advances pc 
            //_rpnf->execute( _nr->toTrimmedString());
            _rpnf->rpnStack->X->fromString( _nr->toTrimmedString());
            #ifdef __DEBUG
            Serial.print("Number in stack: ");
            Serial.println( _rpnf->rpnStack->X->toReal());
            Serial.print("Number updated, returning ");
            Serial.println(r);
            #endif 
            break;
        case 3:
        case 4:
            r = _rr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            _rpnf->execute( (_mode==3)? FUNC_M2X : FUNC_X2M, _rr->toString());
            #ifdef __DEBUG
            Serial.print("Registers updated, returning ");
            Serial.println(r);
            #endif 
            break;
        case 5:
            r = _ar->tick( scancode);
            if( r == NO_CHANGE){
                _lcd->updateStatusPC( _ar->toString());
                return NO_CHANGE;
            }
            _rpnf->execute( FUNC_GOTO, _ar->toString());
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
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
