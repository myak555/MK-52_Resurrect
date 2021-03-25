//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receiver.hpp"

using namespace MK52_Interpreter;

//
// Inits generic receiver
//
Receiver::Receiver( void *components[]) {
    _components = components;
    _kbd = (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];
    _lcd = (MK52_Hardware::LCD_Manager *)components[COMPONENT_LCD_MANAGER];
    _rpnf = (RPN_Functions*)components[COMPONENT_FUNCTIONS];
    memset( _funlabel, ' ', 3);
    _funlabel[3] = 0;
}

void Receiver::activate( int8_t prevReceiver){
    _return_to = prevReceiver;
}

uint8_t Receiver::tick( uint8_t scancode){
    return 0;
}

char Receiver::_convertButton(const char *list, uint8_t scancode){
    char c = (char)pgm_read_byte(list + scancode);
    if( c == '#') return 0;
    return c;
}
