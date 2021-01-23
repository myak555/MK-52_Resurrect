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

unsigned long Receiver_AUTO_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_N");
    #endif
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Receiver::init(components);
}

void Receiver_AUTO_N::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "   ");
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_AUTO_N::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendButton( scancode);
}

int Receiver_AUTO_N::_appendButton(uint8_t scancode){
    int return_value = NO_CHANGE;
    if( _nr->isActive()){
        int8_t r = _nr->tick( scancode);
        if( r == NO_CHANGE) return NO_CHANGE;
        _completeSubentry();
        scancode = (uint8_t)r;
    }
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
        case 0: // keyboard inactive
            break;

        // Column 0
        case 1:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_AUTO_F;
            break;
        case 2:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_AUTO_K;
            break;
        case 3:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_AUTO_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_DMOD);
            _lcd->updateStatusDMODE(_rpnf->Stack->getDModeName());
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
            // no need to wait on keyboard!
            return COMPONENT_RECEIVER_AUTO_R;

        // Column 2
        case 9:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("M->X ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            break;
        case 10:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("X->M ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            break;
        case 11:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("GOTO ") );
        //     _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            break;
        case 12: // TODO STEP
            _rpnf->execute( FUNC_INCREMENT_PC);
            _rpnf->Stack->setStackLabel_P( 0, PSTR("STEP!"));
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
            if(_rpnf->Stack->customStackLabels()) _rpnf->Stack->resetStackLabels();              
            else _rpnf->execute( FUNC_CLEAR_X);
            break;

        default: // all other buttons activate number entry
            _rpnf->execute( FUNC_ENTER);
            _mode = 2;
            _nr->activate( scancode, COMPONENT_RECEIVER_AUTO_N);
            break;
    }
    delay(KBD_IDLE_DELAY);
    return return_value;
}

void Receiver_AUTO_N::_completeSubentry(){
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
