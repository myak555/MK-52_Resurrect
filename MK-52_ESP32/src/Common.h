//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include <Arduino.h>

// Screen dimensions in symbols
// Columns 320 / 11 = 29
// Rows 240 / 20 = 12 (but the top one is taken by the status bar)
#define SCREEN_COLS                 30 
#define SCREEN_ROWS                 12

// How long the system waits between the keyboard scans
#define KBD_IDLE_DELAY              30
#define DEBUG_SHOW_DELAY            10000

#define COMPONENT_LCD_MANAGER       0
#define COMPONENT_KBD_MANAGER       1
#define COMPONENT_SD_MANAGER        2
#define COMPONENT_NUMBER_RECEIVER   3

#define N_COMPONENTS                4
