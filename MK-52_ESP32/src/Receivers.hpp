//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef INPUT_RECEIVERS_HPP
#define INPUT_RECEIVERS_HPP

#include "LCD_Manager.hpp"
#include "KBD_Manager.hpp"
#include "RPN_Functions.hpp"

namespace MK52_Interpreter{

    class Receiver{
      public:
        virtual unsigned long init( void *components[]);
        virtual void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        virtual int tick( uint8_t scancode = 0);
        inline bool isActive(){ return _mode != 0;};
      protected:
        uint8_t _mode = 0;
        int8_t _parentReceiver = -1;
        MK52_Hardware::KBD_Manager *_kbd;
        MK52_Hardware::LCD_Manager *_lcd;
        RPN_Functions *_rpnf;
        char _convertButton(const char *list, uint8_t scancode);
    };

    class Receiver_Number: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        inline char *toTrimmedString(){ return (*_text == ' ')? _text+1: _text;};
      private:
        char _text[SCREEN_COLS]; // temporary input buffer
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };

    class Receiver_Address: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
      private:
        char _text[5]; // temporary input buffer
        int _completeEntry();
    };

    class Receiver_Register: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
      private:
        char _text[3]; // temporary input buffer
    };

    class Receiver_AUTO_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Number *_nr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        int _appendButton(uint8_t scancode);
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_AUTO_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        int _appendButton(uint8_t scancode);
    };

    class Receiver_AUTO_K: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Register *_rr;
        int _appendButton(uint8_t scancode);
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_AUTO_A: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Address *_ar;
        int _appendButton(uint8_t scancode);
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_AUTO_R: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
    };

    class Receiver_PROG_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Number *_nr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        Program_Memory *_pmem;
        int _appendButton(uint8_t scancode);
    };

    class Receiver_PROG_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Address *_ar;
        Program_Memory *_pmem;
        int _appendButton(uint8_t scancode);
    };
};

#endif // INPUT_RECEIVERS_HPP
