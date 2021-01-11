//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef INPUT_RECEIVERS_HPP
#define INPUT_RECEIVERS_HPP

#include "Common.h"
#include "KBD_Manager.hpp"
#include "Program_Memory.hpp"

#define NO_PARENT_RETURN  -1

namespace MK52_Interpreter{

    class Input_Receiver{
      public:
        virtual unsigned long init( void *components[]);
        virtual void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        virtual int tick( uint8_t scancode = 0);
        inline bool isActive(){ return _mode != 0;};
        inline char *toString(){ return _text;};
        inline char *toTrimmedString(){ return (*_text == ' ')? _text+1: _text;};
      protected:
        uint8_t _mode = 0;
        int _parentReturn;
        char _text[SCREEN_COLS]; // temporary input buffer
        MK52_Hardware::KBD_Manager *_kbd;
    };

    class Number_Receiver: public Input_Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        char _convertButton(uint8_t scancode);
        int _appendChar( char c);
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };

    class AUTO_N_Receiver: public Input_Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        Number_Receiver *_nr;
        int _appendButton(uint8_t scancode);
    };

    class PROG_N_Receiver: public Input_Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        Number_Receiver *_nr;
        Program_Memory *_pmem;
        int _appendButton(uint8_t scancode);
    };
};

#endif // INPUT_RECEIVERS_HPP
