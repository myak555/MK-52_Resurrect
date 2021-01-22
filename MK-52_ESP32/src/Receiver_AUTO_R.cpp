//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Receivers.hpp"
#include "../functions/functions.h"

#define __DEBUG

using namespace MK52_Interpreter;

unsigned long Receiver_AUTO_R::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_R");
    #endif
    return Receiver::init(components);
}

void Receiver_AUTO_R::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _lcd->updateStatusFMODE( "RUN");
    _mode = 1;
}

int Receiver_AUTO_R::tick( uint8_t scancode){
    uint32_t newAddress = _rpnf->progMem->getCounter() + 99; // fake program "running"
    while( _rpnf->progMem->getCounter() < newAddress){
        if( _kbd->scan() == 8) break;
        _rpnf->execute( FUNC_INCREMENT_PC);
        _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    }
    _mode = 0;
    return COMPONENT_RECEIVER_AUTO_N;
}
