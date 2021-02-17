//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _RR_ButtonConversion[] PROGMEM = "####f####abcd7410852A963B###C#FED";

using namespace MK52_Interpreter;

//
// Inits register name entry
//
void Receiver_Register::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init register");
    #endif
    Receiver::init(components);
}

void Receiver_Register::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver REGISTER");
    #endif
    Receiver::activate( scancode, parent);
    *_text = 0;
    _lcd->updateStatusFMODE( "MEM");
    _mode = 1;
}

int Receiver_Register::tick( uint8_t scancode){
    char c = _convertButton( _RR_ButtonConversion, scancode);
    switch( c){
        case 0:
            //delay(KBD_IDLE_DELAY);
            return NO_CHANGE;
        case 'f':
            _parentReceiver = (int)scancode;
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
            _text[0] = 'L';
            _text[1] = c - 'a' + '0';
            _text[2] = 0;
            break;
        default:
            _text[0] = c;
            _text[1] = 0;
            break;
    }
    _mode = 0;
    #ifdef __DEBUG
    Serial.println( "Receiver REGISTER ticked");
    #endif
    //delay(KBD_IDLE_DELAY);
    return _parentReceiver;
}
