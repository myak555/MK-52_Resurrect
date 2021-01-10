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

#ifndef KBD_MANAGER_HPP
#define KBD_MANAGER_HPP

#include "Common.h"

#define KBD_CLK                25
#define KBD_RST                26
#define KBD_SENSE              27
#define KBD_Cx                 35
#define KBD_PULSE              1

namespace MK52_Hardware{
    class KBD_Manager{
      public:
        uint8_t lastScan = 0;
        bool LEDOn = true;

        void init();
        uint8_t scan();
      private:
        void _pulseRST();
        void _pulseCLK();
    };
}

#endif // KBD_MANAGER_HPP
