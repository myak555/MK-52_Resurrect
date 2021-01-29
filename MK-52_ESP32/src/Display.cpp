//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"

using namespace MK52_Interpreter;

//
// Inits generic display
//
unsigned long Display::init( void *components[]) {
    _components = components;
    _kbd = (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];
    _lcd = (MK52_Hardware::LCD_Manager *)components[COMPONENT_LCD_MANAGER];
    _rpnf = (RPN_Functions*)components[COMPONENT_FUNCTIONS];
    return millis(); 
}

void Display::activate(){
}

int Display::tick(){
    return NO_CHANGE;
}

void Display::_setCurrentReceiver( uint8_t id, uint8_t scancode, int8_t parent){
   current_Receiver = getReceiver( id);
   if( current_Receiver == NULL) return;
   current_Receiver->activate( scancode, parent);
}
