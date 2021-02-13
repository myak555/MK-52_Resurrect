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
        virtual void init( void *components[]);
        virtual void activate();
        virtual int tick();
        inline Receiver *getReceiver( int id){
            return (Receiver *)_components[id];};

      protected:
        void **_components;
        MK52_Hardware::LCD_Manager *_lcd;
        MK52_Hardware::KBD_Manager *_kbd;
        RPN_Functions *_rpnf;
        void _setCurrentReceiver( uint8_t id, uint8_t scancode=0, int8_t parent=-1);
    };

    class Display_AUTO: public Display{
      public:
        void init( void *components[]);
        void activate();
        int tick();
      private:
        Receiver_Number *_nr;
    };

    class Display_PROG: public Display{
      public:
        void init( void *components[]);
        void activate();
        int tick();
      private:
        Receiver_Number *_nr;
        Receiver_Text *_tr;
        Receiver_Address *_ar;
        Receiver_Register *_rr;
        char *_displayLines[SCREEN_ROWS-1];
        void _printNumber();
        void _printOperatorWithAddress();
        void _printOperatorWithRegister();
        void _printOperator();
        char *_getTerminalLine( char *buff, int32_t lineNumber, char *text);
    };

    class Display_DATA: public Display{
      public:
        void init( void *components[]);
        void activate();
        int tick();
      private:
        Receiver_Number *_nr;
    };

    class Display_FILE: public Display{
      public:
        void init( void *components[]);
        void activate();
        int tick();
      private:
        MK52_Hardware::SD_Manager *_sd;
        Receiver_Text *_tr;
    };
};

#endif // DISPLAYS_HPP
