//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include <Arduino.h>

//
// Serial port for debugging
// 
#define SERIAL_HARD_BAUD_RATE 115200

// Screen dimensions in symbols
// Columns 320 / 11 = 29
// Rows 240 / 20 = 12 (but the top one is taken by the status bar)
#define SCREEN_COLS                 30 
#define CALC_COLS                   20 
#define SCREEN_ROWS                 12

// How long the system waits between the keyboard scans
#define KBD_IDLE_DELAY              30
#define DEBUG_SHOW_DELAY            10000

#define PROGRAM_MEMORY_SIZE         64000
#define EXTENDED_MEMORY_SIZE        36000

#define COMPONENT_LCD_MANAGER       0
#define COMPONENT_KBD_MANAGER       1
#define COMPONENT_SD_MANAGER        2
#define COMPONENT_PROGRAM_MEMORY    3
#define COMPONENT_REGISTER_MEMORY   4
#define COMPONENT_EXTENDED_MEMORY   5
#define COMPONENT_STACK             6
#define COMPONENT_NUMBER_RECEIVER   7
#define COMPONENT_PROG_N_RECEIVER   8
#define COMPONENT_Display_AUTO      9
#define COMPONENT_Display_PROG      10
#define COMPONENT_Display_DATA      11
#define COMPONENT_Display_FILE      12

#define N_COMPONENTS                13
