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
// Pin assignment:
//
// 00 - LOLIN program inject - pushbutton to ground
// *01 - TX0
// *02 - SD chip select (1)
// *03 - RX0
// *04 - TFT RST
// *05 - VSPI CSO - TFT DC
//
// *06 - NA (Dev module not exposing)
// *07 - NA (Dev module not exposing)
// *08 - NA (Dev module not exposing)
// *09 - NA (Dev module not exposing)
// *10 - NA (Dev module not exposing)
// *11 - NA (Dev module not exposing)
//
// 12 - HSPI MISO LCD Data (R/W)
// 13 - HSPI MOSI LCD Reset (RESET)
// 14 - HSPI CLK LCD Clock (E)
// *15 - VSPI TFT Select (CS)
// 16 - Not used [RX2 (serial to Pro Micro 8) Note Pro Micro 14, 15, 16 are SPI/burn]
// 17 - Not used [TX2 (serial to Pro Micro 9)]
// *18 - VSPI CLK - TFT SCK
// *19 - VSPI MISO - TFT SDO/MISO and SD pin 3
//
// *20 - NA (Dev module not exposing)
//
// *21 - LCD LED PWM
// 22 - Not used
// *23 - VSPI MOSI - TFT SDI/MOSI and SD pin 2 (MOSI)
//
// *24 - NA (Dev module not exposing)
//
// *25 - KBD CLK
// *26 - KBD RST
// *27 - KBD SENSOR

// *28 - NA (Dev module not exposing)
// *29 - NA (Dev module not exposing)
// *30 - NA (Dev module not exposing)
// *31 - NA (Dev module not exposing)

// 32 - Not connected
// 33 - Not connected
// *34 - POWER Hold
// *35 - POWER sense (also Cx button)
//
////////////////////////////////////////////////////////

//#define __DEBUG

#define SERIAL_HARD_BAUD_RATE 115200
#include "./src/LCDManager.hpp"
#include "./src/KBDManager.hpp"

static LCDManager MyLCD;
static KBDManager MyKBD;

unsigned long targetTime = 0; // Used for testing draw times
static char buff[30];

void setup(void) {
  Serial.begin(SERIAL_HARD_BAUD_RATE);
  while(Serial.available()) Serial.read();
  Serial.println("MK-52 Resurrect!"); 
  long splashReady = MyLCD.init();
  MyKBD.init();
  MyLCD.waitForEndSplash( splashReady, true);
  //targetTime = millis();
  //CalculatorScreen( 3.12345678910E-012);
  //ReportTime( "Calculator", 500);
}

void loop(void) {  
  //targetTime = millis();
  //FontTest();
  //ReportTime( "Fill Screen", 10000);

  // targetTime = millis();
  // CalculatorScreen( 3.12345678910E-012);
  // ReportTime( "Calculator", 10000);

  // targetTime = millis();
  // CalculatorUpdateX( 3.12345678910E-012);
  // ReportTime( "100 updates of X", 10000);

  // targetTime = millis();
  // ProgramScreen("GOTO 12345678901234567890");
  // ReportTime( "Program", 20000);

  // targetTime = millis();
  // ProgramUpdate( "WHILE L0 LOOP");
  // ReportTime( "100 scrolls", 10000);

  // targetTime = millis();
  // DataScreen(12345678901e-123);
  // ReportTime( "Data", 10000);

  // targetTime = millis();
  // DataUpdate( 3.12345678910E-012);
  // ReportTime( "100 scrolls", 10000);

  if(Serial.available()){
    byte c = Serial.read();
    if( c == 'a')
    {
      MyKBD._pulseRST();
      CalculatorPrintX( (double)c);
      Serial.println("Reset");
      return;
    }
    if( c == 'b')
    {
      MyKBD._pulseCLK();
      CalculatorPrintX( (double)c);
      Serial.println("Pulse");
      return;
    }
    if( c == 'c')
    {
      MyKBD.LEDOn = !MyKBD.LEDOn;
      CalculatorPrintX( (double)c);
      Serial.println("LED flop");
      return;
    }
    if( c == 'd')
    {
      targetTime = millis();
      uint8_t b = MyKBD.scan();
      targetTime = millis() - targetTime;
      CalculatorPrintX( (double)b);
      Serial.print("Scan: ");
      Serial.print(b);
      Serial.print(" in ");
      Serial.print( targetTime);
      Serial.println( " ms");
      return;
    }
    return;
  }
  delay(30);

  // uint8_t b = MyKBD.scan();
  // if( !b){
  //   delay(30);
  //   return;
  // }
  // CalculatorUpdateX( (double)b);
}

void CalculatorScreen( double fakeData){
  MyLCD.dimScreen();
  snprintf(buff, 29, "%18.11E", fakeData);
  MyLCD.clearScreen( false);
  MyLCD.outputStatus( "C", "1234", "5678", "DEG", "   ");
  MyLCD.outputCalcRegister( 0, buff);
  MyLCD.outputCalcLabel( 0, "X: long, long, long label");
  MyLCD.outputCalcRegister( 1, buff);
  MyLCD.outputCalcLabel( 1, "Y: long, long, long label");
  MyLCD.outputCalcRegister( 2, buff);
  MyLCD.outputCalcLabel( 2, "Z: long, long, long label");
  MyLCD.outputCalcRegister( 3, buff);
  MyLCD.outputCalcLabel( 3, "T: long, long, long label");
  MyLCD.undimScreen();
}

void CalculatorUpdateX( double fakeData){
  for( int i=0; i<100; i++){
    snprintf(buff, 29, "%18.11E", fakeData);
    MyLCD.updateCalcRegister( 0, buff);
    fakeData *= 2.0;
  }
}

void CalculatorPrintX( double Data){
  snprintf(buff, 29, "%18.11E", Data);
  MyLCD.updateCalcRegister( 0, buff);
}

void ProgramScreen(char *fakeData){
  MyLCD.dimScreen();
  MyLCD.clearScreen( false);
  MyLCD.outputStatus( "P", "0000", "9999", "RAD", "NUM");
  for( int i=10; i>=0; i--){
    if(i<10)
      snprintf(buff, 30, "%04d  %s", i, fakeData);
    else
      snprintf(buff, 30, "%04d: %s", i, fakeData);
    MyLCD.outputTerminalLine( i, buff);
  }
  MyLCD.undimScreen();
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

void DataScreen( double fakeData){
  MyLCD.dimScreen();
  MyLCD.clearScreen( false);
  MyLCD.outputStatus( "D", "1234", "5678", "GRD", " F ");
  for( int i=10; i>=0; i--){
    if(i<10)
      snprintf(buff, 30, "%04d  %18.11E", i, fakeData);
    else
      snprintf(buff, 30, "%04d: %18.11E", i, fakeData);
    MyLCD.outputTerminalLine( i, buff);
  }
  MyLCD.undimScreen();
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

// void FontTest(){
//   for( int i=0; i<256; i++){
//     int x = (i%30)*11;
//     int y = (i/30)*20;
//     MyLCD.outputChar( x, y, (uint8_t)i);
//   }
// }

void ReportTime( char *name, int wait){
  long dt = millis() - targetTime;
  Serial.print( name);
  Serial.print( " = ");
  Serial.print( dt);
  Serial.println(" ms");
  delay(wait);
}
