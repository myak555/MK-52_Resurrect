//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Entering primary register in PROG mode (text added to the current program line)
//

Receiver_Register::Receiver_Register(void *components[]) : Receiver::Receiver(components){
    Moniker = _RECEIVER_REGISTER;
    strcpy_P( _funlabel, PSTR("MEM"));
}

void Receiver_Register::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating REGISTER: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    if( _RECEIVER_PROG_N <= prevReceiver && prevReceiver <=_RECEIVER_PROG_A)
        _lcd->updateTerminalLine(10, _rpnf->progMem->getCurrentLine());
    _lcd->updateStatusFMODE( _funlabel);
    memset(_text, 0, 3);
}

uint8_t Receiver_Register::tick( uint8_t scancode){
    char c = _convertButton(_RR_ButtonConversion, scancode);
    switch (c){
        case 0:
            return 0;
        case 'f': // entry completed, action needed
            _rpnf->requestNextReceiver(_return_to);
            return scancode;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
            _text[0] = 'L';
            _text[1] = c - 'a' + '0';
            break;
        default:
            _text[0] = c;
            break;
    }
    completeEntry( toString());
    return _rpnf->requestNextReceiver(_return_to);
}

void Receiver_Register::completeEntry( char *value){
    if (value[0] == 0){
        _rpnf->progMem->replaceLine_P(PSTR(""));
        return;
    }
    Program_Memory *pm = _rpnf->progMem;
    _rpnf->setOutputBuffer(pm->getCurrentLine());
    _rpnf->appendOutputBuffer(value);
    pm->replaceLine(_rpnf->getOutputBuffer());
    pm->incrementCounter();
}

//
// Register to X in AUTO mode
//

Receiver_Register_MX::Receiver_Register_MX(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_MX;
}

void Receiver_Register_MX::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_AUTO_N);
}

void Receiver_Register_MX::completeEntry( char *value){
    if( value[0] == 0) return;
    _rpnf->regMem->MtoX( value);
}

//
// X to Register in AUTO mode
//

Receiver_Register_XM::Receiver_Register_XM(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_XM;
}

void Receiver_Register_XM::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_AUTO_N);
}

void Receiver_Register_XM::completeEntry( char *value){
    if( value[0] == 0) return;
    _rpnf->regMem->XtoM( value);
}

//
// K Register to X in AUTO mode
//

Receiver_Register_KMX::Receiver_Register_KMX(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_KMX;
}

void Receiver_Register_KMX::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_AUTO_N);
}

void Receiver_Register_KMX::completeEntry( char *value){
    if( value[0] == 0) return;
    _rpnf->regMem->K_MtoX( value);
}

//
// K X to Register in AUTO mode
//

Receiver_Register_KXM::Receiver_Register_KXM(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_KXM;
}

void Receiver_Register_KXM::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_AUTO_N);
}

void Receiver_Register_KXM::completeEntry( char *value){
    if( value[0] == 0) return;
    _rpnf->regMem->K_XtoM( value);
}

//
// Extended to Register in DATA mode
//

Receiver_Register_EM::Receiver_Register_EM(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_EM;
}

void Receiver_Register_EM::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_DATA_N);
}

void Receiver_Register_EM::completeEntry( char *value){
    if( value[0] == 0) return;
    _rpnf->execute( FUNC_MEXTOR, value);
}

//
// Register to Extended in DATA mode
//

Receiver_Register_ME::Receiver_Register_ME(void *components[]) : Receiver_Register::Receiver_Register(components){
    Moniker = _RECEIVER_REGISTER_ME;
}

void Receiver_Register_ME::activate( int8_t prevReceiver){
    Receiver_Register::activate( _RECEIVER_DATA_N);
}

void Receiver_Register_ME::completeEntry( char *value){
    if( value[0] == 0) return; 
    _rpnf->execute( FUNC_RTOMEX, value);
}
