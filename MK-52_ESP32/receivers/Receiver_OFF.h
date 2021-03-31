//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Parent receiver for AUTO mode
//

Receiver_OFF::Receiver_OFF(void *components[]) : Receiver::Receiver(components){
    Moniker = _RECEIVER_OFF;
}

void Receiver_OFF::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating OFF: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print(prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate(prevReceiver);
    _rpnf->saveState();
    digitalWrite( SYSTEM_POWER_HOLD, LOW);

    // after the power transistor is installed, this will not happen:
    _lcd->dimScreen();
    _lcd->clearScreen(false);
    _kbd->LEDOn = false;
}

uint8_t Receiver_OFF::tick( uint8_t scancode){
    // TODO: this is a fake wake-up from off
    if( scancode != 32) return 0;
    _kbd->LEDOn = true;
    return _rpnf->requestNextReceiver(_return_to);
}
