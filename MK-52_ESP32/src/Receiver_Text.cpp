//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

#define __DEBUG

const char _RT_DigitConversion[] PROGMEM =  "### #<=>!,;:?7410852.963--+^E/*##";
const char _RT_LetterConversion[] PROGMEM = "### #AHOUBIPVCJQWDKRXELSYFMTZGN##";
const char _RT_StandardUnity[] PROGMEM = "1.0E+000";

using namespace MK52_Interpreter;

//
// Inits text entry
//
unsigned long Receiver_Text::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init text entry");
    #endif
    _text = (char *)malloc(PROGRAM_LINE_LENGTH+1);
    return Receiver::init(components);
}

void Receiver_Text::activate( uint8_t scancode, int8_t parent){
    #ifdef __DEBUG
    Serial.println( "Activating receiver TEXT");
    #endif
    Receiver::activate( scancode, parent);
    _setInputMode( 1);
    _text[0] = 0;
    if(!scancode) return;
    tick( scancode);
}

int Receiver_Text::tick( uint8_t scancode){
    return NO_CHANGE;
    // int ln = strlen(_text);
    // char c = _convertButton( _RT_DigitConversion, scancode);
    // int return_value = NO_CHANGE; 
    // switch( c){
    //     case 'e': // entry completed
    //         scancode = 0;
    //     case 'f':
    //         _mode = 0;
    //         #ifdef __DEBUG
    //         Serial.println( "Receiver NUMBER ticked");
    //         #endif
    //         return (int)scancode;
    //     case '0':
    //     case '1':
    //     case '2':
    //     case '3':
    //     case '4':
    //     case '5':
    //     case '6':
    //     case '7':
    //     case '8':
    //     case '9':
    //         #ifdef __DEBUG
    //         Serial.print("Ticking digit: ");
    //         Serial.println(_text);
    //         #endif
    //         if( ln == 2 && _text[1] == '0'){
    //             _text[1] = c;
    //             break;
    //         }
    //         if( _mode == 1 && ln>12) break;
    //         if( _mode == 2 && ln>13) break;
    //         if( _mode == 3){
    //             _text[ln-3] = _text[ln-2]; 
    //             _text[ln-2] = _text[ln-1]; 
    //             _text[ln-1] = c; 
    //             break;
    //         }
    //         _text[ln] = c;
    //         _text[ln+1] = 0;
    //         break;
    //     case '-':
    //         if( _mode == 3){
    //             _swapSign( _text + ln - 4, '+');
    //             break;
    //         }
    //         _swapSign( _text, ' ');
    //         break;
    //     case '.':
    //         if( _mode >= 2) break;
    //         _mode = 2;
    //         if( ln == 1){
    //             strcpy_P( _text+1, PSTR("0."));
    //             break;
    //         }
    //         strcpy_P( _text+ln, PSTR("."));
    //         break;
    //     case 'E':
    //         if( _mode == 3){
    //             _text[ln-5] = 0;
    //             _mode = 2;
    //             break;
    //         }
    //         if( ln == 1 || strcmp_P(_text+1, PSTR("0.0")) == 0 || strcmp_P(_text+1, PSTR("0.")) == 0){
    //             strcpy_P( _text+1, _RT_StandardUnity);
    //             _mode = 3;
    //             break;
    //         }
    //         if( ln == 2 && _text[1] == '0'){
    //             strcpy_P( _text+1, _RT_StandardUnity);
    //             _mode = 3;
    //             break;
    //         }
    //         if( _mode == 1){
    //             strcpy_P( _text+ln, _RT_StandardUnity+1);
    //             _mode = 3;
    //             break;
    //         }
    //         _mode = 3;
    //         if( _text[ln-1] == '.'){
    //             strcpy_P( _text+ln, _RT_StandardUnity+2);
    //             break;
    //         }
    //         strcpy_P( _text+ln, _RT_StandardUnity+3);
    //         break;
    //     case 'c': // erase
    //         if( _mode == 3){
    //             _text[ln-1] = _text[ln-2];
    //             _text[ln-2] = _text[ln-3];
    //             _text[ln-3] = '0';
    //             break;
    //         }
    //         if( _mode == 2 && _text[ln-1] == '.'){
    //             _text[ln-1] = 0;
    //             _mode = 1;
    //             break;
    //         }
    //         if( ln>1){
    //             _text[ln-1] = 0;
    //             break;
    //         }
    //         strcpy_P( _text, PSTR(" 0"));
    //         _mode = 0;
    //         return_value = _parentReceiver;
    //         break;
    //     default:
    //         break;
    // }
    // //delay(KBD_IDLE_DELAY);
    // return return_value;
}

char *Receiver_Text::toTrimmedString(){
    char *ptr = _text;
    while( *ptr == ' ')
    return (*_text == ' ')? _text+1: _text;
}

//
// Modes:
// mode 1 - receiver takes text from the parent
// mode 2 - input letters
// mode 3 - input digits
//
void Receiver_Text::_setInputMode( uint8_t m, char *parentMode){
    _mode = m;
    switch( m){
        case 2:
            _lcd->updateStatusFMODE( "ALP");
            return;
        case 3:
            _lcd->updateStatusFMODE( "DIG");
            return;
        case 0: //force deactivation
            _text[0] = 0;                        
        default:
            if( parentMode == NULL)
                _lcd->updateStatusFMODE( "   ");
            else
                _lcd->updateStatusFMODE( parentMode);
            return;
    }
}
