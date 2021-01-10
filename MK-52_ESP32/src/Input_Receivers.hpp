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

namespace MK52_Interpreter{

    class Input_Receiver{
      public:
        virtual unsigned long init( void *components[]);
        virtual void activate( uint8_t scancode = 0);
        virtual void tick();
        inline bool isActive(){ return _mode != 0;};
        inline char *toString(){ return _text;};
      protected:
        uint8_t _mode = 0;
        char _text[SCREEN_COLS]; // temporary input buffer
    };

    class Number_Receiver: public Input_Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0);
        void tick();
      protected:
        MK52_Hardware::KBD_Manager *_kbd;
        char _convertButton(uint8_t scancode);
        void _appendChar( char c);
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };
};

#endif // INPUT_RECEIVERS_HPP
