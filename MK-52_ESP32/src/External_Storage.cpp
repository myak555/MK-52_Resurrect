//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "RPN_Functions.hpp"

//#define __DEBUG

using namespace MK52_Interpreter;
#include "../functions/Functions.hpp"

const char SettingsFile[] PROGMEM = "/_MK52_Settings.txt";
const char StatusFile[] PROGMEM = "/_MK52_Status.MK52";

char *RPN_Functions::setOutputBuffer(char *text){
    if( text == NULL || text[0] == 0){
        _text[0] = 0;
        return _text;
    }
    strncpy( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer(char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    if( text == NULL || text[0] == 0) return _text;
    strncpy( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::setOutputBuffer_P(const char *text){
    if( text == NULL || strlen_P(text) == 0){
        _text[0] = 0;
        return _text;
    }
    strncpy_P( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer_P(const char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    if( strlen_P( text) == 0) return _text;
    strncpy_P( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

bool RPN_Functions::loadState(){
    #ifdef __DEBUG
    Serial.println("Loading state file");
    #endif
    requestNextReceiver( _RECEIVER_AUTO_N);
    if( _sd->openFile_P(StatusFile)) return true;
    bool result = _read( true, true, true, true);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveState( int8_t finalReceiver){
    #ifdef __DEBUG
    Serial.println("Saving state...");
    #endif
    if( _sd->openFile_P(StatusFile, true)) return true;
    bool result = _writeConfig( finalReceiver);
    if(!result) result = _writeStack();
    if(!result) result = _writeRegisters();
    if(!result) result = _writeProgram();
    if(!result) result = _writeData();
    if(!result) result = _writeReturnStack();
    _sd->closeFile();
    return result;
}

bool RPN_Functions::loadProgram(char *name){
    #ifdef __DEBUG
    Serial.println("Loading program file");
    #endif
    if( _sd->openFile(name)) return true;
    progMem->clear();
    bool result = _read( false, true, false);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveProgram(char *name){
    #ifdef __DEBUG
    Serial.print("Saving program file");
    if( name != NULL){
        Serial.print(" as ");
        Serial.println(name);
    }
    else{
        Serial.println();
    }
    #endif
    if( _sd->openFile(name, true)) return true;
    bool result = _writeProgram();
    _sd->closeFile();
    _sd->readFolderItems();
    return result;
}

bool RPN_Functions::loadData(char *name){
    #ifdef __DEBUG
    Serial.println("Loading data file");
    #endif
    if( _sd->openFile(name)) return true;
    bool result = _read( false, false, true);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveData(char *name){
    #ifdef __DEBUG
    Serial.print("Saving data file");
    if( name != NULL){
        Serial.print(" as ");
        Serial.println(name);
    }
    else{
        Serial.println();
    }
    #endif
    if( _sd->openFile(name, true)) return true;
    bool result = _writeData();
    _sd->closeFile();
    _sd->readFolderItems();
    return result;
}

bool RPN_Functions::loadAll(char *name){
    #ifdef __DEBUG
    Serial.println("Loading all data");
    #endif
    if( _sd->openFile(name)) return true;
    rpnStack->clear();
    regMem->clear();
    progMem->clear();
    extMem->clear();
    bool result = _read( true, true, true);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveAll(char *name){
    #ifdef __DEBUG
    Serial.print("Saving all");
    if( name != NULL){
        Serial.print(" as ");
        Serial.println(name);
    }
    else{
        Serial.println();
    }
    #endif
    if( _sd->openFile(name, true)) return true;
    bool result = _writeStack();
    if(!result) result = _writeRegisters();
    if(!result) result = _writeProgram();
    if(!result) result = _writeData();
    _sd->closeFile();
    _sd->readFolderItems();
    return result;
}

void RPN_Functions::MkDir( char *name){
    _sd->createFolder( name);
    int16_t tmp = _sd->listingPosition;
    _sd->readFolderItems();
    _sd->setListingPosition(tmp);
}

void RPN_Functions::RemoveFile(){
    _sd->deleteEntity( _sd->getItemFromListing());
    int16_t tmp = _sd->listingPosition;
    _sd->readFolderItems();
    _sd->setListingPosition(tmp);
}

void RPN_Functions::stepIn(){
    char *filename = _sd->getItemFromListing();
    if( !_sd->stepIn( filename)) return;
    if( UniversalValue::_endsWith_P( filename, PSTR(".DAT")))
        loadData( filename);
    else
        loadProgram( filename);
}

char *RPN_Functions::formFileName(char *name, const char* ext){
    char *tmpName = _sd->makeEntityName(name);
    int16_t ln = strlen(tmpName);
    if( ln<=0 || ext == NULL || ln>=CURRENT_FILE_LEN-5) return tmpName;
    if (!UniversalValue::_endsWith_P(tmpName, ext))
        sprintf_P( tmpName+ln, "%s", ext);
    return tmpName;
}

bool RPN_Functions::_writeConfig(int8_t finalReceiver){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 configuration"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    #ifdef __DEBUG
    Serial.print( "Receiver to start: ");
    Serial.println( finalReceiver);
    #endif
    switch(finalReceiver){
        case _RECEIVER_PROG_N:
            sprintf_P( _text, PSTR("MODE=PROG"));
            break;
        case _RECEIVER_DATA_N:
            sprintf_P( _text, PSTR("MODE=DATA"));
            break;
        case _RECEIVER_FILE_N:
            sprintf_P( _text, PSTR("MODE=FILE"));
            break;
        default:
            sprintf_P( _text, PSTR("MODE=AUTO"));
    }
    return _sd->println(_text);
}

bool RPN_Functions::_writeStack(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 stack"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;    
    sprintf_P( _text, PSTR("DMODE=%s"), rpnStack->getDModeName());
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("EMODE=%s"), progMem->getEModeName());
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("Bx="));
    rpnStack->Bx->toString(_text+3);
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("X="));
    rpnStack->X->toString(_text+2);
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("Y="));
    rpnStack->Y->toString(_text+2);
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("Z="));
    rpnStack->Z->toString(_text+2);
    if(_sd->println(_text)) return true;
    sprintf_P( _text, PSTR("T="));
    rpnStack->T->toString(_text+2);
    if(_sd->println(_text)) return true;
    if( rpnStack->customLabels()){
        sprintf_P( _text, PSTR("LX=%s"), rpnStack->X_Label);
        if(_sd->println(_text)) return true;
        sprintf_P( _text, PSTR("LY=%s"), rpnStack->Y_Label);
        if(_sd->println(_text)) return true;
        sprintf_P( _text, PSTR("LZ=%s"), rpnStack->Z_Label);
        if(_sd->println(_text)) return true;
        sprintf_P( _text, PSTR("LT=%s"), rpnStack->T_Label);
        if(_sd->println(_text)) return true;
    }
    #ifdef __DEBUG
    Serial.println("Stack written");
    #endif
    return false;
}

bool RPN_Functions::_writeRegisters(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 registers"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    for( uint8_t i=0; i<REGISTER_MEMORY_NVALS; i++){
        _tmpuv->fromLocation(regMem->_registerAddress(i));
        if( _tmpuv->isEmpty()) continue;
        sprintf_P( _text, PSTR("R%02u="), i);
        _tmpuv->toString( _text+4);
        if(_sd->println(_text)) return true;
    }
    #ifdef __DEBUG
    Serial.println("Registers written");
    #endif
    return false;
}

bool RPN_Functions::_writeProgram(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 program"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    uint32_t ctr = progMem->getCounter();
    sprintf_P( _text, PSTR("PC=%04u"), ctr);
    if(_sd->println(_text)) return true;
    progMem->resetCounter();
    while( !progMem->isAtEnd()){
        char *ptr = progMem->getCurrentLine();
        if( *ptr==0){ // empty lines ignored
            progMem->incrementCounter();
            continue;
        }
        snprintf_P( _text, PROGRAM_LINE_LENGTH, PSTR("P%04u: %s"), progMem->getCounter(), ptr);
        _text[PROGRAM_LINE_LENGTH-1] = 0;
        if(_sd->println(_text)){
            progMem->setCounter(ctr);
            return true;
        }
        progMem->incrementCounter();
    }
    progMem->setCounter(ctr);
    #ifdef __DEBUG
    Serial.println("Program written");
    #endif
    return false;
}

bool RPN_Functions::_writeData(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 data"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    sprintf_P( _text, PSTR("MC=%04u"), extMem->getCounter());
    if(_sd->println(_text)) return true;    
    for( uint32_t i=0; i<EXTENDED_MEMORY_NVALS; i++){
        uint8_t *ptr = extMem->getLine( i);
        if( *ptr==VALUE_TYPE_EMPTY) continue;
        _tmpuv->fromLocation( ptr);
        sprintf_P( _text, PSTR("M%04u: "), i);
        _tmpuv->toString(_text+7);
        if(!_sd->println(_text)) continue;
        return true;
    }
    #ifdef __DEBUG
    Serial.println("Data written");
    #endif
    return false;
}

bool RPN_Functions::_writeReturnStack(){
    uint32_t n = progMem->getCallStackPtr();
    if (!n) return false;
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 return stack"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    sprintf_P( _text, PSTR("RS=%04u"), n);
    if(_sd->println(_text)) return true;    
    for( uint32_t i=0; i<n; i++){
        progMem->getCallStackValues( _text, i);
        if(!_sd->println(_text)) continue;
        return true;
    }
    #ifdef __DEBUG
    Serial.println("Return stack written");
    #endif
    return false;
}

bool RPN_Functions::_read(bool readStack, bool readProg, bool readMem, bool readConfig){
    int8_t nextMode = _RECEIVER_AUTO_N;
    uint32_t pmemctr = progMem->getCounter();
    uint32_t ememctr = extMem->getCounter();
    //uint callStackDeclared = 0; presented in dump file, but not used
    uint32_t callStackActual = 0;
    uint8_t regAddress = 0;
    char *ptr = NULL;
    while( true){
        bool result = _sd->readln( _text, PROGRAM_LINE_LENGTH);
        if( result && _text[0] == 0) break;
        #ifdef __DEBUG
        Serial.println( _text);
        #endif
        if( _text[0] == 0) continue;
        if( _text[0] == '#') continue;
        if( readConfig){
            if( UniversalValue::_startsWith_P( _text, PSTR("MODE=PROG"))){
                requestNextReceiver( _RECEIVER_PROG_N);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("MODE=FILE"))){
                requestNextReceiver( _RECEIVER_FILE_N);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("MODE=DATA"))){
                requestNextReceiver( _RECEIVER_DATA_N);
                continue;
            }
        }
        if( readProg){
            if( UniversalValue::_startsWith_P( _text, PSTR("PC="))){
                progMem->setCounter( _text+3);
                pmemctr = progMem->getCounter();
                continue;
            }
            if( UniversalValue::_isProgramAddress(_text)){
                ptr = UniversalValue::_selectAddress(_text);
                while( *ptr==' ') ptr++;
                if( *ptr == 0) continue; // string too short or incorrectly formed
                progMem->setCounter( _text+1);
                progMem->replaceLine( ptr); // TODO: name conversion
                continue;
            }
            if( UniversalValue::_isReturnStackAddress(_text)){
                ptr = UniversalValue::_selectAddress(_text);
                while( *ptr==' ') ptr++;
                if( *ptr == 0) continue; // string too short or incorrectly formed
                progMem->setCallStackValues(callStackActual, _text+1, ptr);
                continue;
            }
        }
        if( readMem){
            if( UniversalValue::_startsWith_P( _text, PSTR("MC="))){
                extMem->setCounter( _text+3);
                ememctr = extMem->getCounter();
                continue;
            }
            if( UniversalValue::_isMemoryAddress(_text)){
                ptr = UniversalValue::_selectAddress(_text);
                if( *ptr == 0) continue; // string too short or incorrectly formed
                extMem->setCounter( _text+1);
                _tmpuv->fromString( ptr);
                if( _tmpuv->getType() > 0) _tmpuv->toLocation( extMem->getCurrentLine());
                continue;
            }
        }
        if( readStack){
            if( UniversalValue::_startsWith_P( _text, PSTR("X="))){
                rpnStack->X->fromString( _text + 2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("Y="))){
                rpnStack->Y->fromString( _text + 2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("Z="))){
                rpnStack->Z->fromString( _text + 2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("T="))){
                rpnStack->T->fromString( _text + 2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("Bx="))){
                rpnStack->Bx->fromString( _text + 3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("DMODE=DEG"))){
                rpnStack->setDMode(0);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("DMODE=RAD"))){
                rpnStack->setDMode(1);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("DMODE=GRD"))){
                rpnStack->setDMode(2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("EMODE=OVR"))){
                progMem->setEMode(0);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("EMODE=INS"))){
                progMem->setEMode(1);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("EMODE=SHF"))){
                progMem->setEMode(2);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LX="))){
                rpnStack->setLabel( 0, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LY="))){
                rpnStack->setLabel( 1, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LZ="))){
                rpnStack->setLabel( 2, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LT="))){
                rpnStack->setLabel( 3, _text+3);
                continue;
            }
            regAddress = UniversalValue::_isRegisterAddress(_text);
            if( regAddress < REGISTER_MEMORY_NVALS){
                _tmpuv->fromString( _text+4);
                _tmpuv->toLocation( regMem->_registerAddress(regAddress));
                continue;
            }
        }
    }
    progMem->setCounter( pmemctr);
    extMem->setCounter( ememctr);
    #ifdef __DEBUG
    Serial.println("Read completed");
    #endif
    return false;
}
