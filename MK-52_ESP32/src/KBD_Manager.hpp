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
// 25 - KBD CLK
// 26 - KBD RST
// 27 - KBD_SENSOR
// 35 - Cx button and power ON/OFF
//

#ifndef KBD_MANAGER_HPP
#define KBD_MANAGER_HPP

#include "Common.h"

#define KBD_CLK                25
#define KBD_RST                26
#define KBD_SENSE              27
#define KBD_Cx                 35

// Half-pulse in microseconds (the keybord operates at 0.5 MHz clock, the full scan of 32 buttons is about 100 us)
#define KBD_PULSE              1

namespace MK52_Hardware{
    class KBD_Manager{
      public:
        uint8_t lastScan = 0;
        unsigned long lastScanTime = 0L;
        unsigned long lastPressedTime = 0L;
        bool LEDOn = false;

        void init();
        uint8_t scan();
        uint8_t scanImmediate();
        inline void resetLastPressed(){
          lastScanTime = millis();
          lastPressedTime = lastScanTime;}
        inline void reset(){
          _pulseRST();};
      private:
        void _pulseRST();
        void _pulseCLK();
    };
}

#endif // KBD_MANAGER_HPP
