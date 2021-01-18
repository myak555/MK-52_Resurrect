//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef DISPLAYS_HPP
#define DISPLAYS_HPP

#include "Receivers.hpp"

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
        MK52_Interpreter::Receiver_Number *_nr;
        double _fakeData = -1.23456789012e+123;
    };

    class Display_PROG: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        MK52_Interpreter::Receiver_Number *_nr;
        MK52_Interpreter::Receiver_Address *_ar;
        MK52_Interpreter::Receiver_Register *_rr;
        void _printNumber();
        void _printOperatorWithAddress();
        void _printOperatorWithRegister();
        void _printOperator();
        void _printStatus( bool output=false);
    };

    class Display_DATA: public Display{
      public:
        unsigned long init( void *components[]);
        int activate();
        void tick();
      protected:
        char buff[30];
        double _fakeData = -1.23456789012e+123;
        MK52_Interpreter::Receiver_Number *_nr;
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
