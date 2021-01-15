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

#include "./src/MK52_Host.hpp"

static MK52_Interpreter::MK52_Host MyHost;
static char buff[30];

void setup(void) {
    MyHost.init();
    //FontTest();
    //MyHost.getDisplay( COMPONENT_Display_FILE)->activate();
    //MyHost.getDisplay( COMPONENT_Display_DATA)->activate();
    //MyHost.getDisplay( COMPONENT_Display_AUTO)->activate();
    //MyHost.getDisplay( COMPONENT_Display_PROG)->activate();
    //MyHost.setDisplay( COMPONENT_Display_PROG);
    //MyHost.setReceiver( COMPONENT_PROG_N_RECEIVER);
}

void loop(void) {
    MyHost.tick();

    if(Serial.available()){
        byte b = Serial.read();
        if( b == 'e')
        {
            MyHost.getKBD()->LEDOn = !MyHost.getKBD()->LEDOn;
            Serial.println("LED flop");
            return;
        }
        if( b == 's')
        {
            Serial.println("Shutdown!");
            delay( 500);
            MyHost.shutdown();
            return;
        }
        return;
    }
    delay(KBD_IDLE_DELAY);
}

void FontTest(){
    MK52_Hardware::LCD_Manager *myLCD = MyHost.getLCD();
    for( int i=0; i<256; i++){
      int x = (i%30)*11;
      int y = (i/30)*20;
      myLCD->outputChar( x, y, (uint8_t)i);
    }
    delay( DEBUG_SHOW_DELAY);
}
