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

unsigned long Receiver_FILE_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init FILE_N");
    #endif
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    return Receiver::init(components);
}

void Receiver_FILE_N::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver FILE_N");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "   ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_FILE_N::tick( uint8_t scancode){
    int return_value = NO_CHANGE;
    int r = _completeSubentry(scancode);
    if( r <= 0) return return_value;
    scancode = (uint8_t)r;
    switch( scancode){
        // Column 0
        case 1:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_FILE_F;
            break;
        case 2:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_FILE_K;
            break;
        case 3:
            _mode = 0;
            return_value = COMPONENT_RECEIVER_FILE_A;
            break;

        // Column 1
        case 5:
            // next line
            break;
        case 6:
            // previous line
            break;
        case 7:
            // first line
            break;
        case 8:
            // load program at cursor and start
            break;

        // Column 2
        case 9:
            // load program
            break;
        case 10:
            // save program
            break;
        case 11:
            // find program
            break;
        case 12:
            // save program as
            break;

        // Column 6
        case 28:
            // create folder
            break;

        // Column 7
        case 31:
            // go into the folder
            break;
        case 32:
            // delete program or dir
            break;

        default: // all other buttons do nothing
            break;
    }
    return return_value;
}

int Receiver_FILE_N::_completeSubentry( uint8_t scancode){
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
            // #ifdef __DEBUG
            // Serial.print("Ticking to NUMBER... ");
            // Serial.println(scancode);
            // #endif 
            // r = _nr->tick( scancode);
            // if( r == NO_CHANGE) return NO_CHANGE;
            // #ifdef __DEBUG
            // Serial.print("Received number: ");
            // Serial.println(_nr->toTrimmedString());
            // #endif 
            // _rpnf->execute( _nr->toTrimmedString());
            // #ifdef __DEBUG
            // Serial.print("Number in stack: ");
            // Serial.println( _rpnf->rpnStack->X->toReal());
            // Serial.print("Number updated, returning ");
            // Serial.println(r);
            // #endif 
            break;
        case 3:
        case 4:
            // r = _rr->tick( scancode);
            // if( r == NO_CHANGE) return NO_CHANGE;
            // _rpnf->execute( (_mode==3)? FUNC_M2X : FUNC_X2M, _rr->toString());
            // #ifdef __DEBUG
            // Serial.print("Registers updated, returning ");
            // Serial.println(r);
            // #endif 
            break;
        case 5:
            // r = _ar->tick( scancode);
            // if( r == NO_CHANGE){
            //     _lcd->updateStatusPC( _ar->toString());
            //     return NO_CHANGE;
            // }
            // _rpnf->execute( FUNC_GOTO, _ar->toString());
            // _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            // #ifdef __DEBUG
            // Serial.print("GOTO done, returning ");
            // Serial.println(r);
            // #endif 
            break;
        default:
            break;
    }
    _mode = 1;
    _lcd->updateStatusFMODE( "   ");
    return r;
}
