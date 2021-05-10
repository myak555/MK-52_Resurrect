//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include <WiFi.h>
#include "MK52_Host.hpp"

//#define __DEBUG

static MK52_Hardware::LCD_Manager _m_Hardware_LCD;
static MK52_Hardware::KBD_Manager _m_Hardware_KBD;
static MK52_Hardware::SD_Manager _m_Hardware_SD;

static MK52_Interpreter::RPN_Stack _m_RPN_Stack;
static MK52_Interpreter::Program_Memory _m_Program_Memory;
static MK52_Interpreter::Extended_Memory _m_Extended_Memory;
static MK52_Interpreter::Register_Memory _m_Register_Memory;
static MK52_Interpreter::RPN_Functions _m_RPN_Functions;

using namespace MK52_Interpreter;

//
// Inits all components in order
//
void MK52_Host::init() {

    // Hold power
    pinMode( SYSTEM_POWER_HOLD, OUTPUT);
    digitalWrite( SYSTEM_POWER_HOLD, HIGH);

    // make sure WiFi does not take power on startup
    WiFi.disconnect(true); delay(100);
    WiFi.mode(WIFI_OFF); delay(100);

    #ifdef __DEBUG
    Serial.begin(SERIAL_HARD_BAUD_RATE);
    while(Serial.available()) Serial.read();
    Serial.println();
    Serial.println("#");
    Serial.println("# Launch sequence start...");
    Serial.println("#");
    Serial.println();
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

    _m_Program_Memory.init( _components);
    _m_Extended_Memory.init( _components);
    _m_Register_Memory.init( _components);
    _m_RPN_Stack.init( _components);
    _m_RPN_Functions.init( _components);

    _addReceivers();
    // in case SD is not in, AUTO_N is launched
    _m_RPN_Functions.requestNextReceiver( _RECEIVER_AUTO_N);
    _m_RPN_Functions.loadState();
 
    #ifdef __DEBUG
    Serial.println();
    Serial.println("#");
    Serial.println("# MK-52 Resurrect!");
    Serial.println("#");
    Serial.println();
    #endif

    // end splash and start serving keyboard
    _m_Hardware_LCD.waitForEndSplash( splashReady, false);
    return;
}

void MK52_Host::tick(){
    uint8_t b = _m_Hardware_KBD.scan();
    do{
        b = current_Receiver->tick( b);
        if( setRequestedReceiver()) break;
    } while( b);
}

bool MK52_Host::setReceiver(int id){
    if( id<0) return true;
    Receiver *ri = getReceiver( id);
    if( !ri) return true;
    ri->activate( current_Receiver->Moniker);
    current_Receiver = ri;
    return false;
}

bool MK52_Host::setRequestedReceiver(){
    Receiver *ri = getReceiver(_m_RPN_Functions.getRequestedReceiver());
    if (!ri) return true;
    int8_t return_to = _m_RPN_Functions.getRequestedReturnReceiver();
    if (return_to < 0) return_to = current_Receiver->Moniker;
    ri->activate(return_to);
    current_Receiver = ri;
    return false;
}

Receiver *MK52_Host::_addReceiver( Receiver *rc){
    #ifdef __DEBUG
    if( rc->Moniker < 0 || rc->Moniker >= N_RECEIVERS){
        Serial.print("Incorrect moniker: ");
        Serial.println( rc->Moniker);
        return rc;
    }
    #endif
    _receivers[rc->Moniker] = rc;
    return rc;
}

void MK52_Host::_addReceivers(){
    for( int8_t i=0; i<N_RECEIVERS; i++){
        _receivers[i] = NULL;
    }
    current_Receiver = _addReceiver( new Receiver_OFF( _components));
    _addReceiver( new Receiver_AUTO_N( _components));
    _addReceiver( new Receiver_AUTO_F( _components));
    _addReceiver( new Receiver_AUTO_K( _components));
    _addReceiver( new Receiver_AUTO_FK( _components));
    _addReceiver( new Receiver_AUTO_A( _components));
    _addReceiver( new Receiver_AUTO_FA( _components));
    _addReceiver( new Receiver_AUTO_R( _components));

    _addReceiver( new Receiver_DATA_N( _components));
    _addReceiver( new Receiver_DATA_F( _components));
    _addReceiver( new Receiver_DATA_K( _components));
    _addReceiver( new Receiver_DATA_A( _components));
    _addReceiver( new Receiver_DATA_Erase( _components));

    _addReceiver( new Receiver_PROG_N( _components));
    _addReceiver( new Receiver_PROG_F( _components));
    _addReceiver( new Receiver_PROG_K( _components));
    _addReceiver( new Receiver_PROG_FK( _components));
    _addReceiver( new Receiver_PROG_A( _components));
    _addReceiver( new Receiver_PROG_FA( _components));
    _addReceiver( new Receiver_PROG_Erase( _components));

    _addReceiver( new Receiver_FILE_N( _components));
    _addReceiver( new Receiver_FILE_F( _components));
    _addReceiver( new Receiver_FILE_K( _components));
    _addReceiver( new Receiver_FILE_A( _components));
    _addReceiver( new Receiver_FILE_Name( _components));
    _addReceiver( new Receiver_FILE_Overwrite( _components));
    _addReceiver( new Receiver_FILE_Overwrite_All( _components));
    _addReceiver( new Receiver_FILE_Overwrite_Data( _components));
    _addReceiver( new Receiver_FILE_All( _components));
    _addReceiver( new Receiver_FILE_Data( _components));
    _addReceiver( new Receiver_FILE_Delete( _components));
    _addReceiver( new Receiver_FILE_MkDir( _components));

    _addReceiver( new Receiver_Number( _components));
    _addReceiver( new Receiver_Number_DATA( _components));
    _addReceiver( new Receiver_Number_PROG( _components));

    _addReceiver( new Receiver_Text( _components));
    _addReceiver( new Receiver_Text_FN( _components));

    _addReceiver( new Receiver_Address( _components));
    _addReceiver( new Receiver_Address_AMX( _components));
    _addReceiver( new Receiver_Address_AXM( _components));
    _addReceiver( new Receiver_Address_MC( _components));
    _addReceiver( new Receiver_Address_PC( _components));

    _addReceiver( new Receiver_Register( _components));
    _addReceiver( new Receiver_Register_MX( _components));
    _addReceiver( new Receiver_Register_XM( _components));
    _addReceiver( new Receiver_Register_KMX( _components));
    _addReceiver( new Receiver_Register_KXM( _components));
    _addReceiver( new Receiver_Register_ME( _components));
    _addReceiver( new Receiver_Register_EM( _components));
}
