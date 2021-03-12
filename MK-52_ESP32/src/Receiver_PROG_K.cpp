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

void Receiver_PROG_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_K");
    #endif
    _rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    _ar = (Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    Receiver::init(components);
}

void Receiver_PROG_K::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver PROG_K");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " K ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_PROG_K::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_PROG_N;
    if( _rr->isActive()){   
        if( _rr->tick( scancode) == NO_CHANGE) return NO_CHANGE;
        _rpnf->setOutputBuffer( _rpnf->progMem->getCurrentLine());
        _rpnf->appendOutputBuffer( _rr->toString());
        _rpnf->progMem->replaceLine( _rpnf->getOutputBuffer());
        _rpnf->progMem->incrementCounter();
        _lcd->updateStatusPC( _rpnf->progMem->getCounter());
        return return_value;
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
    switch( scancode){
        // Column 0
        case 1:
            return_value = COMPONENT_RECEIVER_AUTO_F;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_AUTO_A;
            break;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_EMOD);
            _lcd->updateStatusDMODE(_rpnf->progMem->getEModeName());
            return NO_CHANGE;

        // Column 1 does nothing
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
            _rpnf->appendProgramLine_P(FUNC_K_M2X);
            _rr->activate(0, -2);
            return NO_CHANGE;
        case 10:
            _rpnf->appendProgramLine_P(FUNC_K_X2M);
            _rr->activate(0 , -3);
            return NO_CHANGE;
        case 11:
            _rpnf->progMem->updateLine_P( PSTR("# K-GOTO is bad!"));
            break;
        case 12:
            _rpnf->progMem->updateLine_P( PSTR("# K-GOSUB is bad!"));
            break;

        // Column 3
        case 13:
            _rpnf->appendProgramLine_P(FUNC_WHOLE);
            break;
        case 14:
            _rpnf->appendProgramLine_P(FUNC_ABS);
            break;
        case 15:
            _rpnf->appendProgramLine_P(FUNC_EE);
            break;
        case 16:
            _rpnf->progMem->commentLine();
            break;

        // Column 4
        case 17:
            _rpnf->appendProgramLine_P(FUNC_FRAC);
            break;
        case 18:
            _rpnf->appendProgramLine_P(FUNC_SIGN);
            break;
        case 19:
            _rpnf->appendProgramLine_P(FUNC_LOG);
            break;
        case 20:
            _rpnf->appendProgramLine_P(FUNC_AND);
            break;

        // Column 5
        case 21:
            _rpnf->appendProgramLine_P(FUNC_MAX);
            break;
        case 22:
            _rpnf->appendProgramLine_P(FUNC_DM2D);
            break;
        case 23:
            _rpnf->appendProgramLine_P(FUNC_DMS2D);
            break;
        case 24:
            _rpnf->appendProgramLine_P(FUNC_OR);
            break;

        // Column 6
        case 25:
            _rpnf->progMem->updateLine_P( PSTR("# K-SQRT"));
            break;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_D2DM);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_D2DMS);
            break;
        case 28:
            _rpnf->appendProgramLine_P(FUNC_XOR);
            break;

        // Column 7
        case 29:
            _rpnf->progMem->updateLine_P( PSTR("# K-1/X"));
            break;
        case 30:
            _rpnf->progMem->updateLine_P( PSTR("# K-X2"));
            break;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_RAND);
            break;
        case 32:
            _rpnf->appendProgramLine_P(FUNC_NOT);
            break;

        default: // all other buttons do nothing - keep K-mode
           return NO_CHANGE;
    }
    _mode = 0;
    _rpnf->progMem->incrementCounter();
    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    return return_value;
}
