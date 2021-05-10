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

Receiver_FILE_Name::Receiver_FILE_Name(void *components[]) : Receiver::Receiver(components){
    Moniker = _RECEIVER_FILE_Name;
    strcpy_P( _funlabel, PSTR("FIL"));
    strcpy_P( _Question, _FILE_Message_FileName); 
}

void Receiver_FILE_Name::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating FILE Name: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    _text = (char *)malloc( CURRENT_FILE_LEN+1);
    if( _text != NULL)
        memset( _text, 0, CURRENT_FILE_LEN+1);
    _mode = _MODE_ENTRY_TEXT;
    updateDisplay( toString());
}

uint8_t Receiver_FILE_Name::tick( uint8_t scancode){
    if( !_text){
        _rpnf->requestNextReceiver(_return_to);
        return 0;
    } 
    if (_mode < _MODE_ENTRY_CONFIRM) return _mode1_Tick(scancode);
    return _mode2_Tick(scancode);
}

char *Receiver_FILE_Name::toTrimmedString(){
    if( !_text) return NULL;
    char *ptr = _text;
    while( *ptr == ' ') ptr++;
    return ptr;
}

uint8_t Receiver_FILE_Name::_mode1_Tick( uint8_t scancode){
    int16_t ln = strlen( _text); 
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
            return 0;
        case 32:
            if (ln <= 0){
                free(_text);
                return _rpnf->requestNextReceiver(_return_to);
            }
            _text[ln-1] = 0;
            updateDisplay(toString());
            return 0;
        case 33:
            free(_text);
            _rpnf->requestNextReceiver(_return_to);
            return 33;
        default: 
            break;
    }
    char c = 0;
    switch (_mode){
        case _MODE_ENTRY_NUMBER:
            c = _convertButton(_RFN_DigitConversion, scancode);
            break;
        default:
            c = _convertButton(_RT_LetterConversion, scancode);
            break;
    }
    if (c == 0) return 0;
    if ( ln >= CURRENT_FILE_LEN) return 0;
    _text[ln++] = c;
    _text[ln] = 0;
    updateDisplay(toString());
    return 0;
}

uint8_t Receiver_FILE_Name::_mode2_Tick( uint8_t scancode){
    switch (scancode){
        case 0:
            return 0;
        case 31:
            completeEntry(toString());
            return _rpnf->requestNextReceiver(_return_to);
        case 32:
        case 33:
            free(_text);
            _rpnf->requestNextReceiver(_return_to);
            return (scancode == 33)? 33: 0;
        default:
            _mode = _MODE_ENTRY_TEXT;
            break;
    }
    return scancode;
}

void Receiver_FILE_Name::completeEntry( char *value){
    char *tmpName = _rpnf->formFileName(value, _rpnf->_defaultProgramExt());
    if( _rpnf->fileExists(tmpName)){
        _mode = _MODE_ENTRY_CONFIRM;
        updateDisplay(toString());
        return;
    }
    free(_text);
    _rpnf->saveProgram( tmpName);
    _rpnf->requestNextReceiver(_return_to);
}

void Receiver_FILE_Name::updateDisplay( char *value){
    int16_t ln = strlen( value) - SCREEN_COLS + 1;
    if( ln < 0) ln = 0;
    _lcd->updateTerminalLine(SCREEN_ROWS - 2, value+ln);
    switch (_mode){
        case _MODE_ENTRY_TEXT:
            _lcd->updateStatusFMODE("TXT");
            _lcd->updateTerminalLine(SCREEN_ROWS - 3, _Question);
            break;
        case _MODE_ENTRY_NUMBER:
            _lcd->updateStatusFMODE("NUM");
            _lcd->updateTerminalLine(SCREEN_ROWS - 3, _Question);
            break;
        default:
            _lcd->updateStatusFMODE("   ");
            _lcd->updateTerminalLine(SCREEN_ROWS - 3, _FILE_Message_Overwrite);
            break;
    }
}

//
// Implements a text data entry for saving program with data
//

Receiver_FILE_All::Receiver_FILE_All(void *components[]) : Receiver_FILE_Name::Receiver_FILE_Name(components){
    Moniker = _RECEIVER_FILE_All;
}

void Receiver_FILE_All::completeEntry( char *value){
    char *tmpName = _rpnf->formFileName(value, _rpnf->_defaultProgramExt());
    if( _rpnf->fileExists(tmpName)){
        _mode = _MODE_ENTRY_CONFIRM;
        updateDisplay(toString());
        return;
    }
    free(_text);
    _rpnf->saveAll( tmpName);
    _rpnf->requestNextReceiver(_return_to);
}

//
// Implements a text data entry for saving data only
//

Receiver_FILE_Data::Receiver_FILE_Data(void *components[]) : Receiver_FILE_Name::Receiver_FILE_Name(components){
    Moniker = _RECEIVER_FILE_Data;
}

void Receiver_FILE_Data::completeEntry( char *value){
    char *tmpName = _rpnf->formFileName(value, _rpnf->_defaultDataExt());
    if( _rpnf->fileExists(tmpName)){
        _mode = _MODE_ENTRY_CONFIRM;
        updateDisplay(toString());
        return;
    }
    free(_text);
    _rpnf->saveData( tmpName);
    _rpnf->requestNextReceiver(_return_to);
}

//
// Implements a text data entry for making directories
//

Receiver_FILE_MkDir::Receiver_FILE_MkDir(void *components[]) : Receiver_FILE_Name::Receiver_FILE_Name(components){
    Moniker = _RECEIVER_FILE_MkDir;
    strcpy_P( _Question, _FILE_Message_FolderName); 
}

void Receiver_FILE_MkDir::completeEntry( char *value){
    char *tmpName = _rpnf->formFileName(value);
    _rpnf->MkDir( tmpName);
    _rpnf->requestNextReceiver(_return_to);
    free(_text);
}
