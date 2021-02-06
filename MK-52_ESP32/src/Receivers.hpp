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
        bool _getConfirmation( uint8_t confirmationButton);
    };

    class Receiver_Number: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        inline char *toTrimmedString(){ return (*_text == ' ')? _text+1: _text;};
      private:
        char *_text = NULL;
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };

    class Receiver_Text: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        char *toTrimmedString();
        char *toScreenString();
        void _setInputMode( uint8_t m, char *parentMode=NULL);
        char *appendText( char *text);
        char *appendText_P( const char *text);
      private:
        char *_text = NULL;
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
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_AUTO_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_K: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Register *_rr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_AUTO_A: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Address *_ar;
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
        Receiver_Text *_tr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        Program_Memory *_pmem;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_PROG_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Address *_ar;
        Receiver_Text *_tr;
        Program_Memory *_pmem;
    };

    class Receiver_PROG_K: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Register *_rr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_PROG_A: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Address *_ar;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_DATA_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Number *_nr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_DATA_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_K: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_A: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
    };

    class Receiver_FILE_N: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Text *_tr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_FILE_F: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Text *_tr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_FILE_K: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Text *_tr;
        int _completeSubentry( uint8_t scancode);
    };

    class Receiver_FILE_A: public Receiver{
      public:
        unsigned long init( void *components[]);
        void activate( uint8_t scancode = 0, int8_t parent = NO_CHANGE);
        int tick( uint8_t scancode = 0);
      private:
        Receiver_Text *_tr;
        int _completeSubentry( uint8_t scancode);
    };
};

#endif // INPUT_RECEIVERS_HPP
