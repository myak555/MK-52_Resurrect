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

static MK52_Interpreter::Program_Memory _m_Program_Memory;

static MK52_Interpreter::Receiver_Number _m_Receiver_Number;
static MK52_Interpreter::Receiver_Address _m_Receiver_Address;
static MK52_Interpreter::Receiver_Register _m_Receiver_Register;
static MK52_Interpreter::Receiver_PROG_N _m_Receiver_PROG_N;
static MK52_Interpreter::Receiver_PROG_F _m_Receiver_PROG_F;

static MK52_Interpreter::Display_AUTO _m_Display_AUTO;
static MK52_Interpreter::Display_PROG _m_Display_PROG;
static MK52_Interpreter::Display_FILE _m_Display_FILE;
static MK52_Interpreter::Display_DATA _m_Display_DATA;

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
    _components[ COMPONENT_PROGRAM_MEMORY] = &_m_Program_Memory;
    _components[ COMPONENT_RECEIVER_NUMBER] = &_m_Receiver_Number;
    _components[ COMPONENT_RECEIVER_ADDRESS] = &_m_Receiver_Address;
    _components[ COMPONENT_RECEIVER_REGISTER] = &_m_Receiver_Register;
    _components[ COMPONENT_RECEIVER_PROG_N] = &_m_Receiver_PROG_N;
    _components[ COMPONENT_RECEIVER_PROG_F] = &_m_Receiver_PROG_F;
    _components[ COMPONENT_DISPLAY_AUTO] = &_m_Display_AUTO;
    _components[ COMPONENT_DISPLAY_PROG] = &_m_Display_PROG;
    _components[ COMPONENT_DISPLAY_DATA] = &_m_Display_FILE;
    _components[ COMPONENT_DISPLAY_FILE] = &_m_Display_DATA;

    _m_Program_Memory.init( _components);
    _m_Receiver_Number.init( _components);
    _m_Receiver_Address.init( _components);
    _m_Receiver_Register.init( _components);
    _m_Receiver_PROG_N.init( _components);
    _m_Receiver_PROG_F.init( _components);
    _m_Display_AUTO.init( _components);
    _m_Display_PROG.init( _components);
    _m_Display_DATA.init( _components);
    _m_Display_FILE.init( _components);
 
    #ifdef __DEBUG
    Serial.print("SD card ");
    if( _m_Hardware_SD.SDMounted) Serial.println("mounted");
    else Serial.println("not found");
    Serial.println("MK-52 Resurrect!");
    #endif

    // end splash and start serving keyboard
    _m_Hardware_LCD.waitForEndSplash( splashReady, false);
    setDisplay( COMPONENT_DISPLAY_PROG);
    return millis();
}

void MK52_Host::tick(){
    if( current_Receiver == NULL) return;
    int newReceiver = current_Receiver->tick();
    setReceiver( newReceiver);
    if( current_Display == NULL) return;
    current_Display->tick();
}

void MK52_Host::setDisplay(int id){
    if( id<0) return;
    current_Display = getDisplay( id);
    if( current_Display == NULL) return;
    int receiver = current_Display->activate();
    setReceiver(receiver);
}

void MK52_Host::setReceiver(int id){
    if( id<0) return;
    current_Receiver = getReceiver( id);
    if( current_Receiver == NULL) return;
    current_Receiver->activate();
}
