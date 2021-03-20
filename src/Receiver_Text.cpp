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
//const char _RT_LetterConversion[] PROGMEM = "### #AHOUBIPVCJQWDKRXELSYFMTZGN##";
const char _RT_LetterConversion[] PROGMEM = "#AIQ#BJRXCKSYDLTZEMU.FNV_GOW HP##";

const char _RT_StandardUnity[] PROGMEM = "1.0E+000";

using namespace MK52_Interpreter;

//
// Inits text entry
//
void Receiver_Text::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println("Init text entry");
    #endif
    _text = (char *)malloc(PROGRAM_LINE_LENGTH+1);
    Receiver::init(components);
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
    int ln = strlen(_text);
    char c = _convertButton( (_mode==2)? _RT_LetterConversion: _RT_DigitConversion, scancode);
    int return_value = NO_CHANGE; 
    switch( scancode){
        //case 1:
        //case 2:
        //    break;
        case 4: // mode change
            _setInputMode( (_mode == 2)? 3: 2);
            break;
        case 31: // enter
            _mode = 0;
            return_value = _parentReceiver;
            break;
        case 32: // Cx
            if( ln<=0){
                _mode = 0;
                return_value = _parentReceiver;
                break;
            }
            _text[--ln] = 0;
            break;
        default: // any other symbol is added to string
            if( ln<=PROGRAM_LINE_LENGTH){
                _text[ln++] = c;
                _text[ln] = 0;
                break;
            }
            _mode = 0;
            return_value = _parentReceiver;
            break;
    }
    return return_value;
}

char *Receiver_Text::toTrimmedString(){
    char *ptr = _text;
    while( *ptr == ' ') ptr++;
    return ptr;
}

char *Receiver_Text::toScreenString(){
    int ln = strlen( _text);
    if( ln<SCREEN_COLS-1) return _text;
    return _text + ln - SCREEN_COLS + 1;
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

char *Receiver_Text::appendText( char *text){
    int8_t ln = strlen(_text);
    char *ptr = _text + ln;
    while( ln<PROGRAM_LINE_LENGTH && *text){
        *ptr++ = *text++;
        ln++;
    }
    *ptr = 0;
    return ptr;
}

char *Receiver_Text::appendText_P( const char *text){
    int8_t ln = strlen(_text);
    char *ptr = _text + ln;
    char c = (char)pgm_read_byte(text++);
    while( ln<PROGRAM_LINE_LENGTH && c){
        *ptr++ = c;
        c = (char)pgm_read_byte(text++);
        ln++;
    }
    *ptr = 0;
    return ptr;
}
