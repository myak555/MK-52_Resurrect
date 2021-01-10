////////////////////////////////////////////////////////

/* MK52 RESURRECT - "Электроника МК-52" with retrofitted ESP32 processor
  Copyright (c) 2020 Mike Yakimov.  All rights reserved.

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Inspired by work of: 
    Gordon Brandly (Tiny Basic for 68000)
    Mike Field (Arduino Basic)
    Scott Lawrence (TinyBasic Plus)
    Brian O'Dell (INPUT)
    David A. Mellis (SD card utils)
    Oli Kraus (LCD library)
    Andrey Skvortsov (Terminal-BASIC and Arduino SRAM)
    Pavel Travnik (Retro Calculator with ESP32)
    David Boucher (Tiny Keyboard)
    User "Dita Schop" (Arduino RPN calc)
*/

////////////////////////////////////////////////////////
//
// This implementation is for ESP32 Dev Module version 1
//
// Pin assignment (LOLIN 32):
//
// 00 - Available
// *01 - TX0
// *02 - TFT DC
// *03 - RX0
// *04 - TFT RST
// *05 - SD chip select (CS)
//
// *06 - NA (Dev module not exposing)
// *07 - NA (Dev module not exposing)
// *08 - NA (Dev module not exposing)
// *09 - NA (Dev module not exposing)
// *10 - NA (Dev module not exposing)
// *11 - NA (Dev module not exposing)
//
// 12 - Available (HSPI MISO)
// 13 - Available (HSPI MOSI)
// 14 - Available (HSPI CLK)
// *15 - VSPI TFT Select (CS)
// 16 - Reserved [RX2 (serial to Pro Micro 8) Note Pro Micro 14, 15, 16 are SPI/burn]
// 17 - Reserved [TX2 (serial to Pro Micro 9)]
// *18 - VSPI CLK - TFT SCK and SD SCK
// *19 - VSPI MISO - TFT SDO/MISO and SD MISO
//
// *20 - NA (Dev module not exposing)
//
// *21 - TFT LED PWM
// 22 - Available
// *23 - VSPI MOSI - TFT SDI/MOSI and SD MOSI
//
// *24 - NA (Dev module not exposing)
// *25 - KBD CLK
// *26 - KBD RST
// *27 - KBD SENSOR
//
// 28 - NA (Dev module not exposing)
// 29 - NA (Dev module not exposing)
// 30 - NA (Dev module not exposing)
// 31 - NA (Dev module not exposing)
//
// 32 - Available
// *33 - POWER Hold
// 34 - Available (input-only)
// *35 - POWER sense (also Cx button)
//
////////////////////////////////////////////////////////

//#define __DEBUG

#define SERIAL_HARD_BAUD_RATE 115200

//#include <math.h>

#include "./src/MK52_Host.hpp"
//#include "./src/SD_Manager.hpp"
//#include "./src/Input_Receivers.hpp"
//#include "./src/Displays.hpp"

static MK52_Hardware::LCD_Manager MyLCD;
static MK52_Hardware::KBD_Manager MyKBD;
static MK52_Hardware::SD_Manager MySD;
static MK52_Interpreter::Number_Receiver MyNR;
static MK52_Interpreter::AUTO_Display MyAUTO;
static MK52_Interpreter::PROG_Display MyPROG;
static MK52_Interpreter::FILE_Display MyFILE;
static MK52_Interpreter::DATA_Display MyDATA;

static void *MyComponents[N_COMPONENTS];

static char buff[30];

void setup(void) {
    Serial.begin(SERIAL_HARD_BAUD_RATE);
    while(Serial.available()) Serial.read();
    Serial.println("MK-52 Resurrect!"); 
    long splashReady = MyLCD.init();
    MyKBD.init();
    MySD.init();
    MyComponents[ COMPONENT_LCD_MANAGER] = &MyLCD;
    MyComponents[ COMPONENT_KBD_MANAGER] = &MyKBD;
    MyComponents[ COMPONENT_SD_MANAGER] = &MySD;
    MyComponents[ COMPONENT_NUMBER_RECEIVER] = &MyNR;
    MyNR.init( MyComponents);
    MyAUTO.init( MyComponents);
    MyPROG.init( MyComponents);
    MyDATA.init( MyComponents);
    MyFILE.init( MyComponents);

    Serial.print("SD card ");
    if( MySD.SDMounted) Serial.println("mounted");
    else Serial.println("not found");
    MyLCD.waitForEndSplash( splashReady, true);
    
    FontTest();
    MyPROG.activate();
    MyFILE.activate();
    MyDATA.activate();
    MyAUTO.activate();
}

void loop(void) {
    if( MyNR.isActive()){
        MyNR.tick();
        MyAUTO.tick();
        delay(KBD_IDLE_DELAY);
        return;
    }

    uint8_t b = MyKBD.scan();
    if( b){
        Serial.print("Activating on key: ");
        Serial.println( b);
        MyNR.activate( b);    
        if( b == 32) MyLCD.shutdown();
        delay(KBD_IDLE_DELAY);
        return;
    }

    if(Serial.available()){
      b = Serial.read();
      if( b == 'e')
      {
        MyKBD.LEDOn = !MyKBD.LEDOn;
        Serial.println("LED flop");
        return;
      }
      if( b == 's')
      {
        Serial.println("Shutdown!");
        delay( 500);
        MyLCD.shutdown();
        return;
      }
      return;
    }
    delay(KBD_IDLE_DELAY);
}

void ProgramUpdate(char *fakeData){
    for( int j=1; j<=100; j++){
      for( int i=10; i>=0; i--){
        if(i<10)
          snprintf(buff, 30, "%04d  %s", i+j, fakeData);
        else
          snprintf(buff, 30, "%04d: %s", i, fakeData);
        MyLCD.outputTerminalLine( i, buff);
      }
    }
}

void DataUpdate( double fakeData){
    for( int j=1; j<=100; j++){
      for( int i=10; i>=0; i--){
        if(i<10)
          snprintf(buff, 30, "%04d  %18.11E", i, fakeData);
        else
          snprintf(buff, 30, "%04d: %18.11E", i, fakeData);
        MyLCD.outputTerminalLine( i, buff);
      }
    }
}

void FontTest(){
    for( int i=0; i<256; i++){
      int x = (i%30)*11;
      int y = (i/30)*20;
      MyLCD.outputChar( x, y, (uint8_t)i);
    }
    delay( DEBUG_SHOW_DELAY);
}
