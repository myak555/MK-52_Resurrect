//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "MK52_Host.hpp"

#define __DEBUG

static MK52_Hardware::LCD_Manager _m_Hardware_LCD;
static MK52_Hardware::KBD_Manager _m_Hardware_KBD;
static MK52_Hardware::SD_Manager _m_Hardware_SD;
static MK52_Interpreter::Number_Receiver _m_Receiver_Number;
static MK52_Interpreter::AUTO_Display _m_Display_AUTO;
static MK52_Interpreter::PROG_Display _m_Display_PROG;
static MK52_Interpreter::FILE_Display _m_Display_FILE;
static MK52_Interpreter::DATA_Display _m_Display_DATA;

using namespace MK52_Interpreter;

//
// Inits all components in order
//
unsigned long MK52_Host::init() {

    // Hold power
    pinMode( SYSTEM_POWER_HOLD, OUTPUT);
    digitalWrite( SYSTEM_POWER_HOLD, HIGH);

    #ifdef __DEBUG
    Serial.begin(SERIAL_HARD_BAUD_RATE);
    while(Serial.available()) Serial.read();
    #endif

    //
    // init hardware first
    //
    long splashReady = _m_Hardware_LCD.init();
    _m_Hardware_KBD.init();
    _m_Hardware_SD.init();

    // set components and init the rest
    _components[ COMPONENT_LCD_MANAGER] = &_m_Hardware_LCD;
    _components[ COMPONENT_KBD_MANAGER] = &_m_Hardware_KBD;
    _components[ COMPONENT_SD_MANAGER] = &_m_Hardware_SD;
    _components[ COMPONENT_NUMBER_RECEIVER] = &_m_Receiver_Number;
    _components[ COMPONENT_AUTO_DISPLAY] = &_m_Display_AUTO;
    _components[ COMPONENT_PROG_DISPLAY] = &_m_Display_PROG;
    _components[ COMPONENT_DATA_DISPLAY] = &_m_Display_FILE;
    _components[ COMPONENT_FILE_DISPLAY] = &_m_Display_DATA;
    _m_Receiver_Number.init( _components);
    _m_Display_AUTO.init( _components);
    _m_Display_PROG.init( _components);
    _m_Display_DATA.init( _components);
    _m_Display_FILE.init( _components);

    #ifdef __DEBUG
    Serial.println("MK-52 Resurrect!");
    Serial.print("SD card ");
    if( _m_Hardware_SD.SDMounted) Serial.println("mounted");
    else Serial.println("not found");
    #endif
    _m_Hardware_LCD.waitForEndSplash( splashReady, true);
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
