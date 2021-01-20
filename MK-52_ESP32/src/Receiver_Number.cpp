//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _RN_ButtonConversion[] PROGMEM = "#############7410852.963-###E##ec";
const char _RN_StandardUnity[] PROGMEM = "1.0E+000";

using namespace MK52_Interpreter;

//
// Inits number entry
//
unsigned long Receiver_Number::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init number");
    #endif
    return Receiver::init(components);
}

void Receiver_Number::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    strcpy_P( _text, PSTR(" "));
    _mode = 1;
    if(!scancode) return;
    _appendChar( _convertButton(_RN_ButtonConversion,  scancode));
}

int Receiver_Number::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendChar( _convertButton( _RN_ButtonConversion, scancode));
}

int Receiver_Number::_appendChar( char c){
    int ln = strlen(_text);
    switch( c){
        case 0:
            return NO_CHANGE;
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
            if( ln == 2 && _text[1] == '0'){
                _text[1] = c;
                return NO_CHANGE;
            }
            if( _mode == 1 && ln>12) return NO_CHANGE;
            if( _mode == 2 && ln>13) return NO_CHANGE;
            if( _mode == 3){
                _text[ln-3] = _text[ln-2]; 
                _text[ln-2] = _text[ln-1]; 
                _text[ln-1] = c; 
                return NO_CHANGE;
            }
            _text[ln] = c;
            _text[ln+1] = 0;
            return NO_CHANGE;
        case '-':
            if( _mode == 3){
                _swapSign( _text + ln - 4, '+');
                return NO_CHANGE;
            }
            _swapSign( _text, ' ');
            return NO_CHANGE;
            case '.':
            if( _mode >= 2) return NO_CHANGE;
            _mode = 2;
            if( ln == 1){
                strcpy_P( _text+1, PSTR("0."));
                return NO_CHANGE;
            }
            strcpy_P( _text+ln, PSTR("."));
            return NO_CHANGE;
        case 'E':
            if( _mode == 3){
                _text[ln-5] = 0;
                _mode = 2;
                return NO_CHANGE;
            }
            if( ln == 1 || strcmp_P(_text+1, PSTR("0.0")) == 0 || strcmp_P(_text+1, PSTR("0.")) == 0){
                strcpy_P( _text+1, _RN_StandardUnity);
                _mode = 3;
                return NO_CHANGE;
            }
            if( ln == 2 && _text[1] == '0'){
                strcpy_P( _text+1, _RN_StandardUnity);
                _mode = 3;
                return NO_CHANGE;
            }
            if( _mode == 1){
                strcpy_P( _text+ln, _RN_StandardUnity+1);
                _mode = 3;
                return NO_CHANGE;
            }
            _mode = 3;
            if( _text[ln-1] == '.'){
                strcpy_P( _text+ln, _RN_StandardUnity+2);
                return NO_CHANGE;
            }
            strcpy_P( _text+ln, _RN_StandardUnity+3);
            return NO_CHANGE;
        case 'e': // entry completed
          _mode = 0;
          return _parentReceiver;
        case 'c': // erase
            if( _mode == 3){
                _text[ln-1] = _text[ln-2];
                _text[ln-2] = _text[ln-3];
                _text[ln-3] = '0';
                return NO_CHANGE;
            }
            if( _mode == 2 && _text[ln-1] == '.'){
                _text[ln-1] = 0;
                _mode = 1;
                return NO_CHANGE;
            }
            if( ln>1){
                _text[ln-1] = 0;
                return NO_CHANGE;
            }
            strcpy_P( _text, PSTR(" 0"));
            _mode = 0;
            return _parentReceiver;
        default:
            return NO_CHANGE;
    }
}
