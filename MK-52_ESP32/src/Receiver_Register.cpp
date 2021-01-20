//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _RR_ButtonConversion[] PROGMEM = "#########abcd7410852A963B###C#FED";

using namespace MK52_Interpreter;

//
// Inits register name entry
//
unsigned long Receiver_Register::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init register");
    #endif
    return Receiver::init(components);
}

void Receiver_Register::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    *_text = 0; 
    _mode = 1;
    if(!scancode) return;
    _appendChar( _convertButton( _RR_ButtonConversion, scancode));
}

int Receiver_Register::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendChar( _convertButton( _RR_ButtonConversion, scancode));
}

int Receiver_Register::_appendChar( char c){
    switch( c){
        case 0:
            return NO_CHANGE;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
            _text[0] = 'L';
            _text[1] = c - 'a' + '0';
            _text[2] = 0;
            _mode = 0;
            return _parentReceiver;
        default:
            _text[0] = c;
            _text[1] = 0;
            _mode = 0;
            return _parentReceiver;
    }
}
