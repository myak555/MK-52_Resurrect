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

TFT_eSPI _MyTFT = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

static const uint16_t _statusLocations[] = { 77, 167, 231, 279};
static const uint8_t _statusLengths[] = { 4, 4, 3, 3};
static const uint8_t _statusOffsets[] = { 2, 7, 12, 16};
static const char _calcCharacters[] = "0123456789ABCDEFIfnor-+.:";
static const int16_t _calcRegisterLocations[] = {210,155,100,45};
static const int16_t _calcLabelLocations[] = {188,133,78,23};

using namespace MK52_Hardware;

//
// Inits LCD display
//
unsigned long LCD_Manager::init() {

    // Set timer and attach to the led
    pinMode( LCD_LED_PIN, OUTPUT);
    ledcSetup(LCD_LEDC_CHANNEL_0, LCD_LEDC_BASE_FREQ, LCD_LEDC_TIMER_13_BIT);
    ledcAttachPin(LCD_LED_PIN, LCD_LEDC_CHANNEL_0);
    _ledcAnalogWrite(LCD_LEDC_CHANNEL_0, 0); // Screen PWM off initially

    //perform init sequence and show splash
    _MyTFT.init();
    _MyTFT.setRotation(3);
    _MyTFT.fillScreen( bgcolor);
    _MyTFT.drawBitmap( 95, 85, Simple_Icon_128x60px, 128, 60, fgcolor, bgcolor);
    _dimLED( 0, ledBrightness, 60); // lit slowly

    long t = millis();

    // The first row is split:
    // 5 bytes each for pc and mc
    // 3 bytes each for dmode and fmode
    _buffer = (char *)malloc( SCREEN_BUFFER_SIZE);
    memset( _buffer, 0, SCREEN_BUFFER_SIZE);
    char *ptr = _buffer;
    for( uint8_t i=0; i<SCREEN_ROWS; i++){
        _lines[i] = ptr;
        ptr += SCREEN_COLS + 1;
    }
    return t; 
}

//
// Other inits are hidden behind the splash screen
//
void LCD_Manager::waitForEndSplash( unsigned long start, bool cls) {
    while( millis()-start < SCR_SPLASH) delay(50);
    if( !cls) return;
    clearScreen( true);
}

void LCD_Manager::outputStatus( uint32_t pc, uint32_t mc, char *dmode, char *fmode){
    _MyTFT.drawBitmap( 0, 0, StatusTemplate_320x20px, 320, 20, bgcolor, fgcolor);
    memset( _buffer, 0, SCREEN_COLS);
    outputCharString( 51, 0, "PC", bgcolor, fgcolor);
    _printCounter(pc);
    _redrawStatusPosition( _text, 0);
    outputCharString( 141, 0, "MC", bgcolor, fgcolor);
    _printCounter(mc);
    _redrawStatusPosition( _text, 1);
    _redrawStatusPosition( dmode, 2);
    _redrawStatusPosition( fmode, 3);
}

void LCD_Manager::updateStatus( uint32_t pc, uint32_t mc, char *dmode, char *fmode){
    _printCounter(pc);
    _redrawStatusPosition( _text, 0);
    _printCounter(mc);
    _redrawStatusPosition( _text, 1);
    _redrawStatusPosition( dmode, 2);
    _redrawStatusPosition( fmode, 3);
}

void LCD_Manager::updateStatusPC( uint32_t pc){
    _printCounter(pc);
    _redrawStatusPosition( _text, 0);
}

void LCD_Manager::updateStatusMC( uint32_t mc){
    _printCounter(mc);
    _redrawStatusPosition( _text, 1);
}

void LCD_Manager::_redrawStatusPosition( char *message, uint8_t pos){
    char *ptr = _buffer + _statusOffsets[pos];
    if( strcmp(message, ptr) == 0) return; // strings identical
    uint8_t ln = _statusLengths[pos];
    strncpy( ptr, message, ln);
    ptr[ln] = 0; // safety zero
    #ifdef __DEBUG
    Serial.println("redraw status");
    #endif
    outputCharString( _statusLocations[pos], 0, ptr, bgcolor, fgcolor);
}

void LCD_Manager::outputCalcRegister( uint8_t row, char *text){
    if( row > 3) return;
    char *line = _lines[ (row<<1) + 1];
    memset( line, 0, SCREEN_COLS);
    _redrawCalcRegister( row, line, text);
}

