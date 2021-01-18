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
#include "LCD_Manager.hpp"
#include "KBD_Manager.hpp"
#include "SD_Manager.hpp"
#include "Program_Memory.hpp"

namespace MK52_Interpreter{

    class Receiver{
      public:
        virtual unsigned long init( void *components[]);
        virtual void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        virtual int tick( uint8_t scancode = 0);
        inline bool isActive(){ return _mode != 0;};
      protected:
        uint8_t _mode = 0;
        int _parentReturn;
        char _convertButton(const char *list, uint8_t scancode);
        MK52_Hardware::KBD_Manager *_kbd;
    };

    class Receiver_Number: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        inline char *toTrimmedString(){ return (*_text == ' ')? _text+1: _text;};
      protected:
        int _appendChar( char c);
        char _text[SCREEN_COLS]; // temporary input buffer
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };

    class Receiver_Address: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
      protected:
        int _appendChar( char c);
        char _text[SCREEN_COLS]; // temporary input buffer
    };

    class Receiver_Register: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
      protected:
        int _appendChar( char c);
        char _text[3]; // temporary input buffer
    };

    class Receiver_AUTO_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        Receiver_Number *_nr;
        int _appendButton(uint8_t scancode);
    };

    class Receiver_PROG_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        Receiver_Number *_nr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        Program_Memory *_pmem;
        int _appendButton(uint8_t scancode);
    };

    class Receiver_PROG_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( int parentReturn=NO_PARENT_RETURN, uint8_t scancode = 0);
        int tick( uint8_t scancode = 0);
      protected:
        Receiver_Address *_ar;
        Program_Memory *_pmem;
        int _appendButton(uint8_t scancode);
    };
};

#endif // INPUT_RECEIVERS_HPP
