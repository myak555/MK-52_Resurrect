//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef DISPLAYS_HPP
#define DISPLAYS_HPP

#include "Common.h"
#include "LCD_Manager.hpp"
#include "SD_Manager.hpp"
#include "Program_Memory.hpp"
#include "Input_Receivers.hpp"

namespace MK52_Interpreter{

    class Display{
      public:
        virtual unsigned long init( void *components[]);
        virtual int activate();
        virtual void tick();
        inline bool isActive(){ return _mode != 0;};
      protected:
        uint8_t _mode = 0;
        MK52_Hardware::LCD_Manager *_lcd;
        MK52_Interpreter::Program_Memory *_pmem;
    };

    class Display_AUTO: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        MK52_Interpreter::Number_Receiver *_nr;
        double _fakeData = -1.23456789012e+123;
    };

    class Display_PROG: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        MK52_Interpreter::Number_Receiver *_nr;
    };

    class Display_DATA: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        char buff[30];
        double _fakeData = -1.23456789012e+123;
        MK52_Interpreter::Number_Receiver *_nr;
    };

    class Display_FILE: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        MK52_Hardware::SD_Manager *_sd;
    };
};

#endif // DISPLAYS_HPP
