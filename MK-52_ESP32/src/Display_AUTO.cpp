//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"

#define __DEBUG
using namespace MK52_Interpreter;

//
// Inits display for AUTO mode
//
unsigned long Display_AUTO::init( void *components[]) {
    _stack = (RPN_Stack *)components[COMPONENT_STACK];
    _nr = (Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    return Display::init( components);
}

void Display_AUTO::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _setCurrentReceiver( COMPONENT_RECEIVER_AUTO_N);
    char *buff = _lcd->getOutputBuffer(); 
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( _pmem->getCounter(), _emem->getCounter(), _stack->getDModeName(), current_Receiver->moniker());
    _lcd->outputCalcRegister( 0, _stack->X->toString( buff));
    _lcd->outputCalcLabel( 0, _stack->X_Label);
    _lcd->outputCalcRegister( 1, _stack->Y->toString(buff));
    _lcd->outputCalcLabel( 1, _stack->Y_Label);
    _lcd->outputCalcRegister( 2, _stack->Z->toString(buff));
    _lcd->outputCalcLabel( 2, _stack->Z_Label);
    _lcd->outputCalcRegister( 3, _stack->T->toString(buff));
    _lcd->outputCalcLabel( 3, _stack->T_Label);
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("AUTO display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
    return;
}

int Display_AUTO::tick(){
    // keyboard serve part
    uint8_t scancode = _kbd->scan();
    switch( scancode){
        case 0: // keyboard inactive
            delay(KBD_IDLE_DELAY);
            return NO_CHANGE;
        case 4:
            _stack->flipDMode();
            break;
        default:
            if( current_Receiver == NULL) return NO_CHANGE;
            int newReceiver = current_Receiver->tick( scancode);
            if( newReceiver < 0) return newReceiver; 
            _setCurrentReceiver( newReceiver, scancode, newReceiver);
            break;
    }
    
    // display update part
    char *buff = _lcd->getOutputBuffer(); 
    _lcd->updateStatus( _pmem->getCounter(), _emem->getCounter(), _stack->getDModeName(), current_Receiver->moniker());
    if( _nr->isActive())
        _lcd->updateCalcRegister( 0, _nr->toString());
    else
        _lcd->updateCalcRegister( 0, _stack->X->toString( buff));
    _lcd->updateCalcLabel( 0, _stack->X_Label);
    _lcd->updateCalcRegister( 1, _stack->Y->toString(buff));
    _lcd->updateCalcLabel( 1, _stack->Y_Label);
    _lcd->updateCalcRegister( 2, _stack->Z->toString(buff));
    _lcd->updateCalcLabel( 2, _stack->Z_Label);
    _lcd->updateCalcRegister( 3, _stack->T->toString(buff));
    _lcd->updateCalcLabel( 3, _stack->T_Label);
    return NO_CHANGE;
}
