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

void Receiver_PROG_A::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_A");
    #endif
    _ar = (Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    Receiver::init(components);
}

void Receiver_PROG_A::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver PROG_A");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " A ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_PROG_A::tick( uint8_t scancode){    int return_value = COMPONENT_RECEIVER_PROG_N;
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
    switch( scancode){
        // Column 0
        case 1:
            _mode = 0;
            return COMPONENT_RECEIVER_PROG_F;
        case 2:
            _mode = 0;
            return COMPONENT_RECEIVER_PROG_K;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_EMOD);
            _lcd->updateStatusDMODE(_rpnf->progMem->getEModeName());
            return NO_CHANGE;

        // Column 1
        case 5:
            _rpnf->appendProgramLine_P(FUNC_IFNOTLTY);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 6:
            _rpnf->appendProgramLine_P(FUNC_IFNOTEQY);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 7:
            _rpnf->appendProgramLine_P(FUNC_IFNOTGEY);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 8:
            _rpnf->appendProgramLine_P(FUNC_IFNOTNEY);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;

        // Column 2
        case 9:
            _rpnf->appendProgramLine_P(FUNC_A_X2M);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 10:
            _rpnf->appendProgramLine_P(FUNC_A_M2X);
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;

        // Column 3 does nothing
        // Column 4 does nothing

        // Column 5
        case 21:
            // TODO
            return NO_CHANGE;
        case 22:
            _rpnf->appendProgramLine_P(FUNC_D2RAD);
            break;
        case 23:
            _rpnf->appendProgramLine_P(FUNC_MM2IN);
            break;
        case 24:
            #ifdef __DEBUG
            Serial.println("Going to FILE Display");
            #endif
            _mode = 0;
            return COMPONENT_DISPLAY_FILE;

        // Column 6
        case 25:
            // TODO
            return NO_CHANGE;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_RAD2D);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_IN2MM);
            break;
        case 28:
            #ifdef __DEBUG
            Serial.println("Going to DATA Display");
            #endif
            _mode = 0;
            return COMPONENT_DISPLAY_DATA;

        // Column 7
        case 29:
            // TODO
        case 30:
            // TODO
            return NO_CHANGE;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_SEED);
            break;
        case 32:
            _mode = 0;
            return SHUTDOWN_REQUESTED;

        default: // all other buttons do nothing - keep A-mode
           return NO_CHANGE;
    }
    _mode = 0;
    _rpnf->progMem->incrementCounter();
    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    return return_value;
}
