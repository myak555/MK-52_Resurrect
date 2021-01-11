//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Input_Receivers.hpp"

using namespace MK52_Interpreter;

//
// Inits generic receiver
//
unsigned long Input_Receiver::init( void *components[]) {
    _kbd = (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];
    return millis(); 
}

void Input_Receiver::activate( int parentReturn, uint8_t scancode ){
    _parentReturn = parentReturn;
}
