//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef MK52_HOST_HPP
#define MK52_HOST_HPP

#include "Common.h"
#include "KBD_Manager.hpp"
#include "LCD_Manager.hpp"
#include "SD_Manager.hpp"
#include "Input_Receivers.hpp"
#include "Displays.hpp"

namespace MK52_Interpreter{
    class MK52_Host{
      public:
        unsigned long init();
    };
};

#endif // MK52_HOST_HPP
