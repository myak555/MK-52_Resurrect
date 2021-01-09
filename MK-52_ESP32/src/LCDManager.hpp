//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Pin assignment:
//
// 04 - TFT RST
// 05 - VSPI CSO - TFT DC
// 15 - VSPI TFT Select (CS)
// 18 - VSPI CLK - TFT SCK
// 19 - VSPI MISO - TFT SDO/MISO
// 21 - LCD LED PWM
// 23 - VSPI MOSI - TFT SDI/MOSI
// 23 - VSPI MOSI - TFT SDI/MOSI
// 34 - POWER HOLD

#ifndef LCDMANAGER_HPP
#define LCDMANAGER_HPP

#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

// Output ports are set within TFT-eSPI/User_Setup.h:
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_SCLK 18
//#define TFT_CS   15  // Chip select control pin
//#define TFT_DC    2  // Data Command control pin (changed  from 5)
//#define TFT_RST   4  // Reset pin (could connect to RST pin)
// The same files disables useless fonts 6, 7 and 8

// fade LED PIN (replace with LED_BUILTIN=2 constant for built-in LED)
// LCD PIN controls power for LCD
// use first channel of 16 channels (started from zero)
// use 13 bit precision for LEDC timer
// use 5000 Hz as a LEDC base frequency
#define SYSTEM_POWER_HOLD      33
#define LCD_LED_PIN            21
#define LCD_LEDC_CHANNEL_0     0
#define LCD_LEDC_TIMER_13_BIT  13
#define LCD_LEDC_MAX_DUTY      8191
#define LCD_LEDC_BASE_FREQ     5000

// must be less than IO_BUFFER_LENGTH (256)
#define SCR_MAX_UTF (SCR_COLS + SCR_COLS + 1)
#define SCR_BUFFER_SIZE 1024

// cursor blinker rate in ms
#define BLINKER_RATE 500

// show splashscreen in ms
#define SCR_SPLASH  5000

// Screen dimensions in symbols
// Columns 320 / 11 = 29
// Rows 240 / 20 = 12 (but the top one is taken by the status bar)
#define SCREEN_COLS 30 
#define SCREEN_ROWS 12 

class LCDManager{
  public:
    bool isLEDoff = false;
    bool cursorShown = true;
    byte ledBrightness = 200;
    uint16_t fgcolor = TFT_GREEN;
    uint16_t bgcolor = TFT_BLACK;

    unsigned long init();
    void waitForEndSplash( unsigned long start, bool cls = false);
    inline void dimScreen(){_dimLED( ledBrightness, 0, 5);};
    inline void undimScreen(){_dimLED( 0, ledBrightness, 5);};
    void clearScreen( bool dim=false);

    void outputStatus( char *pc, char *mc, char *dmode, char *fmode);
    void updateStatus( char *pc, char *mc, char *dmode, char *fmode);

    void outputCalcRegister( uint8_t row, char *text);
    void outputCalcRegister( uint8_t row, double value);
    void outputCalcRegister( uint8_t row, int64_t value);
    void updateCalcRegister( uint8_t row, char *text);
    void updateCalcRegister( uint8_t row, double value);
    void updateCalcRegister( uint8_t row, int64_t value);
    void outputCalcLabel( uint8_t row, char *text);
    void updateCalcLabel( uint8_t row, char *text);
    void outputTerminalLine( uint8_t row, char *text);
    void updateTerminalLine( uint8_t row, char *text);

    void outputDigitString( int16_t x, int16_t y, char *src, uint16_t fg=TFT_GREEN, uint16_t bg=TFT_BLACK);
    void outputDigit( int16_t x, int16_t y, char d, uint16_t fg=TFT_GREEN, uint16_t bg=TFT_BLACK);
    void outputCharString( int16_t x, int16_t y, char *src, uint16_t fg=TFT_GREEN, uint16_t bg=TFT_BLACK);
    void outputChar( int16_t x, int16_t y, uint8_t c, uint16_t fg=TFT_GREEN, uint16_t bg=TFT_BLACK);

    inline void shutdown(){ digitalWrite( SYSTEM_POWER_HOLD, LOW); };
  private:
    char _text[30]; // temporary output buffer
    char *_buffer = NULL;
    char *_lines[SCREEN_ROWS];
    int64_t *_ledPWM = NULL;
    void _dimLED( byte start_duty, byte stop_duty, byte step=30);
    void _ledcAnalogWrite(uint8_t channel, uint8_t value);
    void _redrawStatusPosition( char *message, uint8_t pos);
    void _redrawCalcLabel( uint8_t row, char *line, char* text);
    void _redrawCalcRegister( uint8_t row, char *line, char* text);
    void _redrawTerminalLine( uint8_t row, char *line, char* text);
    char *_composeDouble(char *text, double value); 
    char *_composeInt64(char *text, int64_t value);
};

#endif // LCDMANAGER_HPP
