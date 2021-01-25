//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"

#define __DEBUG

const char _programLineFormat[] PROGMEM = "%04d  %s";
const char _programLineEditFormat[] PROGMEM = "%04d> %s";
const char _programLineEdit2Format[] PROGMEM = "%04d> %s%s";

using namespace MK52_Interpreter;

//
// Inits display for PROG mode
//
unsigned long Display_PROG::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init Display PROG");
    #endif
    _nr = (MK52_Interpreter::Receiver_Number *)components[COMPONENT_RECEIVER_NUMBER];
    _ar = (MK52_Interpreter::Receiver_Address *)components[COMPONENT_RECEIVER_ADDRESS];
    _rr = (MK52_Interpreter::Receiver_Register *)components[COMPONENT_RECEIVER_REGISTER];
    return Display::init( components);
}

void Display_PROG::activate(){
    #ifdef __DEBUG
    Serial.println("Activating PROG Display...");
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    char *buff = _lcd->getOutputBuffer();
    uint32_t prev_PC = _pmem->getCounter();
    _printStatus(true);
    snprintf_P(buff, SCREEN_COLS, _programLineEditFormat, prev_PC % 10000, _pmem->getCurrentLine());
    buff[ SCREEN_COLS] = 0;
    _lcd->outputTerminalLine( 10, buff);
    for( int i=9; i>=0; i--){
        if( _pmem->decrementCounter()) break;
        snprintf_P(buff, SCREEN_COLS, _programLineFormat, _pmem->getCounter() % 10000, _pmem->getCurrentLine());
        buff[ SCREEN_COLS] = 0;
        _lcd->outputTerminalLine( i, buff);
    }
    _pmem->setCounter( prev_PC);
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("PROG display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
    return;
}

int Display_PROG::tick(){
    delay( 10000);
    return COMPONENT_DISPLAY_AUTO;

    // unsigned long start = millis();
    // char *buff = _lcd->getOutputBuffer();
    // uint32_t prev_PC = _pmem->getCounter();
    // _printNumber();
    // _printOperatorWithAddress();
    // _printOperatorWithRegister();
    // _printOperator();
    // buff[ SCREEN_COLS-1] = 0;
    // _lcd->updateTerminalLine( 10, buff);
    // for( int i=9; i>=0; i--){
    //     if( !_pmem->decrementCounter()){
    //         snprintf_P(buff, SCREEN_COLS-1, _programLineFormat, _pmem->getCounter() % 10000, _pmem->getCurrentLine());
    //         buff[ SCREEN_COLS-1] = 0;
    //         _lcd->updateTerminalLine( i, buff);
    //     }
    //     else
    //         _lcd->eraseTerminalLine( i);
    //     //if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    // }
    // if( millis()-start < KBD_IDLE_DELAY) delay(KBD_IDLE_DELAY);
    // _pmem->setCounter( prev_PC);
    // return -1;
}

void Display_PROG::_printNumber(){
    if( !_nr->isActive()) return;
    _printStatus();
    uint32_t pc = _pmem->getCounter();
    snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _nr->toString());
}

void Display_PROG::_printOperatorWithAddress(){
    if( !_ar->isActive()) return;
    _printStatus();
    uint32_t pc = _pmem->getCounter();
    snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEdit2Format, pc % 10000, _pmem->toString(), _ar->toString());
}

void Display_PROG::_printOperatorWithRegister(){
    if( !_rr->isActive()) return;
    _printStatus();
    uint32_t pc = _pmem->getCounter();
    snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _pmem->toString());
}

void Display_PROG::_printOperator(){
    if( _nr->isActive()) return;
    if( _ar->isActive()) return;
    if( _rr->isActive()) return;
    _printStatus();
    uint32_t pc = _pmem->getCounter();
    snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _pmem->getCurrentLine());
}

void Display_PROG::_printStatus( bool output){
    uint32_t pc = _pmem->getCounter();
    uint32_t mc = _emem->getCounter();
    char *iMod = _pmem->getInputMode();
    char *eMod = _pmem->getEditMode();
    if( output) _lcd->outputStatus( pc, mc, eMod, iMod); 
    else _lcd->updateStatus( pc, mc, eMod, iMod); 
}
