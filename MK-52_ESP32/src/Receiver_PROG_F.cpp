//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"

//#define __DEBUG

using namespace MK52_Interpreter;

unsigned long Receiver_PROG_F::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_F");
    #endif
    _ar = (Receiver_Address*)components[COMPONENT_RECEIVER_ADDRESS];
    _pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return Receiver::init(components);
}

void Receiver_PROG_F::activate( int parentReturn, uint8_t scancode){
    Receiver::activate( parentReturn, scancode);
    _pmem->setInputMode(PSTR(" F "));
    _pmem->clearText();
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_PROG_F::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_PARENT_RETURN;
    return _appendButton( scancode);
}

int Receiver_PROG_F::_appendButton(uint8_t scancode){
    if( _ar->isActive()){
        if( _ar->tick( scancode) == NO_PARENT_RETURN) return NO_PARENT_RETURN;
        char *tmp = _ar->toString();
        if( *tmp == 0){
            _pmem->deleteLine();
            return COMPONENT_RECEIVER_PROG_N;
        }
        _pmem->appendText( tmp);
        _pmem->updateLine();
        _pmem->incrementCounter();
        return COMPONENT_RECEIVER_PROG_N;
    }
    switch( scancode){
        case 0:
        case 1:
        case 2:
        case 3:
            return NO_PARENT_RETURN;

        // Column 0
        case 4:
            _pmem->EditOverwrite = !_pmem->EditOverwrite;
            return NO_PARENT_RETURN;

        // Column 1
        case 5:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("IFNOT X<0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 6:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("IFNOT X=0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 7:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("IFNOT X>=0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 8:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("IFNOT X!=0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;

        // Column 2
        case 9:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("WHILE L0>0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 10:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("WHILE L1>0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 11:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("WHILE L2>0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 12:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("WHILE L3>0 GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;

        // Column 3
        case 13:
            _pmem->updateLine_P( PSTR("SIN"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 14:
            _pmem->updateLine_P( PSTR("ArcSIN"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 15:
            _pmem->updateLine_P( PSTR("EXP"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 16:
            _pmem->updateLine_P( PSTR("10^X"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 4
        case 17:
            _pmem->updateLine_P( PSTR("COS"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 18:
            _pmem->updateLine_P( PSTR("ArcCOS"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 19:
            _pmem->updateLine_P( PSTR("LG"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 20:
            _pmem->updateLine_P( PSTR("Rotate"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 5
        case 21:
            _pmem->updateLine_P( PSTR("TG"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 22:
            _pmem->updateLine_P( PSTR("ArcTG"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 23:
            _pmem->updateLine_P( PSTR("LN"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 24:
            _pmem->updateLine_P( PSTR("AVT"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 6
        case 25:
            _pmem->updateLine_P( PSTR("SQRT"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 26:
            _pmem->updateLine_P( PSTR("pi"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 27:
            _pmem->updateLine_P( PSTR("X^Y"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 28:
            _pmem->updateLine_P( PSTR("PRG"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 7
        case 29:
            _pmem->updateLine_P( PSTR("1/X"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 30:
            _pmem->updateLine_P( PSTR("X^2"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 31:
            _pmem->updateLine_P( PSTR("Bx"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 32:
            return COMPONENT_RECEIVER_PROG_N;

        default: // no more buttons
            break;
    }
    return NO_PARENT_RETURN;
}