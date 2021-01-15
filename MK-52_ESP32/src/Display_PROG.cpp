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

using namespace MK52_Interpreter;

//
// Inits display for PROG mode
//
unsigned long Display_PROG::init( void *components[]) {
    _nr = (MK52_Interpreter::Number_Receiver *)components[COMPONENT_NUMBER_RECEIVER];
    return Display::init( components);
}

int Display_PROG::activate(){
    #ifdef __DEBUG
    long TargetTime = millis();
    #endif
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    char *buff = _lcd->getOutputBuffer();
    uint32_t prev_PC = _pmem->getCounter();
    _lcd->outputStatus( prev_PC, 9999, "RAD", "   ");
    snprintf_P(buff, SCREEN_COLS-1, _programLineEditFormat, prev_PC % 10000, _pmem->getCurrentLine());
    buff[ SCREEN_COLS-1] = 0;
    _lcd->outputTerminalLine( 10, buff);
    for( int i=9; i>=0; i--){
        if( _pmem->decrementCounter()) break;
        snprintf_P(buff, SCREEN_COLS-1, _programLineFormat, _pmem->getCounter() % 10000, _pmem->getCurrentLine());
        buff[ SCREEN_COLS-1] = 0;
        _lcd->outputTerminalLine( i, buff);
    }
    _pmem->setCounter( prev_PC);
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print ("PROG display activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    delay( DEBUG_SHOW_DELAY);
    #endif
    return COMPONENT_PROG_N_RECEIVER;
}

void Display_PROG::tick(){
    unsigned long start = millis();
    char *buff = _lcd->getOutputBuffer();
    uint32_t prev_PC = _pmem->getCounter();
    if( _nr->isActive()){
        _lcd->updateStatus( prev_PC, 9999, "RAD", "NUM");
        snprintf_P(buff, SCREEN_COLS-1, _programLineEditFormat, prev_PC % 10000, _nr->toString());
    }
    else{
        _lcd->updateStatus( prev_PC, 9999, "RAD", "   ");
        snprintf_P(buff, SCREEN_COLS-1, _programLineEditFormat, prev_PC % 10000, _pmem->getCurrentLine());
    }
    buff[ SCREEN_COLS-1] = 0;
    _lcd->updateTerminalLine( 10, buff);
    for( int i=9; i>=0; i--){
        if( !_pmem->decrementCounter()){
            snprintf_P(buff, SCREEN_COLS-1, _programLineFormat, _pmem->getCounter() % 10000, _pmem->getCurrentLine());
            buff[ SCREEN_COLS-1] = 0;
            _lcd->updateTerminalLine( i, buff);
        }
        else
            _lcd->eraseTerminalLine( i);
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    if( millis()-start < KBD_IDLE_DELAY) delay(KBD_IDLE_DELAY);
    _pmem->setCounter( prev_PC);
}
