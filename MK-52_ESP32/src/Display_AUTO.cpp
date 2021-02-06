//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"
#include "../functions/functions.h"

#define __DEBUG
using namespace MK52_Interpreter;

//
// Inits display for AUTO mode
//
unsigned long Display_AUTO::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init Display AUTO");
    #endif
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Display::init( components);
}

void Display_AUTO::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    char *buff = _rpnf->getOutputBuffer();
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    RPN_Stack *st = _rpnf->rpnStack;
    _lcd->outputStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(), st->getDModeName(), "   ");
    _lcd->outputCalcRegister( 0, st->X->toString( buff));
    _lcd->outputCalcLabel( 0, st->X_Label);
    _lcd->outputCalcRegister( 1, st->Y->toString(buff));
    _lcd->outputCalcLabel( 1, st->Y_Label);
    _lcd->outputCalcRegister( 2, st->Z->toString(buff));
    _lcd->outputCalcLabel( 2, st->Z_Label);
    _lcd->outputCalcRegister( 3, st->T->toString(buff));
    _lcd->outputCalcLabel( 3, st->T_Label);
    _setCurrentReceiver( COMPONENT_RECEIVER_AUTO_N);
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("AUTO display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
}

int Display_AUTO::tick(){
    // keyboard serve part
    uint8_t scancode = _kbd->scan();
    if( current_Receiver == NULL) return NO_CHANGE;
    int newReceiver = current_Receiver->tick( scancode);
    if( newReceiver < -1) return newReceiver;
    switch( newReceiver){
        case COMPONENT_DISPLAY_AUTO:
            _setCurrentReceiver( COMPONENT_RECEIVER_AUTO_N);
            break;
        case COMPONENT_DISPLAY_DATA:
        case COMPONENT_DISPLAY_FILE:
        case COMPONENT_DISPLAY_PROG:
            return newReceiver;
        case 0:
        case -1:
            break;
        default:
            _setCurrentReceiver( newReceiver, 0, COMPONENT_RECEIVER_AUTO_N);
            break;
    }
    
    // display update part
    char *buff = _rpnf->getOutputBuffer();
    RPN_Stack *st = _rpnf->rpnStack;
    if( _nr->isActive())
        _lcd->updateCalcRegister( 0, _nr->toString());
    else
        _lcd->updateCalcRegister( 0, st->X->toString( buff));
    _lcd->updateCalcLabel( 0, st->X_Label);
    _lcd->updateCalcRegister( 1, st->Y->toString(buff));
    _lcd->updateCalcLabel( 1, st->Y_Label);
    _lcd->updateCalcRegister( 2, st->Z->toString(buff));
    _lcd->updateCalcLabel( 2, st->Z_Label);
    _lcd->updateCalcRegister( 3, st->T->toString(buff));
    _lcd->updateCalcLabel( 3, st->T_Label);
    return NO_CHANGE;
}
