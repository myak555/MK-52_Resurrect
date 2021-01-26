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

static MK52_Interpreter::RPN_Stack _m_RPN_Stack;
static MK52_Interpreter::Program_Memory _m_Program_Memory;
static MK52_Interpreter::Extended_Memory _m_Extended_Memory;
static MK52_Interpreter::Register_Memory _m_Register_Memory;
static MK52_Interpreter::RPN_Functions _m_RPN_Functions;

static MK52_Interpreter::Receiver_Number _m_Receiver_Number;
static MK52_Interpreter::Receiver_Text _m_Receiver_Text;
static MK52_Interpreter::Receiver_Address _m_Receiver_Address;
static MK52_Interpreter::Receiver_Register _m_Receiver_Register;

static MK52_Interpreter::Receiver_AUTO_N _m_Receiver_AUTO_N;
static MK52_Interpreter::Receiver_AUTO_F _m_Receiver_AUTO_F;
static MK52_Interpreter::Receiver_AUTO_K _m_Receiver_AUTO_K;
static MK52_Interpreter::Receiver_AUTO_A _m_Receiver_AUTO_A;
static MK52_Interpreter::Receiver_AUTO_R _m_Receiver_AUTO_R;

static MK52_Interpreter::Receiver_PROG_N _m_Receiver_PROG_N;
static MK52_Interpreter::Receiver_PROG_F _m_Receiver_PROG_F;

