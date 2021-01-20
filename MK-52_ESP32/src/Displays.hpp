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
        Receiver *current_Receiver = NULL;
        virtual unsigned long init( void *components[]);
        virtual void activate();
        virtual int tick();
        inline Receiver *getReceiver( int id){
            return (Receiver *)_components[id];};

      protected:
        void **_components;
        MK52_Hardware::LCD_Manager *_lcd;
        MK52_Hardware::KBD_Manager *_kbd;
        MK52_Interpreter::Program_Memory *_pmem;
        MK52_Interpreter::Extended_Memory *_emem;
        void _setCurrentReceiver( uint8_t id, uint8_t scancode=0, int8_t parent=-1);
    };

    class Display_AUTO: public Display{
      public:
        unsigned long init( void *components[]);
        void activate();
        int tick();
      protected:
        MK52_Interpreter::RPN_Stack *_stack;
        MK52_Interpreter::Receiver_Number *_nr;
    };

    class Display_PROG: public Display{
      public:
        unsigned long init( void *components[]);
        void activate();
        int tick();
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
        void activate();
        int tick();
      protected:
        char buff[30];
        double _fakeData = -1.23456789012e+123;
        MK52_Interpreter::Receiver_Number *_nr;
    };

    class Display_FILE: public Display{
      public:
        unsigned long init( void *components[]);
        void activate();
        int tick();
      protected:
        MK52_Hardware::SD_Manager *_sd;
    };
};

#endif // DISPLAYS_HPP
