//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include <cmath>
#include <math.h>

#include "LCD_Manager.hpp"

#include "../hardware/Splash_Screen.h"
#include "../hardware/Seven_Segment.h"
#include "../hardware/Nixedsys_1251.h"
#include "../hardware/Status_Template.h"

//#define __DEBUG

static TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
static const uint16_t _statusLocations[] = { 77, 167, 231, 279};
static const uint8_t _statusLengths[] = { 4, 4, 3, 3};
static const uint8_t _statusOffsets[] = { 2, 7, 12, 16};
static const char _calcCharacters[] = "0123456789ABCDEFIfnor-+.:";
static const int16_t _calcRegisterLocations[] = {210,155,100,45};
static const int16_t _calcLabelLocations[] = {188,133,78,23};

const char _standard_DoubleFormat[] PROGMEM = "%f";  
const char _standard_FullPrecision[] PROGMEM = "%13.11f";  
const char _standard_ExponentFormat[] PROGMEM = "%+04d";  
const char _standard_Error[] PROGMEM = "Error";  
const char _standard_MinusInfinity[] PROGMEM = "-Inf";  
const char _standard_PlusInfinity[] PROGMEM = "+Inf";  

using namespace MK52_Hardware;

//
// Inits LCD display
//
unsigned long LCD_Manager::init() {

    // Hold power
    pinMode( SYSTEM_POWER_HOLD, OUTPUT);
    digitalWrite( SYSTEM_POWER_HOLD, HIGH);

    // Set timer and attach to the led
    pinMode( LCD_LED_PIN, OUTPUT);
    ledcSetup(LCD_LEDC_CHANNEL_0, LCD_LEDC_BASE_FREQ, LCD_LEDC_TIMER_13_BIT);
    ledcAttachPin(LCD_LED_PIN, LCD_LEDC_CHANNEL_0);
    _ledcAnalogWrite(LCD_LEDC_CHANNEL_0, 0); // Screen PWM off initially

    //perform init sequence and show splash
    tft.init();
    tft.setRotation(3);
    tft.fillScreen( bgcolor);
    tft.drawBitmap( 95, 85, Simple_Icon_128x60px, 128, 60, fgcolor, bgcolor);
    _dimLED( 0, ledBrightness, 60); // lit slowly

    long t = millis();

    // The first row is split:
    // 5 bytes each for pc and mc
    // 3 bytes each for dmode and fmode
    _buffer = (char *)malloc( SCREEN_COLS *  SCREEN_ROWS);
    memset( _buffer, 0, SCREEN_COLS *  SCREEN_ROWS );
    char *ptr = _buffer;
    for( uint8_t i=0; i<SCREEN_ROWS; i++){
        _lines[i] = ptr;
        ptr += SCREEN_COLS;
    }
    return t; 
}

//
// Other inits are hidden behind the splash screen
//
void LCD_Manager::waitForEndSplash( unsigned long start, bool cls) {
    while( millis()-start < SCR_SPLASH) delay(50);
    //memset( _buffer, _SP_, SCR_SIZE);
    //memset( lineInversed, false, SCR_ROWS);
    //_ledPWM = (int64_t *)_vars->findDataPtr( _LCD_lcdPWM);
    //if( _ledPWM) ledBrightness = (byte)( *_ledPWM & 0xFF);
    if( cls) clearScreen(true);
    //keepAwake();
}

void LCD_Manager::outputStatus( char *pc, char *mc, char *dmode, char *fmode){
    tft.drawBitmap( 0, 0, StatusTemplate_320x20px, 320, 20, bgcolor, fgcolor);
    memset( _buffer, 0, SCREEN_COLS);
    outputCharString( 51, 0, "PC", bgcolor, fgcolor);
    _redrawStatusPosition( pc, 0);
    outputCharString( 141, 0, "MC", bgcolor, fgcolor);
    _redrawStatusPosition( mc, 1);
    _redrawStatusPosition( dmode, 2);
    _redrawStatusPosition( fmode, 3);
}

void LCD_Manager::updateStatus( char *pc, char *mc, char *dmode, char *fmode){
    _redrawStatusPosition( pc, 0);
    _redrawStatusPosition( mc, 1);
    _redrawStatusPosition( dmode, 2);
    _redrawStatusPosition( fmode, 3);
}

void LCD_Manager::_redrawStatusPosition( char *message, uint8_t pos){
    char *ptr = _buffer + _statusOffsets[pos];
    if( strcmp(message, ptr) == 0) return; // strings identical
    uint8_t l = _statusLengths[pos];
    strncpy( ptr, message, l);
    ptr[l] = 0; // safety zero
    outputCharString( _statusLocations[pos], 0, ptr, bgcolor, fgcolor);
}

