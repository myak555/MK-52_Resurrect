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
    _lcd = (MK52_Hardware::LCD_Manager *)components[COMPONENT_LCD_MANAGER];
    _pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return millis(); 
}

int Display::activate(){
    return NO_PARENT_RETURN;
}

void Display::tick(){
}
