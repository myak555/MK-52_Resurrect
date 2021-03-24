//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Entering numbers in AUTO mode
//

Receiver_Number::Receiver_Number(void *components[]) : Receiver::Receiver(components){
    _text = _rpnf->rpnStack->_DataEntry;
    Moniker = _RECEIVER_NUMBER;
    strcpy_P( _funlabel, PSTR("NUM"));
}

void Receiver_Number::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating NUMBER: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    _lcd->updateStatusFMODE( _funlabel);
    strcpy_P( _text, PSTR(" "));
    _mode = _MODE_NUMBER_WHOLE;
}

uint8_t Receiver_Number::tick( uint8_t scancode){
    int8_t ln = strlen(_text);
    if( ln>SCREEN_COLS) return 0; // prevents buffer overfill
    char c = _convertButton( _RN_ButtonConversion, scancode);
    switch( c){
        case 'e': // entry completed
        case 'f': // entry completed, action needed
            _mode = _MODE_OFF;
            completeEntry( toTrimmedString());
            _rpnf->requestNextReceiver(_return_to);
            return (c=='e')? 0: scancode;
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
            _processDigit(ln, c);
            break;
        case '-':
            if( _mode == _MODE_NUMBER_EXPONENT){
                _swapSign( _text + ln - 4, '+');
                break;
            }
            _swapSign( _text, ' ');
            break;
        case '.':
            if( _mode >= _MODE_NUMBER_DECIMAL) break;
            if (_mode == _MODE_NUMBER_WHOLE && ln>12) break;
            _mode = _MODE_NUMBER_DECIMAL;
            if( ln == 1){
                strcpy_P( _text+ln, PSTR("0."));
                break;
            }
            strcpy_P( _text+ln, PSTR("."));
            break;
        case 'E':
            _processExponent(ln);
            break;
        case 'c': // erase
            if( _processCx(ln)) return 0;
            break;
        default:
            break;
    }
    updateDisplay(toString());
    return 0;
}

char *Receiver_Number::toTrimmedString(){
    char *ptr = _text;
    while( *ptr==' ') ptr++;
    return ptr;
}

void Receiver_Number::completeEntry( char *value){
    _rpnf->rpnStack->X->fromString( value); 
}

void Receiver_Number::updateDisplay( char *value){
    _lcd->updateCalcRegister(0, toString());
}

void Receiver_Number::_processDigit( int8_t ln, char c){
    if (ln == 2 && _text[1] == '0'){
        _text[1] = c;
        return;
    }
    if (_mode == _MODE_NUMBER_WHOLE && ln > 17) return;
    if (_mode == _MODE_NUMBER_DECIMAL && ln > 13) return;
    if (_mode == _MODE_NUMBER_EXPONENT){
        _text[ln - 3] = _text[ln - 2];
        _text[ln - 2] = _text[ln - 1];
        _text[ln - 1] = c;
        return;
    }
    _text[ln++] = c;
    _text[ln] = 0;
    return;
}

void Receiver_Number::_processExponent( int8_t ln){
    if (_mode == _MODE_NUMBER_EXPONENT){
        _text[ln-5] = 0;
        _mode = _MODE_NUMBER_DECIMAL;
        return;
    }
    if (_mode == _MODE_NUMBER_WHOLE && ln > 12) return; // long integer
    if (_mode == _MODE_NUMBER_WHOLE && ln <= 1){ // only sign present
        strcpy_P( _text+1, _RN_StandardUnity);
        _mode = _MODE_NUMBER_EXPONENT;
        return;
    }
    if (_mode == _MODE_NUMBER_WHOLE && ln == 2 && _text[1] == '0'){ // integer zero
        strcpy_P( _text+1, _RN_StandardUnity);
        _mode = _MODE_NUMBER_EXPONENT;
        return;
    }
    UniversalValue *_uv = _rpnf->getUV();
    _uv->fromString(toTrimmedString());
    if (_uv->isEmpty() || (_uv->isInt() && _uv->toInt() == 0)){
        _text[0] = ' ';
        strcpy_P( _text+1, _RN_StandardUnity);
        return;
    }
    if (_mode == _MODE_NUMBER_WHOLE){ // going from integer to exponent
        strcpy_P( _text+ln, _RN_StandardUnity+1);
        _mode = _MODE_NUMBER_EXPONENT;
        return;
    }
    if (_text[ln-1] == '.'){ // ends with decimal point
        strcpy_P( _text+ln, _RN_StandardUnity + 2);
        _mode = _MODE_NUMBER_EXPONENT;
        return;
    }
    strcpy_P( _text+ln, _RN_StandardUnity + 3);
    _mode = _MODE_NUMBER_EXPONENT;
}

bool Receiver_Number::_processCx( int8_t ln){
    if (_mode == _MODE_NUMBER_EXPONENT){
        _text[ln - 1] = _text[ln - 2];
        _text[ln - 2] = _text[ln - 3];
        _text[ln - 3] = '0';
        return false;
    }
    if (_mode == _MODE_NUMBER_DECIMAL && _text[ln - 1] == '.'){
        _text[ln-1] = 0;
        _mode = _MODE_NUMBER_WHOLE;
        return false;
    }
    if (ln > 2){
        _text[ln-1] = 0;
        return false;
    }
    _mode = _MODE_OFF;
    strcpy_P( _text, PSTR("0"));
    completeEntry(_text);
    _rpnf->requestNextReceiver(_return_to);
    return true;
}

//
// Entering numbers in DATA mode
//

Receiver_Number_DATA::Receiver_Number_DATA(void *components[]) : Receiver_Number::Receiver_Number(components){
    Moniker = _RECEIVER_NUMBER_DATA;
}

void Receiver_Number_DATA::completeEntry( char *value){
    Extended_Memory *em = _rpnf->extMem;
    em->fromString(value);
    em->incrementCounter();
}

void Receiver_Number_DATA::updateDisplay( char *value){
    Extended_Memory *em = _rpnf->extMem;
    char *buff = _rpnf->getOutputBuffer();
    em->toCounterString(buff);
    _rpnf->appendOutputBuffer( toTrimmedString());
    _lcd->updateTerminalLine(SCREEN_ROWS-2, buff);
}

//
// Entering numbers in PROG mode
//

Receiver_Number_PROG::Receiver_Number_PROG(void *components[]) : Receiver_Number::Receiver_Number(components){
    Moniker = _RECEIVER_NUMBER_PROG;
}

void Receiver_Number_PROG::completeEntry( char *value){
    Program_Memory *pm = _rpnf->progMem;
    pm->updateLine(toTrimmedString());
    pm->incrementCounter();
}

void Receiver_Number_PROG::updateDisplay( char *value){
    Program_Memory *pm = _rpnf->progMem;
    char *buff = _rpnf->getOutputBuffer();
    pm->toCounterString(buff, 10);
    _rpnf->appendOutputBuffer( toTrimmedString());
    _lcd->updateTerminalLine(SCREEN_ROWS-2, buff);
}
