//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "KBD_Manager.hpp"

using namespace MK52_Hardware;

void KBD_Manager::init(){
    pinMode(KBD_RST, OUTPUT);
    pinMode(KBD_CLK, OUTPUT);
    pinMode(KBD_SENSE, INPUT);
    pinMode(KBD_Cx, INPUT);
    digitalWrite( KBD_CLK, LOW);
    _pulseRST();
}

uint8_t KBD_Manager::scan(){
    uint8_t ret = scanImmediate();
    if( ret == 0){
        if( LEDOn && lastPressedTime + KBD_SLEEP_DELAY < lastScanTime){
            LEDOn = false;
            // TODO - uncomment after receiver is ready
            // return 33; 
        }
        delay(KBD_IDLE_DELAY);
        return ret;
    }
    lastScan = ret;
    while( ret != 0){
        ret = scanImmediate();
        delay( KBD_JITTER_DELAY);
    }
    lastPressedTime = millis();
    return lastScan;
}

uint8_t KBD_Manager::scanImmediate(){
    _pulseRST();
    uint8_t ret=0;
    uint8_t end = LEDOn? 32: 31;
    for(uint8_t i=0; i<end; i++){
        if( !ret && digitalRead( KBD_SENSE) == HIGH){
            ret = i+1;
            if( !LEDOn) break;
        }
        _pulseCLK();
    }
    if( digitalRead( KBD_Cx) == HIGH) ret = 32; // read the Cx - power button, set apart
    lastScanTime = millis();
    return ret;
}

void KBD_Manager::_pulseRST(){
    digitalWrite( KBD_RST, HIGH);
    delayMicroseconds(KBD_PULSE);
    digitalWrite( KBD_RST, LOW);
    delayMicroseconds(KBD_PULSE);
}

void KBD_Manager::_pulseCLK(){
  digitalWrite( KBD_CLK, HIGH);
  delayMicroseconds(KBD_PULSE);
  digitalWrite( KBD_CLK, LOW);
  delayMicroseconds(KBD_PULSE);
}
