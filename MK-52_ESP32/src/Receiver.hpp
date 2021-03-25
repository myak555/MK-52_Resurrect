//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef INPUT_RECEIVER_HPP
#define INPUT_RECEIVER_HPP

#include "LCD_Manager.hpp"
#include "KBD_Manager.hpp"
#include "RPN_Functions.hpp"

namespace MK52_Interpreter{

    class Receiver{
      public:
        int8_t Moniker = NO_CHANGE;
        Receiver(void *components[]);
        virtual void activate( int8_t prevReceiver = NO_CHANGE);
        virtual uint8_t tick( uint8_t scancode = 0);
      protected:
        uint8_t _mode = 0;
        int8_t _return_to = -1;
        void **_components;
        char _funlabel[4];
        MK52_Hardware::KBD_Manager *_kbd;  //TODO: Required only in RUN to check keyboard
        MK52_Hardware::LCD_Manager *_lcd;
        RPN_Functions *_rpnf;
        char _convertButton(const char *list, uint8_t scancode);
    };
};

#endif // INPUT_RECEIVER_HPP
