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

unsigned long Receiver_FILE_F::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init FILE_F");
    #endif
    _tr = (Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
    return Receiver::init(components);
}

void Receiver_FILE_F::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver FILE_F");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( " F ");
    _mode = 1;
    if(!scancode) return;
    tick(scancode);
}

int Receiver_FILE_F::tick( uint8_t scancode){
    int return_value = COMPONENT_RECEIVER_FILE_N;
    int r = _completeSubentry(scancode);
    if( r < NO_CHANGE) return return_value;
    if( r <= 0) return NO_CHANGE;
    scancode = (uint8_t)r;
    switch( scancode){
        // Column 0
        case 2:
            return_value = COMPONENT_RECEIVER_FILE_K;
            break;
        case 3:
            return_value = COMPONENT_RECEIVER_FILE_A;
            break;

        // Column 1
        case 5:
            for( int i=0; i<9; i++)
                _rpnf->execute( FUNC_NEXTFILE);            
            break;
        case 6:
            for( int i=0; i<9; i++)
                _rpnf->execute( FUNC_PREVFILE);            
            break;

        // Column 2
        case 9:
            _rpnf->execute( FUNC_LOADDATA);
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            _mode = 0;
            return COMPONENT_DISPLAY_DATA;
        case 10:
            _rpnf->execute( FUNC_SAVEDATA);
            break;
        case 11:
            // find program
            break;
        case 12:
            // save data as
            _mode = 2;
            _tr->activate(0, -3);
            _tr->_setInputMode( 2); // alpha mode by default;
            break;

        // Column 5
        case 24:
            #ifdef __DEBUG
            Serial.println("Going to AUTO Display");
            #endif
            return_value = COMPONENT_DISPLAY_AUTO;
            break;

        // Column 6
        case 28:
            #ifdef __DEBUG
            Serial.println("Going to PROG Display");
            #endif
            return_value = COMPONENT_DISPLAY_PROG;
            break;

        // Column 7
        case 32:
            // release F
            break;

        default: // all other buttons do nothing, keeping F-mode
            return NO_CHANGE;
    }
    _mode = 0;
    return return_value;
}

int Receiver_FILE_F::_completeSubentry( uint8_t scancode){
    char *filename = NULL;
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
            r = _tr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            _tr->appendText_P(PSTR(".DAT"));
            filename = _rpnf->formFileName( _tr->toTrimmedString());
            _tr->_setInputMode( 0);
            #ifdef __DEBUG
            Serial.print("Received name: ");
            Serial.println(filename);
            #endif
            if( !_rpnf->fileExists(filename)){
                _rpnf->execute( FUNC_SAVEDATAAS, filename);
                break;
            }
            _lcd->outputTerminalLine( 10, "Confirm OVERWRITE (\030)");
            if( _getConfirmation( 31)) _rpnf->execute( FUNC_SAVEDATAAS, filename);
            break;
        default:
            break;
    }
    _mode = 0;
    return r;
}
