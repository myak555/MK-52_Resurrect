//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _AR_ButtonConversion[] PROGMEM = "####f########7410852#963#######ec";

using namespace MK52_Interpreter;

//
// Inits memory or program address entry
//
void Receiver_Address::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init address entry");
    #endif
    Receiver::init(components);
}

void Receiver_Address::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver ADDRESS");
    #endif
    Receiver::activate( scancode, parent);
    memset( _text, ' ', 4);
    _text[4] = 0; 
    _mode = 1;
    _lcd->updateStatusFMODE( "ADR");
}

char *Receiver_Address::toTrimmedString(){
    char *ptr = _text;
    while( *ptr == ' ') ptr++;
    return ptr;
}

int Receiver_Address::tick( uint8_t scancode){
    char c = _convertButton( _AR_ButtonConversion, scancode);
    switch( c){
        case 'f':
            _mode = 0;
            #ifdef __DEBUG
            Serial.println( "Receiver ADDRESS ticked (aborted)");
            #endif
            return (int)scancode;
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
            memmove( _text, _text+1, 3);
            _text[3] = c;
            _text[4] = 0;
            if( _text[0] == ' ') break;
            return _completeEntry();
        case 'c': // erase
            memmove( _text+1, _text, 3);
            _text[0] = ' ';
            if( _text[3] != ' ') break;
            // fall-through for empty line
        case 'e': // entry completed
            return _completeEntry();
        default:
            break;
    }
    return NO_CHANGE;
}

int Receiver_Address::_completeEntry(){
    #ifdef __DEBUG
    Serial.println( "Completing address entry...");
    #endif
    _mode = 0;
    for( int8_t i=0; i<4; i++){
        if( _text[i] != ' ') break;
        _text[i] = '0';
    }
    return _parentReceiver;
}
