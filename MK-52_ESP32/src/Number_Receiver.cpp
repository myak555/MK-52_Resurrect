//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Input_Receivers.hpp"

const char _NR_ButtonConversion[] PROGMEM = "#############7410852.963-###E##ec";
const char _NR_StandardUnity[] PROGMEM = "1.0E+000";

using namespace MK52_Interpreter;

//
// Inits number entry
//
unsigned long Number_Receiver::init( void *components[]) {
    _kbd = (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];
    return millis(); 
}

void Number_Receiver::activate( uint8_t scancode){
    strcpy_P( _text, PSTR(" "));
    _mode = 1;
    if(!scancode) return;
    _appendChar( _convertButton( scancode));
}

void Number_Receiver::tick(){
    uint8_t scancode = _kbd->scan();
    if( !scancode) return;
    _appendChar( _convertButton( scancode));
}

char Number_Receiver::_convertButton(uint8_t scancode){
    char c = (char)pgm_read_byte(_NR_ButtonConversion + scancode);
    if( c == '#') return 0;
    return c;
}

void Number_Receiver::_appendChar( char c){
    int ln = strlen(_text);
    switch( c){
      case 0:
          return;
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
              return;
          }
          if( _mode == 1 && ln>12) return;
          if( _mode == 2 && ln>13) return;
          if( _mode == 3){
              _text[ln-3] = _text[ln-2]; 
              _text[ln-2] = _text[ln-1]; 
              _text[ln-1] = c; 
              return;
          }
          _text[ln] = c;
          _text[ln+1] = 0;
          return;
      case '-':
          if( _mode == 3){
              _swapSign( _text + ln - 4, '+');
              return;
          }
          _swapSign( _text, ' ');
          return;
      case '.':
          if( _mode >= 2) return;
          _mode = 2;
          if( ln == 1){
              strcpy_P( _text+1, PSTR("0."));
              return;
          }
          strcpy_P( _text+ln, PSTR("."));
          return;
      case 'E':
          if( _mode == 3){
              _text[ln-5] = 0;
              _mode = 2;
              return;
          }
          if( ln == 1 || strcmp_P(_text+1, PSTR("0.0")) == 0 || strcmp_P(_text+1, PSTR("0.")) == 0){
              strcpy_P( _text+1, _NR_StandardUnity);
              _mode = 3;
              return;
          }
          if( ln == 2 && _text[1] == '0'){
              strcpy_P( _text+1, _NR_StandardUnity);
              _mode = 3;
              return;
          }
          if( _mode == 1){
              strcpy_P( _text+ln, _NR_StandardUnity+1);
              _mode = 3;
              return;
          }
          _mode = 3;
          if( _text[ln-1] == '.'){
              strcpy_P( _text+ln, _NR_StandardUnity+2);
              return;
          }
          strcpy_P( _text+ln, _NR_StandardUnity+3);
          return;
      case 'e': // entry completed
          _mode = 0;
          return;
      case 'c': // erase
          if( _mode == 3){
              _text[ln-1] = _text[ln-2];
              _text[ln-2] = _text[ln-3];
              _text[ln-3] = '0';
              return;
          }
          if( _mode == 2 && _text[ln-1] == '.'){
              _text[ln-1] = 0;
              _mode = 1;
              return;
          }
          if( ln>1){
              _text[ln-1] = 0;
              return;
          }
          strcpy_P( _text, PSTR(" 0"));
          _mode = 0;
          return;
      default:
          return;
    }
}
