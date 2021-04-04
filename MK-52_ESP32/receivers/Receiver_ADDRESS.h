//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Entering address in PROG mode (text added to the current program line)
//

Receiver_Address::Receiver_Address(void *components[]) : Receiver::Receiver(components){
    Moniker = _RECEIVER_ADDRESS;
    strcpy_P( _funlabel, PSTR("ADR"));
}

void Receiver_Address::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating ADDRESS: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    _lcd->updateStatusFMODE( _funlabel);
    strcpy_P( _text, PSTR("    "));
}

uint8_t Receiver_Address::tick( uint8_t scancode){
    char c = _convertButton(_AR_ButtonConversion, scancode);
    switch (c){
        case 'e': // entry completed
        case 'f': // entry completed, action needed
            completeEntry( toTrimmedString());
            _rpnf->requestNextReceiver(_return_to);
            return (c == 'e') ? 0 : scancode;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            _text[0] = _text[1]; 
            _text[1] = _text[2]; 
            _text[2] = _text[3]; 
            _text[3] = c; 
            if( _text[0] == ' ') break;
            completeEntry(toTrimmedString());
            return _rpnf->requestNextReceiver(_return_to);
        case 'c': // erase
            _text[3] = _text[2]; 
            _text[2] = _text[1]; 
            _text[1] = _text[0]; 
            _text[0] = ' '; 
            if (_text[3] != ' ') break;
            completeEntry(toTrimmedString());
            return _rpnf->requestNextReceiver(_return_to);
        default:
            break;
    }
    updateDisplay(toString());
    return 0;
}

char *Receiver_Address::toTrimmedString(){
    char *ptr = _text;
    while( *ptr==' ') ptr++;
    return ptr;
}

void Receiver_Address::completeEntry( char *value){
    Program_Memory *pm = _rpnf->progMem;
    if (value[0] == 0){
        pm->deleteLine();
        return;
    }
    for( int8_t i=0; i<3; i++){
        if( _text[i] == ' ') _text[i] = '0';
    }
    _rpnf->setOutputBuffer(pm->getCurrentLine());
    _rpnf->appendOutputBuffer(_text);
    pm->replaceLine(_rpnf->getOutputBuffer());
    pm->incrementCounter();
}

void Receiver_Address::updateDisplay( char *value){
    Program_Memory *pm = _rpnf->progMem;
    char *buff = _rpnf->getOutputBuffer();
    pm->toString(buff, PROGRAM_LINE_LENGTH-4);
    _rpnf->appendOutputBuffer( toTrimmedString());
    _lcd->updateTerminalLine(10, _rpnf->getOutputBuffer());
}

//
// Extended memory to X in AUTO mode
//

Receiver_Address_AMX::Receiver_Address_AMX(void *components[]) : Receiver_Address::Receiver_Address(components){
    Moniker = _RECEIVER_ADDRESS_AMX;
}

void Receiver_Address_AMX::activate( int8_t prevReceiver){
    Receiver_Address::activate( _RECEIVER_AUTO_N);
    _lcd->updateStatusMC( _text);
}

void Receiver_Address_AMX::completeEntry( char *value){
    if (value[0] == 0){
        _rpnf->execute(FUNC_A_M2X);
        _rpnf->extMem->decrementCounter();
    }
    else{
        _rpnf->execute( FUNC_A_M2X, value);
    }
}

void Receiver_Address_AMX::updateDisplay( char *value){
    _lcd->updateStatusMC( _text);
}

//
// X to Extended memory in AUTO mode
//

Receiver_Address_AXM::Receiver_Address_AXM(void *components[]) : Receiver_Address::Receiver_Address(components){
    Moniker = _RECEIVER_ADDRESS_AXM;
}

void Receiver_Address_AXM::activate( int8_t prevReceiver){
    Receiver_Address::activate( _RECEIVER_AUTO_N);
    _lcd->updateStatusMC( _text);
}

void Receiver_Address_AXM::completeEntry( char *value){
    if (value[0] == 0){
        _rpnf->extMem->incrementCounter();
        _rpnf->execute(FUNC_A_X2M);
    }
    else{
        _rpnf->execute( FUNC_A_X2M, value);
    }
}

void Receiver_Address_AXM::updateDisplay( char *value){
    _lcd->updateStatusMC( _text);
}

//
// Set memory counter
//

Receiver_Address_MC::Receiver_Address_MC(void *components[]) : Receiver_Address::Receiver_Address(components){
    Moniker = _RECEIVER_ADDRESS_MC;
}

void Receiver_Address_MC::activate( int8_t prevReceiver){
    Receiver_Address::activate( _RECEIVER_AUTO_N);
    _lcd->updateStatusMC( _text);
}

void Receiver_Address_MC::completeEntry( char *value){
    _rpnf->extMem->setCounter( value);
}

void Receiver_Address_MC::updateDisplay( char *value){
    _lcd->updateStatusMC( _text);
}

//
// Set program counter
//

Receiver_Address_PC::Receiver_Address_PC(void *components[]) : Receiver_Address::Receiver_Address(components){
    Moniker = _RECEIVER_ADDRESS_PC;
}

void Receiver_Address_PC::activate( int8_t prevReceiver){
    Receiver_Address::activate( _RECEIVER_AUTO_N);
    _lcd->updateStatusPC( _text);
}

void Receiver_Address_PC::completeEntry( char *value){
    _rpnf->progMem->setCounter( value);
}

void Receiver_Address_PC::updateDisplay( char *value){
    _lcd->updateStatusPC( _text);
}
