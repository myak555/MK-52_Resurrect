//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _AR_ButtonConversion[] PROGMEM = "#############7410852#963#######ec";

using namespace MK52_Interpreter;

//
// Inits memory or program address entry
//
unsigned long Receiver_Address::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init address");
    #endif
    return Receiver::init(components);
}

void Receiver_Address::activate( int parentReturn, uint8_t scancode){
    Receiver::activate( parentReturn, scancode);
    *_text = 0; 
    _mode = 1;
    if(!scancode) return;
    _appendChar( _convertButton( _AR_ButtonConversion, scancode));
}

int Receiver_Address::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_PARENT_RETURN;
    return _appendChar( _convertButton( _AR_ButtonConversion, scancode));
}

int Receiver_Address::_appendChar( char c){
    int ln = strlen(_text);
    switch( c){
        case 0:
            return NO_PARENT_RETURN;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            _text[ln++] = c;
            _text[ln] = 0;
            if( ln < 4) return NO_PARENT_RETURN;
            _mode = 0;
            return _parentReturn;
        case 'e': // entry completed
            _mode = 0;
            return _parentReturn;
        case 'c': // erase
            if( ln > 0){
                _text[ln-1] = 0;
                return NO_PARENT_RETURN;
            }
            _mode = 0;
            return _parentReturn;
        default:
          return NO_PARENT_RETURN;
    }
}
