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

unsigned long Receiver_PROG_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_N");
    #endif
    _nr = (Receiver_Number*)components[COMPONENT_RECEIVER_NUMBER];
    _tr = (Receiver_Text*)components[COMPONENT_RECEIVER_TEXT];
    _ar = (Receiver_Address*)components[COMPONENT_RECEIVER_ADDRESS];
    _rr = (Receiver_Register*)components[COMPONENT_RECEIVER_REGISTER];
    _pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return Receiver::init(components);
}

void Receiver_PROG_N::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver PROG_N");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "   ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_PROG_N::tick( uint8_t scancode){
    int return_value = NO_CHANGE;
    if( _nr->isActive()){
        if( _nr->tick( scancode) == NO_CHANGE){
            _rpnf->progMem->updateLine( _nr->toTrimmedString());
            return NO_CHANGE;
        }
        _rpnf->progMem->replaceLine( _nr->toTrimmedString());
        _rpnf->progMem->incrementCounter();
        _lcd->updateStatusPC( _rpnf->progMem->getCounter());
        return NO_CHANGE;
    }
    if( _ar->isActive()){        
        if( _ar->tick( scancode) == NO_CHANGE){
            sprintf_P( _rpnf->getOutputBuffer(), PSTR("%04u> "), _rpnf->progMem->getCounter());
            _rpnf->appendOutputBuffer( _rpnf->progMem->getCurrentLine());
            _rpnf->appendOutputBuffer( _ar->toTrimmedString());
            _lcd->updateTerminalLine( 10, _rpnf->getOutputBuffer());
            return NO_CHANGE;
        }
        _rpnf->setOutputBuffer( _rpnf->progMem->getCurrentLine());
        _rpnf->appendOutputBuffer( _ar->toString());
        _rpnf->progMem->replaceLine( _rpnf->getOutputBuffer());
        _rpnf->progMem->incrementCounter();
        _lcd->updateStatusPC( _rpnf->progMem->getCounter());
        return return_value;
    }
    if( _rr->isActive()){   
        if( _rr->tick( scancode) == NO_CHANGE) return NO_CHANGE;
        _rpnf->setOutputBuffer( _rpnf->progMem->getCurrentLine());
        _rpnf->appendOutputBuffer( _rr->toString());
        _rpnf->progMem->replaceLine( _rpnf->getOutputBuffer());
        _rpnf->progMem->incrementCounter();
        _lcd->updateStatusPC( _rpnf->progMem->getCounter());
        return return_value;
    }
    switch( scancode){
        case 0:
            break;

        // Column 0
        case 1:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_PROG_F;
            break;
        case 2:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_PROG_K;
            break;
        case 3:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_PROG_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_EMOD);
            _lcd->updateStatusDMODE(_rpnf->progMem->getEModeName());
            return NO_CHANGE;

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
            _rpnf->appendProgramLine_P(FUNC_RETURN);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 8:
            _rpnf->appendProgramLine_P(FUNC_STOP);
            _pmem->incrementCounter();
            return NO_CHANGE;

        // Column 2
        case 9:
            _rpnf->appendProgramLine_P(FUNC_M2X);
            _rr->activate(0, -2);
            return NO_CHANGE;
        case 10:
            _rpnf->appendProgramLine_P(FUNC_X2M);
            _rr->activate(0, -3);
            return NO_CHANGE;
        case 11:
            _rpnf->appendProgramLine_P(FUNC_GOTO);
            _ar->activate(0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 12:
            _rpnf->appendProgramLine_P(FUNC_GOSUB);
            _ar->activate(0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;

        // Column 5
        case 24:
            _rpnf->appendProgramLine_P(FUNC_NEGATE);
            _pmem->incrementCounter();
            return NO_CHANGE;

        // Column 6
        case 25:
            _rpnf->appendProgramLine_P(FUNC_MINUS);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_PLUS);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_SWAP);
            _pmem->incrementCounter();
            return NO_CHANGE;

        // Column 7
        case 29:
            _rpnf->appendProgramLine_P(FUNC_DIVIDE);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 30:
            _rpnf->appendProgramLine_P(FUNC_MULTIPLY);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_ENTER);
            _pmem->incrementCounter();
            return NO_CHANGE;
        case 32:
            _rpnf->appendProgramLine_P(FUNC_CLEAR_X);
            _pmem->incrementCounter();
            return NO_CHANGE;

        default: // all other buttons activate number entry
            _nr->activate(scancode, COMPONENT_RECEIVER_PROG_N);
            break;
    }
    return return_value;
}
