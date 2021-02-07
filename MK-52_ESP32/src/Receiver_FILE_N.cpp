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
            _rpnf->execute( FUNC_NEXTFILE);            
            break;
        case 6:
            _rpnf->execute( FUNC_PREVFILE);            
            break;
        case 7:
            _rpnf->execute( FUNC_UPDIR);
            break;
        case 8:
            _rpnf->execute( FUNC_STEPIN);
            break;

        // Column 2
        case 9:
            _rpnf->execute( FUNC_LOAD);
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            #ifdef __DEBUG
            Serial.println("Going to AUTO Display");
            #endif
            _mode = 0;
            return COMPONENT_DISPLAY_AUTO;
        case 10:
            _rpnf->execute( FUNC_SAVE);
            break;
        case 11:
            // find program
            break;
        case 12:
            // save program as
            _mode = 3;
            _tr->activate(0, -3);
            _tr->_setInputMode( 2); // alpha mode by default;
            break;

        // Column 6
        case 28:
            // create folder
            _mode = 2;
            _tr->activate(0, -3);
            _tr->_setInputMode( 2); // alpha mode by default;
            break;

        // Column 7
        case 31:
            // go into the folder
            _rpnf->execute( FUNC_STEPIN);
            break;
        case 32:
            // delete program or dir
            _lcd->outputTerminalLine( 10, "Confirm DELETE (\030)");
            if( _getConfirmation( 31)) _rpnf->execute( FUNC_REMOVE);
            break;

        default: // all other buttons do nothing
            break;
    }
    return return_value;
}

int Receiver_FILE_N::_completeSubentry( uint8_t scancode){
    char *filename = NULL;
    int8_t r = (int)scancode;
    switch( _mode){
        case 0:
        case 1:
            return r;
        case 2:
            r = _tr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            #ifdef __DEBUG
            Serial.print("Received name: ");
            Serial.println(_tr->toTrimmedString());
            #endif 
            _rpnf->execute( FUNC_MKDIR, _tr->toTrimmedString());
            _tr->_setInputMode( 0);
            break;
        case 3:
            r = _tr->tick( scancode);
            if( r == NO_CHANGE) return NO_CHANGE;
            _tr->appendText_P(PSTR(".MK52"));
            filename = _rpnf->formFileName( _tr->toTrimmedString());
            _tr->_setInputMode( 0);
            #ifdef __DEBUG
            Serial.print("Received name: ");
            Serial.println(filename);
            #endif
            if( !_rpnf->fileExists(filename)){
                _rpnf->execute( FUNC_SAVEAS, filename);
                break;
            }
            _lcd->outputTerminalLine( 10, "Confirm OVERWRITE (\030)");
            if( _getConfirmation( 31)) _rpnf->execute( FUNC_SAVEDATAAS, filename);
            break;
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
