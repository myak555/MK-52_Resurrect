//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef NUMBERRECEIVER_HPP
#define NUMBERRECEIVER_HPP

#include "Common.h"
#include "KBDManager.hpp"
#include "LCDManager.hpp"

class NumberReceiver{
  public:
    unsigned long init( void *components[]);
    void activate( uint8_t scancode = 0);
    void tick();
    inline bool isActive(){ return _mode != 0;};
    inline char *toString(){ return _text;};

  private:
    uint8_t _mode = 0;
    char _text[SCREEN_COLS]; // temporary input buffer
    KBDManager *_kbd;
    char _convertButton(uint8_t scancode);
    void _appendChar( char c);
    inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
};

#endif // NUMBERRECEIVER
