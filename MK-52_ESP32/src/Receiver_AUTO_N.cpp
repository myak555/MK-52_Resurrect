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

unsigned long Receiver_AUTO_N::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init PROG_N");
    #endif
    _stack = (RPN_Stack *)components[COMPONENT_STACK];
    return Receiver::init(components);
}

void Receiver_AUTO_N::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _mode = 1;
    if(!scancode) return;
    _appendButton(scancode);
}

int Receiver_AUTO_N::tick( uint8_t scancode){
    if(scancode == 0) scancode = _kbd->scan();
    if( !scancode) return NO_CHANGE;
    return _appendButton( scancode);
}

int Receiver_AUTO_N::_appendButton(uint8_t scancode){
//     if( _nr->isActive()){
//         if( _nr->tick( scancode) == NO_CHANGE) return NO_CHANGE;
//         _pmem->updateLine( _nr->toTrimmedString());
//         _pmem->incrementCounter();
//         return NO_CHANGE;
//     }
//     if( _ar->isActive()){
//         if( _ar->tick( scancode) == NO_CHANGE) return NO_CHANGE;
//         char *tmp = _ar->toString();
//         if( *tmp == 0){
//             _pmem->deleteLine();
//             return NO_CHANGE;
//         }
//         _pmem->appendText( tmp);
//         _pmem->updateLine();
//         _pmem->incrementCounter();
//         return NO_CHANGE;
//     }
//     if( _rr->isActive()){
//         if( _rr->tick( scancode) == NO_CHANGE) return NO_CHANGE;
//         _pmem->appendText( _rr->toString());
//         _pmem->updateLine();
//         _pmem->incrementCounter();
//         return NO_CHANGE;
//     }
    switch( scancode){
        case 0:
        case 2:
        case 3:
        return NO_CHANGE;

        // // Column 0
        // case 1:
        //     Serial.println("F pressed!");
        //     return COMPONENT_RECEIVER_PROG_F;

        // // Column 1
        // case 5:
        //     Serial.println("Increment!");
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 6:
        //     Serial.println("Decrement!");
        //     _pmem->decrementCounter();
        //     return NO_CHANGE;
        // case 7:
        //     _pmem->updateLine_P( PSTR("RETURN"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 8:
        //     _pmem->updateLine_P( PSTR("STOP"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;

        // // Column 2
        // case 9:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("M->X ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
        //     return NO_CHANGE;
        // case 10:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("X->M ") );
        //     _rr->activate(COMPONENT_RECEIVER_PROG_N, 0);
        //     return NO_CHANGE;
        // case 11:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("GOTO ") );
        //     _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
        //     return NO_CHANGE;
        // case 12:
        //     _pmem->clearText();
        //     _pmem->appendText_P( PSTR("GOSUB ") );
        //     _ar->activate(COMPONENT_RECEIVER_PROG_N, 0);
        //     return NO_CHANGE;

        // // Column 5
        // case 24:
        //     _pmem->updateLine_P( PSTR("/-/"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;

        // // Column 6
        // case 25:
        //     _pmem->updateLine_P( PSTR("-"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 26:
        //     _pmem->updateLine_P( PSTR("+"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 27:
        //     _pmem->updateLine_P( PSTR("X<->Y"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;

        // // Column 7
        // case 29:
        //     _pmem->updateLine_P( PSTR("/"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 30:
        //     _pmem->updateLine_P( PSTR("*"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 31:
        //     _pmem->updateLine_P( PSTR("Enter"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;
        // case 32:
        //     _pmem->updateLine_P( PSTR("Cx"));
        //     _pmem->incrementCounter();
        //     return NO_CHANGE;

        default: // all other buttons activate number entry
            //_nr->activate(COMPONENT_RECEIVER_PROG_N, scancode);
            break;
    }
    return NO_CHANGE;
}
