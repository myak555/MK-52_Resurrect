//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Displays.hpp"

#define __DEBUG

const char _emptyLineFormat[] PROGMEM = "%04d";
const char _emptyLineEditFormat[] PROGMEM = "%04d> ";
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
    _tr = (MK52_Interpreter::Receiver_Text *)components[COMPONENT_RECEIVER_TEXT];
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
    _lcd->outputStatus( _pmem->getCounter(), _emem->getCounter(), _pmem->getEModeName(), "   ");
    int32_t display_PC = (int32_t)_pmem->getCounter();
    _pmem->getPreviousLines(_displayLines, SCREEN_ROWS-1);
    for( int i=10, j=0; i>=0; i--, j++){
        _lcd->outputTerminalLine( i, _getTerminalLine( buff, display_PC--, _displayLines[j]));
    }
    _setCurrentReceiver( COMPONENT_RECEIVER_PROG_N);
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
    // keyboard serve part
    uint8_t scancode = _kbd->scan();
    if( current_Receiver == NULL) return NO_CHANGE;
    int newReceiver = current_Receiver->tick( scancode);
    if( newReceiver < -1) return newReceiver;
    switch( newReceiver){
        case COMPONENT_DISPLAY_AUTO:
        case COMPONENT_DISPLAY_DATA:
        case COMPONENT_DISPLAY_FILE:
            return newReceiver;
        case 0:
        case -1:
            break;
        default:
            _setCurrentReceiver( newReceiver, 0, COMPONENT_RECEIVER_PROG_N);
            break;
    }

    unsigned long start = millis();
    char *buff = _lcd->getOutputBuffer();
    int32_t display_PC = (int32_t)_pmem->getCounter();
    _pmem->getPreviousLines(_displayLines, SCREEN_ROWS-1);
    for( int i=10, j=0; i>=0; i--, j++){
        _lcd->updateTerminalLine( i, _getTerminalLine( buff, display_PC--, _displayLines[j]));
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return NO_CHANGE;

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

// void Display_PROG::_printNumber(){
//     if( !_nr->isActive()) return;
//     _printStatus();
//     uint32_t pc = _pmem->getCounter();
//     snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _nr->toString());
// }

// void Display_PROG::_printOperatorWithAddress(){
//     if( !_ar->isActive()) return;
//     _printStatus();
//     uint32_t pc = _pmem->getCounter();
//     snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEdit2Format, pc % 10000, _pmem->toString(), _ar->toString());
// }

// void Display_PROG::_printOperatorWithRegister(){
//     if( !_rr->isActive()) return;
//     _printStatus();
//     uint32_t pc = _pmem->getCounter();
//     snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _pmem->toString());
// }

// void Display_PROG::_printOperator(){
//     if( _nr->isActive()) return;
//     if( _ar->isActive()) return;
//     if( _rr->isActive()) return;
//     _printStatus();
//     uint32_t pc = _pmem->getCounter();
//     snprintf_P(_lcd->getOutputBuffer(), SCREEN_COLS-1, _programLineEditFormat, pc % 10000, _pmem->getCurrentLine());
// }

char *Display_PROG::_getTerminalLine( char *buff, int32_t lineNumber, char *text){
    memset( buff, 0, SCREEN_COLS+1);
    if( lineNumber < 0) return buff;
    uint32_t lNum = (uint32_t)lineNumber;
    snprintf_P( buff, 5, PSTR("%04u"), lNum);
    buff[4] = (lNum == _pmem->getCounter())? '>': ' ';
    buff[5] = ' ';
    buff[6] = 0;
    int limit = SCREEN_COLS-6;
    // int ln = 0;
    // if( _tr->isActive()){
    //     text = _tr->toString();
    //     ln = strlen( text);
    //     if( ln > limit) text += ln-limit;
    //     snprintf_P( buff+6, limit, PSTR("%s"), text);
    //     return buff;
    // } 
    if( text == NULL) return buff;
    snprintf_P( buff+6, limit, PSTR("%s"), text);
    return buff;
}
