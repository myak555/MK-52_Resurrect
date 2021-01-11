//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Input_Receivers.hpp"

using namespace MK52_Interpreter;

unsigned long PROG_N_Receiver::init( void *components[]) {
    _nr = (Number_Receiver*)components[COMPONENT_NUMBER_RECEIVER];
    _pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return Input_Receiver::init(components);
}

void PROG_N_Receiver::activate( int parentReturn, uint8_t scancode){
    Input_Receiver::activate( parentReturn, scancode);
    *_text = 0;
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int PROG_N_Receiver::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_PARENT_RETURN;
    return _appendButton( scancode);
}

int PROG_N_Receiver::_appendButton(uint8_t scancode){
    if( _nr->isActive()){
        if( _nr->tick( scancode) == NO_PARENT_RETURN) return NO_PARENT_RETURN;
        _pmem->replaceLine( _nr->toTrimmedString());
        _pmem->incrementCounter();
        return NO_PARENT_RETURN;
    }
    switch( scancode){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 24:
        case 25:
        case 26:
        case 27:
        case 29:
        case 30:
        case 31:
        case 32:
            return NO_PARENT_RETURN;
        case 5:
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 6:
            _pmem->decrementCounter();
            return NO_PARENT_RETURN;
        default:
            _nr->activate(COMPONENT_PROG_N_RECEIVER, scancode);
            break;
    }
    return NO_PARENT_RETURN;
}
