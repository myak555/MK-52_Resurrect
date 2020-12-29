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
//

#ifndef KBDMANAGER_HPP
#define KBDMANAGER_HPP

#include <Arduino.h>

#define KBD_CLK                25
#define KBD_RST                26
#define KBD_SENSE              27
#define KBD_PULSE              10

class KBDManager{
  public:
    uint8_t lastScan = 0;
    bool LEDOn = true;

    void init();
    uint8_t scan();
  //private:
    void _pulseRST();
    void _pulseCLK();
};

#endif // KBDMANAGER_HPP
