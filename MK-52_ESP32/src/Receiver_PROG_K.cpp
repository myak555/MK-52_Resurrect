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

unsigned long Receiver_PROG_K::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_K");
    #endif
    _rr = (Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    return Receiver::init(components);
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
        
        // Column 2
        case 9:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_K_M2X)->Name());
            _rr->activate(0, -2);
            return NO_CHANGE;
        case 10:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_K_X2M)->Name());
            _rr->activate(0 , -3);
            return NO_CHANGE;
        case 11:
            _rpnf->progMem->updateLine_P( PSTR("# K-GOTO is bad for you!"));
            break;
        case 12:
            _rpnf->progMem->updateLine_P( PSTR("# K-GOSUB is bad for you!"));
            break;

        // Column 3
        case 13:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_WHOLE)->Name());
            break;
        case 14:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_ABS)->Name());
            break;
        case 15:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_EE)->Name());
            break;
        case 16:
            // NOP TODO
            _rpnf->progMem->updateLine_P( PSTR("# NOP"));
            break;

        // Column 4
        case 17:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_FRAC)->Name());
            break;
        case 18:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_SIGN)->Name());
            break;
        case 19:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_LOG)->Name());
            break;
        case 20:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_AND)->Name());
            break;

        // Column 5
        case 21:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_MAX)->Name());
            break;
        case 22:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_DM2D)->Name());
            break;
        case 23:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_DMS2D)->Name());
            break;
        case 24:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_OR)->Name());
            break;

        // Column 6
        case 25:
            _rpnf->progMem->updateLine_P( PSTR("# K-SQRT"));
            break;
        case 26:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_D2DM)->Name());
            break;
        case 27:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_D2DMS)->Name());
            break;
        case 28:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_XOR)->Name());
            break;

        // Column 7
        case 29:
            _rpnf->progMem->updateLine_P( PSTR("# K-1/X"));
            break;
        case 30:
            _rpnf->progMem->updateLine_P( PSTR("# K-X2"));
            break;
        case 31:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_RAND)->Name());
            break;
        case 32:
            _rpnf->progMem->updateLine_P( _rpnf->getFunctionByID( FUNC_NOT)->Name());
            break;

        default: // all other buttons do nothing - keep K-mode
           return NO_CHANGE;
    }
    _mode = 0;
    _rpnf->progMem->incrementCounter();
    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    return return_value;
}