void LCD_Manager::outputCalcRegister( uint8_t row, char *text){
    if( row > 3) return;
    char *line = _lines[ (row<<1) + 1];
    memset( line, 0, SCREEN_COLS);
    _redrawCalcRegister( row, line, text);
}

void LCD_Manager::outputCalcRegister( uint8_t row, double value){
    if( row > 3) return;
    outputCalcRegister( row, _composeDouble( _text, value));
}

void LCD_Manager::outputCalcRegister( uint8_t row, int64_t value){
    if( row > 3) return;
    outputCalcRegister( row, _composeInt64( _text, value));
}

void LCD_Manager::updateCalcRegister( uint8_t row, char *text){
    if( row > 3) return;
    _redrawCalcRegister( row, _lines[ (row<<1) + 1], text);
}

void LCD_Manager::updateCalcRegister( uint8_t row, double value){
    if( row > 3) return;
    updateCalcRegister( row, _composeDouble( _text, value));
}

void LCD_Manager::updateCalcRegister( uint8_t row, int64_t value){
    if( row > 3) return;
    updateCalcRegister( row, _composeInt64( _text, value));
}

void LCD_Manager::_redrawCalcRegister( uint8_t row, char *line, char* text){
    if( strcmp(line, text) == 0) return; // strings identical
    strncpy( line, text, 19);
    line[19] = 0; // safety zero
    uint8_t j = strlen(line);
    uint8_t j2 = 19-j;
    int16_t x = 12;
    int16_t y = _calcRegisterLocations[row];
    tft.drawBitmap( 0, y, Seven_segment_16x27px, 12, 30, bgcolor, bgcolor);
    for( uint8_t i=0; i<j2; i++, x+=16)
        tft.drawBitmap( x, y, Seven_segment_16x27px, 16, 30, bgcolor, bgcolor);
    for( uint8_t i=0; i<j; i++, x+=16)
        outputDigit( x, y, line[i], fgcolor, bgcolor);
}

void LCD_Manager::outputCalcLabel( uint8_t row, char *text){
    if( row > 3) return;
    char *line = _lines[ (row<<1) + 2];
    memset( line, 0, SCREEN_COLS);
    _redrawCalcLabel( row, line, text);
}

void LCD_Manager::updateCalcLabel( uint8_t row, char *text){
    if( row > 3) return;
    _redrawCalcLabel( row, _lines[ (row<<1) + 2], text);
}

void LCD_Manager::_redrawCalcLabel( uint8_t row, char *line, char* text){
    if( strcmp(line, text) == 0) return; // strings identical
    strncpy( line, text, SCREEN_COLS);
    line[SCREEN_COLS] = 0; // safety zero
    int l = strlen(line);
    int16_t x = 4;
    int16_t y = _calcLabelLocations[row];
    for( uint8_t i=0; i<SCREEN_COLS; i++, x+=11){
        if( i<l) outputChar( x, y, line[i], fgcolor, bgcolor);
        else outputChar( x, y, ' ', bgcolor, bgcolor);
    }
}

void LCD_Manager::outputTerminalLine( uint8_t row, char *text){
    if( row > 10) return;
    char *line = _lines[ row+1];
    memset( line, 0, SCREEN_COLS);
    _redrawTerminalLine( row, line, text);
}

void LCD_Manager::updateTerminalLine( uint8_t row, char *text){
    if( row > 10) return;
    _redrawTerminalLine( row, _lines[ row+1], text);
}

void LCD_Manager::_redrawTerminalLine( uint8_t row, char *line, char* text){
    if( strcmp(line, text) == 0) return; // strings identical
    strncpy( line, text, SCREEN_COLS);
    line[SCREEN_COLS] = 0; // safety zero
    int l = strlen(line);
    int16_t x = 1;
    int16_t y = (row+1) * 20;
    for( uint8_t i=0; i<SCREEN_COLS; i++, x+=11){
        if( i<l) outputChar( x, y, line[i], fgcolor, bgcolor);
        else outputChar( x, y, ' ', bgcolor, bgcolor);
    }
}

void LCD_Manager::clearScreen( bool dim){
    if( dim) _dimLED( ledBrightness, 0, 5); // dim before cleaning
    tft.fillScreen( bgcolor);
    if( dim) _dimLED( 0, ledBrightness, 5);
}

void LCD_Manager::outputDigitString( int16_t x, int16_t y, char *src, uint16_t fg, uint16_t bg){
    int8_t len = strlen( src);
    for( int i=0; i<len; i++){
        outputDigit( x, y, *src++, fg, bg);
        x+=16;
    }
}

