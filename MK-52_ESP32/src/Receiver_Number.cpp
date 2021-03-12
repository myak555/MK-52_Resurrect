//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

const char _RN_ButtonConversion[] PROGMEM = "#ffffffffffff7410852.963-fffEffec";
const char _RN_StandardUnity[] PROGMEM = "1.0E+000";

using namespace MK52_Interpreter;

//
// Inits number entry
//
void Receiver_Number::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init number entry");
    #endif
    _text = (char *)malloc(SCREEN_COLS+1);
    Receiver::init(components);
}

void Receiver_Number::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver NUMBER");
    #endif
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "NUM");
    strcpy_P( _text, PSTR(" "));
    _mode = 1;
    if(!scancode) return;
    tick( scancode);
}

int Receiver_Number::tick( uint8_t scancode){
    int ln = strlen(_text);
    char c = _convertButton( _RN_ButtonConversion, scancode);
    int return_value = NO_CHANGE; 
    switch( c){
        case 'e': // entry completed
            scancode = 0;
        case 'f':
            _mode = 0;
            #ifdef __DEBUG
            Serial.println( "Receiver NUMBER ticked");
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
            if( ln == 2 && _text[1] == '0'){
                _text[1] = c;
                break;
            }
            if( _mode == 1 && ln>17) break;
            if( _mode == 2 && ln>13) break;
            if( _mode == 3){
                _text[ln-3] = _text[ln-2]; 
                _text[ln-2] = _text[ln-1]; 
                _text[ln-1] = c; 
                break;
            }
            _text[ln] = c;
            _text[ln+1] = 0;
            break;
        case '-':
            if( _mode == 3){
                _swapSign( _text + ln - 4, '+');
                break;
            }
            _swapSign( _text, ' ');
            break;
        case '.':
            if( _mode == 1 && ln>12) break;
            if( _mode >= 2) break;
            _mode = 2;
            if( ln == 1){
                strcpy_P( _text+1, PSTR("0."));
                break;
            }
            strcpy_P( _text+ln, PSTR("."));
            break;
        case 'E':
            if( _mode == 1 && ln>12) break;
            if( _mode == 3){
                _text[ln-5] = 0;
                _mode = 2;
                break;
            }
            if( ln == 1 || UniversalValue::_identicalTo_P(_text+1, PSTR("0.0"))
                || UniversalValue::_identicalTo_P(_text+1, PSTR("0."))){
                strcpy_P( _text+1, _RN_StandardUnity);
                _mode = 3;
                break;
            }
            if( ln == 2 && _text[1] == '0'){
                strcpy_P( _text+1, _RN_StandardUnity);
                _mode = 3;
                break;
            }
            if( _mode == 1){
                strcpy_P( _text+ln, _RN_StandardUnity+1);
                _mode = 3;
                break;
            }
            _mode = 3;
            if( _text[ln-1] == '.'){
                strcpy_P( _text+ln, _RN_StandardUnity+2);
                break;
            }
            strcpy_P( _text+ln, _RN_StandardUnity+3);
            break;
        case 'c': // erase
            if( _mode == 3){
                _text[ln-1] = _text[ln-2];
                _text[ln-2] = _text[ln-3];
                _text[ln-3] = '0';
                break;
            }
            if( _mode == 2 && _text[ln-1] == '.'){
                _text[ln-1] = 0;
                _mode = 1;
                break;
            }
            if( ln>2){
                _text[ln-1] = 0;
                break;
            }
            strcpy_P( _text, PSTR(" 0"));
            _mode = 0;
            return_value = _parentReceiver;
            break;
        default:
            break;
    }
    return return_value;
}
