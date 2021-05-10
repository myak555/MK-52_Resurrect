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

Receiver_Text::Receiver_Text(void *components[]) : Receiver::Receiver(components){
    Moniker = _RECEIVER_TEXT;
    strcpy_P( _funlabel, PSTR("TXT"));
    _letter_Converter = _RT_LetterConversion;
    _number_Converter = _RT_DigitConversion;
}

Receiver_Text_FN::Receiver_Text_FN(void *components[]) : Receiver_Text::Receiver_Text(components){
    Moniker = _RECEIVER_TEXT_FN;
    strcpy_P( _funlabel, PSTR("FIL"));
    _letter_Converter = _RT_LetterConversion;
    _number_Converter = _RFN_DigitConversion;
}

void Receiver_Text::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating TEXT: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    _text = (char *)malloc( PROGRAM_LINE_LENGTH+1);
    char *ptr = _rpnf->progMem->getCurrentLine();
    if( _text != NULL){
        memset( _text, 0, PROGRAM_LINE_LENGTH+1);
        if( ptr[0] != 0) strncpy( _text, ptr, PROGRAM_LINE_LENGTH);
    } 
    _mode = _MODE_ENTRY_TEXT;
    updateDisplay( toString());
}

uint8_t Receiver_Text::tick( uint8_t scancode){
    int16_t ln = 0;
    if( _text != NULL) ln = strlen( _text); 
    switch( scancode){
        case 0:
            return 0;
        case 4:
            _mode++;
            if (_mode > _MODE_ENTRY_NUMBER) _mode = _MODE_ENTRY_TEXT;
            updateDisplay(toString());
            return 0;
        case 31:
            completeEntry(toString());
            return _rpnf->requestNextReceiver(_return_to);
        case 32:
            if( _text && ln > 0) _text[ln-1] = 0;
            updateDisplay(toString());
            return 0;
        case 33:
            if( _text != NULL) free(_text);
            _rpnf->requestNextReceiver(_return_to);
            return 33;
        default: 
            break;
    }
    if( _text == NULL) return 0;
    char c = 0;
    switch (_mode){
        case _MODE_ENTRY_NUMBER:
            c = _convertButton(_number_Converter, scancode);
            break;
        default:
            c = _convertButton(_letter_Converter, scancode);
            break;
    }
    if (c == 0) return 0;
    if ( ln >= PROGRAM_LINE_LENGTH) return 0;
    _text[ln++] = c;
    _text[ln] = 0;
    updateDisplay(toString());
    return 0;
}

char *Receiver_Text::toTrimmedString(){
    if( !_text) return NULL;
    char *ptr = _text;
    while( *ptr == ' ') ptr++;
    return ptr;
}

void Receiver_Text::completeEntry( char *value){
    Program_Memory *pm = _rpnf->progMem;
    if( _text == NULL){
        pm->deleteLine();
        return;
    }
    if (_text[0] == 0){
        free( _text);
        pm->deleteLine();
        return;
    }
    pm->replaceLine(_text);
    pm->incrementCounter();
    free(_text);
}

void Receiver_Text::updateDisplay( char *value){
    Program_Memory *pm = _rpnf->progMem;
    char *buff = _rpnf->getOutputBuffer();
    if( _text != NULL){
        pm->toCounterString(buff, PROGRAM_LINE_LENGTH);
        int16_t ln = strlen(_text) - SCREEN_COLS + 7;
        if( ln<0) ln = 0;
        _rpnf->appendOutputBuffer( _text+ln);
    }
    else pm->toString(buff, PROGRAM_LINE_LENGTH);
    _lcd->updateTerminalLine(10, buff);
    switch(_mode){
        case _MODE_ENTRY_TEXT:
            _lcd->updateStatusFMODE( "TXT");
            break;
        case _MODE_ENTRY_NUMBER:
            _lcd->updateStatusFMODE( "NUM");
            break;
        default:
            _lcd->updateStatusFMODE( "SYM");
            break;
    }
}
