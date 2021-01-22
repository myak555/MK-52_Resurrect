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
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
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
        case 2:
            return NO_CHANGE;

        // Column 0
        case 1:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_F;
        case 3:
            _mode = 0;
            return COMPONENT_RECEIVER_AUTO_A;

        // Column 1
        case 5:
            _rpnf->execute( FUNC_INCREMENT_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            return NO_CHANGE;
        case 6:
            _rpnf->execute( FUNC_DECREMENT_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            return NO_CHANGE;
        case 7:
            _rpnf->execute( FUNC_RESET_PC);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            return NO_CHANGE;
        case 8: {// TODO START

            uint32_t newAddress = _rpnf->progMem->getCounter() + 99; // fake program "running"
            while( _rpnf->progMem->getCounter() < newAddress){
                _rpnf->execute( FUNC_INCREMENT_PC);
                _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            }}
            //     _pmem->updateLine_P( PSTR("STOP"));
            //     _pmem->incrementCounter();
            return NO_CHANGE;

        // Column 2
        case 9:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("M->X ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_CHANGE;
        case 10:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("X->M ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_CHANGE;
        case 11:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("GOTO ") );
        //     _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_CHANGE;
        case 12: // TODO STEP
            _rpnf->execute( FUNC_INCREMENT_PC);
            _rpnf->Stack->setStackLabel_P( 0, PSTR("STEP!"));
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            return NO_CHANGE;

        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("GOSUB ") );
        //     _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_CHANGE;

        // Column 5
        case 24:
            _rpnf->execute( FUNC_NEGATE);
            return NO_CHANGE;

        // Column 6
        case 25:
            _rpnf->execute( FUNC_MINUS);
            return NO_CHANGE;
        case 26:
            _rpnf->execute( FUNC_PLUS);
            return NO_CHANGE;
        case 27:
            _rpnf->execute( FUNC_SWAP);
            return NO_CHANGE;

        // Column 7
        case 29:
            _rpnf->execute( FUNC_DIVIDE);
            return NO_CHANGE;
        case 30:
            _rpnf->execute( FUNC_MULTIPLY);
            return NO_CHANGE;
        case 31:
            _rpnf->execute( FUNC_ENTER);
            return NO_CHANGE;
        case 32:
            if(_rpnf->Stack->customStackLabels())
                _rpnf->Stack->resetStackLabels();                
        //     _pmem->updateLine_P( PSTR("Cx"));
        //     _pmem->incrementCounter();
            return NO_CHANGE;

        default: // all other buttons activate number entry
            _rpnf->execute( FUNC_ENTER);
            _mode = 2;
            _nr->activate( scancode, COMPONENT_RECEIVER_AUTO_K);
            return NO_CHANGE;
    }
    return NO_CHANGE;
}

void Receiver_AUTO_K::_completeSubentry(){
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