void LCD_Manager::updateCalcRegister( uint8_t row, char *text){
    if( row > 3) return;
    _redrawCalcRegister( row, _lines[ (row<<1) + 1], text);
}

void LCD_Manager::_redrawCalcRegister( uint8_t row, char *line, char* text){
    if( strcmp(line, text) == 0) return; // strings identical
    strncpy( line, text, CALC_COLS);
    line[CALC_COLS] = 0; // safety zero
    int16_t j = strlen(line);
    int16_t j2 = CALC_COLS-j;
    if( j2 < 0) j2 = 0;
    int16_t x = 0;
    int16_t y = _calcRegisterLocations[row];
    //_MyTFT.drawBitmap( 0, y, Seven_segment_16x27px, 8, 30, bgcolor, bgcolor);
    for( int16_t i=0; i<j2; i++, x+=16)
        _MyTFT.drawBitmap( x, y, Seven_segment_16x27px, 16, 30, bgcolor, bgcolor);
    for( int16_t i=0; i<j; i++, x+=16)
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
    int ln = strlen(line);
    int16_t x = 4;
    int16_t y = _calcLabelLocations[row];
    for( uint8_t i=0; i<SCREEN_COLS; i++, x+=11){
        if( i<ln) outputChar( x, y, line[i], fgcolor, bgcolor);
        else outputChar( x, y, ' ', bgcolor, bgcolor);
    }
}

void LCD_Manager::outputTerminalLine( uint8_t row, char *text){
    if( row > 10) return;
    char *line = _lines[ row+1];
    if( strlen(text)==0) eraseTerminalLine( row);
    else{
        line[0] = 0;    
        _redrawTerminalLine( row, line, text);
    }
}

void LCD_Manager::updateTerminalLine( uint8_t row, char *text){
    if( row > 10) return;
    _redrawTerminalLine( row, _lines[ row+1], text);
}

void LCD_Manager::eraseTerminalLine( uint8_t row){
    if( row > 10) return;
    char *line = _lines[row+1];
    if( line[0] == 0) return;
    #ifdef __DEBUG
    Serial.print("Erase row ");
    Serial.println( row);
    #endif
    int16_t y = (row+1) * 20;
    _MyTFT.drawBitmap( 0, y, Nixedsys_12x20, 320, 20, bgcolor, bgcolor);
    *line=0;    
}

void LCD_Manager::_redrawTerminalLine( uint8_t row, char *line, char* text){
    if( line[0] == 0 && text[0] ==0) return;
    if( strcmp(line, text) == 0) return; // strings identical
    #ifdef __DEBUG
    Serial.print("Update row ");
    Serial.println( row);
    #endif
    strncpy( line, text, SCREEN_COLS);
    line[SCREEN_COLS] = 0; // safety zero
    int ln = strlen(line);
    int16_t x = 1;
    int16_t y = (row+1) * 20;
    for( uint8_t i=0; i<SCREEN_COLS; i++, x+=11){
        if( i<ln) outputChar( x, y, line[i], fgcolor, bgcolor);
        else outputChar( x, y, ' ', bgcolor, bgcolor);
    }
}

void LCD_Manager::clearScreen( bool dim){
    if( dim) _dimLED( ledBrightness, 0, 5); // dim before cleaning
    _MyTFT.fillScreen( bgcolor);
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
        _MyTFT.drawBitmap( x, y, Seven_segment_16x27px, 16, 30, bg, bg);
        return;     
    }
    const uint8_t *bmp = Seven_segment_16x27px + 54 * (int16_t)( ptr-_calcCharacters);
    _MyTFT.drawBitmap( x, y, bmp, 16, 1, bg, bg);
    _MyTFT.drawBitmap( x, y+1, bmp, 16, 27, fg, bg);
    _MyTFT.drawBitmap( x, y+28, bmp, 16, 2, bg, bg);
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
    _MyTFT.drawBitmap( x, y, bmp, 11, 3, bg, bg);
    _MyTFT.drawBitmap( x, y+3, bmp, 11, 16, fg, bg);
    _MyTFT.drawBitmap( x, y+19, bmp, 11, 1, bg, bg);
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
