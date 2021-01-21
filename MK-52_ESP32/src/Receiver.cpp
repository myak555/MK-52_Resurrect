//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

using namespace MK52_Interpreter;

//
// Inits generic receiver
//
unsigned long Receiver::init( void *components[]) {
    _kbd = (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];
    _lcd = (MK52_Hardware::LCD_Manager *)components[COMPONENT_LCD_MANAGER];
    _rpnf = (RPN_Functions*)components[COMPONENT_FUNCTIONS];
    return millis(); 
}

void Receiver::activate( uint8_t scancode, int8_t parent){
    _parentReceiver = parent;
}

char Receiver::_convertButton(const char *list, uint8_t scancode){
    char c = (char)pgm_read_byte(list + scancode);
    if( c == '#') return 0;
    return c;
}
