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

void Receiver_AUTO_R::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init AUTO_R");
    #endif
    Receiver::init(components);
}

void Receiver_AUTO_R::activate( uint8_t scancode, int8_t parent){
    Receiver::activate( scancode, parent);
    _rpnf->_atStop = false;
    _lcd->updateStatusFMODE( "RUN");
    if( _rpnf->progMem->isAtStop())
        _rpnf->progMem->incrementCounter();
    _mode = 1;
}

int Receiver_AUTO_R::tick( uint8_t scancode){
    while( true){
        bool update_required = (millis() - _kbd->lastScanTime) > KBD_RUNNING_DELAY;
        _rpnf->executeRun();
        if( _rpnf->_atStop) break;
        if( update_required){
            if( _kbd->scanImmediate() == 8) break;
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            _lcd->updateCalcRegister( 0, _rpnf->rpnStack->X->toString( _rpnf->getOutputBuffer()));
        }
    }
    _lcd->outputStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(),
                        _rpnf->rpnStack->getDModeName(), "   ");
    while( _kbd->scanImmediate() != 0) delay( KBD_JITTER_DELAY);
    _mode = 0;
    return COMPONENT_DISPLAY_AUTO;
}