void LCD_Manager::outputDigit( int16_t x, int16_t y, char d, uint16_t fg, uint16_t bg){
    char *ptr = strchr( _calcCharacters, d);
    if( ptr == NULL){
        tft.drawBitmap( x, y, Seven_segment_16x27px, 16, 30, bg, bg);
        return;     
    }
    const uint8_t *bmp = Seven_segment_16x27px + 54 * (int16_t)( ptr-_calcCharacters);
    tft.drawBitmap( x, y, bmp, 16, 1, bg, bg);
    tft.drawBitmap( x, y+1, bmp, 16, 27, fg, bg);
    tft.drawBitmap( x, y+28, bmp, 16, 2, bg, bg);
}

void LCD_Manager::outputCharString( int16_t x, int16_t y, char *src, uint16_t fg, uint16_t bg){
    int8_t len = strlen( src);
    for( int i=0; i<len; i++){
        uint16_t b = (uint16_t)(*src++);  
        outputChar( x, y, b, fg, bg);
        x+=11;
    }
}

void LCD_Manager::outputChar( int16_t x, int16_t y, uint8_t c, uint16_t fg, uint16_t bg){
    uint16_t shift = (uint16_t)c;
    const uint8_t *bmp = Nixedsys_12x20 + (shift<<5);
    tft.drawBitmap( x, y, bmp, 11, 3, bg, bg);
    tft.drawBitmap( x, y+3, bmp, 11, 16, fg, bg);
    tft.drawBitmap( x, y+19, bmp, 11, 1, bg, bg);
}

//
// Lights or dims LED slowly in steps of 16/256 to the preset level.
// The larger the step in ms, the slower the dim.
//
void LCD_Manager::_dimLED( byte start_duty, byte stop_duty, byte step){
    int16_t duty = start_duty;
    while( true){
        if( duty == stop_duty) return;
        if(duty < stop_duty){
            duty += 16;
            if( duty > stop_duty) duty = stop_duty; 
        }
        else{
            duty -= 16;
            if( duty < stop_duty) duty = stop_duty;       
        }
        _ledcAnalogWrite( LCD_LEDC_CHANNEL_0, (byte)duty);
        if( duty != stop_duty) delay(step);      
    }
}

//
// Normalizes LED PWM to 256 levels.
//
void LCD_Manager::_ledcAnalogWrite(uint8_t channel, uint8_t value) {
    uint32_t duty = (LCD_LEDC_MAX_DUTY * value) >> 8;
    ledcWrite(channel, duty);
}

//
// Converts double number
//
char *LCD_Manager::_composeDouble(char *text, double value){ 
    if( isnan(value)){
        sprintf_P(text, _standard_Error);
        return text;
    }
    if( value == -INFINITY){
        sprintf_P(text, _standard_MinusInfinity);
        return text;
    }
    if( value == INFINITY){
        sprintf_P(text, _standard_PlusInfinity);
        return text;
    }
    bool negative = false;
    if( value < 0.0){
        negative = true;
        value = -value;
    } 
    if( 0.1 <= value && value < 1.e12){
      snprintf_P(text, 29, _standard_DoubleFormat, negative? -value: value);
      text[29] = 0;
      return text;
    }
    int16_t exponent = 0;
    while(value<1.0){
      exponent--;
      value *= 10.0;
    }
    while(value>=10.0){
      exponent++;
      value *= 0.1;
    }
    snprintf_P(text, 24, _standard_FullPrecision, negative? -value: value);
    text[24] = 0;
    int16_t i = strlen(text);
    snprintf_P(text+i, 29-i, _standard_ExponentFormat, exponent);
    text[29] = 0; // safety zero
    return text;
}

//
// Converts int
//
char *LCD_Manager::_composeInt64(char *text, int64_t value){ 
  if( value > 9000000000000000000L){
    snprintf_P(text, 29, _standard_MinusInfinity);
    return text;
  }
  if( value < -9000000000000000000L){
    snprintf_P(text, 29, _standard_PlusInfinity);
    return text;
  }
  // my own version of lltoa
  // return lltoa( value, text, 10);
  char *ptr = text;
  if( value == 0L){
    *ptr++ = '0';
    *ptr = 0;
    return text;
  }
  if( value < 0){
    *ptr++ = '-';
    value = -value;
  }
  int64_t mult = 1000000000000000000L;
  while( mult && !(value / mult)) mult /= 10;
  while( mult){
    *ptr++ = '0' + (int8_t)(value / mult);
    value %= mult;
    mult /= 10;
  }
  *ptr = 0;
  return text;
}
