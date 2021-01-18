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

unsigned long Receiver_PROG_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_N");
    #endif
    _nr = (Receiver_Number*)components[COMPONENT_RECEIVER_NUMBER];
    _ar = (Receiver_Address*)components[COMPONENT_RECEIVER_ADDRESS];
    _rr = (Receiver_Register*)components[COMPONENT_RECEIVER_REGISTER];
    _pmem = (Program_Memory*)components[COMPONENT_PROGRAM_MEMORY];
    return Receiver::init(components);
}

void Receiver_PROG_N::activate( int parentReturn, uint8_t scancode){
    Receiver::activate( parentReturn, scancode);
    _pmem->setInputMode(PSTR("   "));
    _pmem->clearText();
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_PROG_N::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_PARENT_RETURN;
    return _appendButton( scancode);
}

int Receiver_PROG_N::_appendButton(uint8_t scancode){
    if( _nr->isActive()){
        if( _nr->tick( scancode) == NO_PARENT_RETURN) return NO_PARENT_RETURN;
        _pmem->updateLine( _nr->toTrimmedString());
        _pmem->incrementCounter();
        return NO_PARENT_RETURN;
    }
    if( _ar->isActive()){
        if( _ar->tick( scancode) == NO_PARENT_RETURN) return NO_PARENT_RETURN;
        char *tmp = _ar->toString();
        if( *tmp == 0){
            _pmem->deleteLine();
            return NO_PARENT_RETURN;
        }
        _pmem->appendText( tmp);
        _pmem->updateLine();
        _pmem->incrementCounter();
        return NO_PARENT_RETURN;
    }
    if( _rr->isActive()){
        if( _rr->tick( scancode) == NO_PARENT_RETURN) return NO_PARENT_RETURN;
        _pmem->appendText( _rr->toString());
        _pmem->updateLine();
        _pmem->incrementCounter();
        return NO_PARENT_RETURN;
    }
    switch( scancode){
        case 0:
        case 2:
        case 3:
            return NO_PARENT_RETURN;

        // Column 0
        case 1:
            Serial.println("F pressed!");
            return COMPONENT_RECEIVER_PROG_F;
        case 4:
            Serial.println("Mode pressed!");
            _pmem->EditOverwrite = !_pmem->EditOverwrite;
            return NO_PARENT_RETURN;

        // Column 1
        case 5:
            Serial.println("Increment!");
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 6:
            Serial.println("Decrement!");
            _pmem->decrementCounter();
            return NO_PARENT_RETURN;
        case 7:
            _pmem->updateLine_P( PSTR("RETURN"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 8:
            _pmem->updateLine_P( PSTR("STOP"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 2
        case 9:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("M->X ") );
            _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 10:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("X->M ") );
            _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 11:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("GOTO ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;
        case 12:
            _pmem->clearText();
            _pmem->appendText_P( PSTR("GOSUB ") );
            _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
            return NO_PARENT_RETURN;

        // Column 5
        case 24:
            _pmem->updateLine_P( PSTR("/-/"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 6
        case 25:
            _pmem->updateLine_P( PSTR("-"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 26:
            _pmem->updateLine_P( PSTR("+"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 27:
            _pmem->updateLine_P( PSTR("X<->Y"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        // Column 7
        case 29:
            _pmem->updateLine_P( PSTR("/"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 30:
            _pmem->updateLine_P( PSTR("*"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 31:
            _pmem->updateLine_P( PSTR("Enter"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;
        case 32:
            _pmem->updateLine_P( PSTR("Cx"));
            _pmem->incrementCounter();
            return NO_PARENT_RETURN;

        default: // all other buttons activate number entry
            _nr->activate(COMPONENT_RECEIVER_PROG_N, scancode);
            break;
    }
    return NO_PARENT_RETURN;
}
