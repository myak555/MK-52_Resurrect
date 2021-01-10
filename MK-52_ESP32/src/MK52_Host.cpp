//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "MK52_Host.hpp"

#define __DEBUG

static MK52_Hardware::LCD_Manager MyLCD;
static MK52_Hardware::KBD_Manager MyKBD;
static MK52_Hardware::SD_Manager MySD;
static MK52_Interpreter::Number_Receiver MyNR;
static MK52_Interpreter::AUTO_Display MyAUTO;
static MK52_Interpreter::PROG_Display MyPROG;
static MK52_Interpreter::FILE_Display MyFILE;
static MK52_Interpreter::DATA_Display MyDATA;

using namespace MK52_Interpreter;

//
// Inits FILE display
//
unsigned long MK52_Host::init() {
}

// void FILE_Display::activate(){
//     #ifdef __DEBUG
//     long TargetTime = millis();
//     #endif
//     _lcd->dimScreen();
//     _lcd->clearScreen( false);

//     char *strs[10];
//     char *tmp = (char *)malloc( 300);
//     for( int i=0; i<10; i++, tmp+=30) strs[i] = tmp;
//     _sd->startFolderListing( strs, 10, 29);

//     _lcd->outputStatus( "0000", "9999", "RAD", "NUM");
//     for( int i=0; i<10; i++)
//         _lcd->outputTerminalLine( i, strs[i]);

//     _lcd->undimScreen();
//     free(strs[0]);

//     #ifdef __DEBUG
//     TargetTime = millis() - TargetTime;
//     Serial.print ("FILE display activated in ");
//     Serial.print ( TargetTime);
//     Serial.println (" ms");
//     delay( DEBUG_SHOW_DELAY);
//     #endif
// }

// void FILE_Display::tick(){
// }