static MK52_Interpreter::Receiver_DATA_N _m_Receiver_DATA_N;
static MK52_Interpreter::Receiver_DATA_F _m_Receiver_DATA_F;
static MK52_Interpreter::Receiver_DATA_K _m_Receiver_DATA_K;
static MK52_Interpreter::Receiver_DATA_A _m_Receiver_DATA_A;

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

    // hardware components
    _components[ COMPONENT_LCD_MANAGER] = &_m_Hardware_LCD;
    _components[ COMPONENT_KBD_MANAGER] = &_m_Hardware_KBD;
    _components[ COMPONENT_SD_MANAGER] = &_m_Hardware_SD;

    // interpreter engine components
    _components[ COMPONENT_STACK] = &_m_RPN_Stack;
    _components[ COMPONENT_PROGRAM_MEMORY] = &_m_Program_Memory;
    _components[ COMPONENT_EXTENDED_MEMORY] = &_m_Extended_Memory;
    _components[ COMPONENT_REGISTER_MEMORY] = &_m_Register_Memory;
    _components[ COMPONENT_FUNCTIONS] = &_m_RPN_Functions;

    // UI data receivers
    _components[ COMPONENT_RECEIVER_NUMBER] = &_m_Receiver_Number;
    _components[ COMPONENT_RECEIVER_TEXT] = &_m_Receiver_Text;
    _components[ COMPONENT_RECEIVER_ADDRESS] = &_m_Receiver_Address;
    _components[ COMPONENT_RECEIVER_REGISTER] = &_m_Receiver_Register;
    
    _components[ COMPONENT_RECEIVER_AUTO_N] = &_m_Receiver_AUTO_N;
    _components[ COMPONENT_RECEIVER_AUTO_F] = &_m_Receiver_AUTO_F;
    _components[ COMPONENT_RECEIVER_AUTO_K] = &_m_Receiver_AUTO_K;
    _components[ COMPONENT_RECEIVER_AUTO_A] = &_m_Receiver_AUTO_A;
    _components[ COMPONENT_RECEIVER_AUTO_R] = &_m_Receiver_AUTO_R;

    _components[ COMPONENT_RECEIVER_PROG_N] = &_m_Receiver_PROG_N;
    _components[ COMPONENT_RECEIVER_PROG_F] = &_m_Receiver_PROG_F;

    _components[ COMPONENT_RECEIVER_DATA_N] = &_m_Receiver_DATA_N;
    _components[ COMPONENT_RECEIVER_DATA_F] = &_m_Receiver_DATA_F;
    _components[ COMPONENT_RECEIVER_DATA_K] = &_m_Receiver_DATA_K;
    _components[ COMPONENT_RECEIVER_DATA_A] = &_m_Receiver_DATA_A;

    // User interfaces
    _components[ COMPONENT_DISPLAY_AUTO] = &_m_Display_AUTO;
    _components[ COMPONENT_DISPLAY_PROG] = &_m_Display_PROG;
    _components[ COMPONENT_DISPLAY_DATA] = &_m_Display_DATA;
    _components[ COMPONENT_DISPLAY_FILE] = &_m_Display_FILE;

    _m_Program_Memory.init( _components);
    _m_Extended_Memory.init( _components);
    _m_Register_Memory.init( _components);
    _m_RPN_Stack.init( _components);
    _m_RPN_Functions.init( _components);

    _m_Receiver_Number.init( _components);
    _m_Receiver_Text.init( _components);
    _m_Receiver_Address.init( _components);
    _m_Receiver_Register.init( _components);

    _m_Receiver_AUTO_N.init( _components);
    _m_Receiver_AUTO_F.init( _components);
    _m_Receiver_AUTO_K.init( _components);
    _m_Receiver_AUTO_A.init( _components);
    _m_Receiver_AUTO_R.init( _components);
    
    _m_Receiver_PROG_N.init( _components);
    _m_Receiver_PROG_F.init( _components);

    _m_Receiver_DATA_N.init( _components);
    _m_Receiver_DATA_F.init( _components);
    _m_Receiver_DATA_K.init( _components);
    _m_Receiver_DATA_A.init( _components);

    _m_Display_AUTO.init( _components);
    _m_Display_PROG.init( _components);
    _m_Display_DATA.init( _components);
    _m_Display_FILE.init( _components);
 
    #ifdef __DEBUG
    Serial.println("Checks:");
    Serial.println( _m_RPN_Functions.progMem->getCounter());
    Serial.println( _m_RPN_Functions.extMem->getCounter());
    Serial.print( "[");
    Serial.print( _m_RPN_Functions.Stack->getDModeName());
    Serial.println( "]");
    Serial.print("SD card ");
    Serial.println( _m_Hardware_SD.SDMounted? "mounted": "not found");
    Serial.println("MK-52 Resurrect!");
    #endif

    // end splash and start serving keyboard
    _m_Hardware_LCD.waitForEndSplash( splashReady, false);
    #ifdef __DEBUG
    // testing all displays
    //setDisplay( COMPONENT_DISPLAY_AUTO);
    //delay(DEBUG_SHOW_DELAY);
    //setDisplay( COMPONENT_DISPLAY_FILE);
    //delay(DEBUG_SHOW_DELAY);
    //setDisplay( COMPONENT_DISPLAY_DATA);
    //delay(DEBUG_SHOW_DELAY);
    //setDisplay( COMPONENT_DISPLAY_PROG);
    //delay(DEBUG_SHOW_DELAY);
    #endif

    setDisplay( COMPONENT_DISPLAY_AUTO);
    return millis();
}

void MK52_Host::tick(){
    if( current_Display == NULL) return;
    int newDisplay = current_Display->tick();
    if( newDisplay == SHUTDOWN_REQUESTED) shutdown();
    setDisplay( newDisplay);
}

void MK52_Host::setDisplay(int id){
    if( id<0) return;
    current_Display = getDisplay( id);
    if( current_Display == NULL) return;
    current_Display->activate();
}

//
// For now, it is just a demo code for debugging (TODO)
//
void MK52_Host::shutdown(){
    bool t = !(getKBD()->LEDOn);
    getKBD()->LEDOn = t;
    digitalWrite( SYSTEM_POWER_HOLD, t);

    // after the power transistor is installed, this will not happen:
    setDisplay( COMPONENT_DISPLAY_AUTO);
}
