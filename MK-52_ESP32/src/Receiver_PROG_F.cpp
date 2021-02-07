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

unsigned long Receiver_PROG_F::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_F");
    #endif
    _ar = (Receiver_Address*)components[COMPONENT_RECEIVER_ADDRESS];
    //_tr = (Receiver_Text*)components[COMPONENT_RECEIVER_TEXT];
    //_pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return Receiver::init(components);
}

void Receiver_PROG_F::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver PROG_F");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " F ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_PROG_F::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_PROG_N;
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
        return return_value;
    }
    switch( scancode){
        // Column 0
        case 2:
            _mode = 0;
            return COMPONENT_RECEIVER_PROG_K;
        case 3:
            _mode = 0;
            return COMPONENT_RECEIVER_PROG_F;
        case 4:
            _rpnf->execute(FUNC_TOGGLE_EMOD);
            _lcd->updateStatusDMODE(_rpnf->progMem->getEModeName());
            return NO_CHANGE;

        // Column 1
        case 5:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_IFNOTLT0)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 6:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_IFNOTEQ0)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 7:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_IFNOTGE0)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 8:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_IFNOTNE0)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;

        // Column 2
        case 9:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_L0)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 10:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_L1)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 11:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_L2)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;
        case 12:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_L3)->Name()));
            _ar->activate( 0, COMPONENT_RECEIVER_PROG_N);
            return NO_CHANGE;

        // Column 3
        case 13:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_SIN)->Name()));
            break;
        case 14:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_ARCSIN)->Name()));
            break;
        case 15:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_EXP)->Name()));
            break;
        case 16:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_10X)->Name()));
            break;

        // Column 4
        case 17:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_COS)->Name()));
            break;
        case 18:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_ARCCOS)->Name()));
            break;
        case 19:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_LG)->Name()));
            break;
        case 20:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_ROT)->Name()));
            break;

        // Column 5
        case 21:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_TG)->Name()));
            break;
        case 22:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_ARCTG)->Name()));
            break;
        case 23:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_LN)->Name()));
            break;
        case 24:
            #ifdef __DEBUG
            Serial.println("Going to AUTO Display");
            #endif
            _mode = 0;
            return COMPONENT_DISPLAY_AUTO;

        // Column 6
        case 25:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_SQRT)->Name()));
            break;
        case 26:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_PI)->Name()));
            break;
        case 27:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_POW)->Name()));
            break;
        case 28:
            #ifdef __DEBUG
            Serial.println("PROG display already activated");
            #endif
            return NO_CHANGE;

        // Column 7
        case 29:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_1X)->Name()));
            break;
        case 30:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_X2)->Name()));
            break;
        case 31:
            _rpnf->progMem->updateLine_P( PSTR(_rpnf->getFunctionByID( FUNC_BX)->Name()));
            break;
        case 32:
            _mode = 0;
            return COMPONENT_RECEIVER_PROG_N;

        default: // no more buttons
            return NO_CHANGE;
    }
    _mode = 0;
    _rpnf->progMem->incrementCounter();
    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    return return_value;
}
