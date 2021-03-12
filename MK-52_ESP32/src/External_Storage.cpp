//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "RPN_Functions.hpp"

#define __DEBUG
using namespace MK52_Interpreter;
#include "../functions/functions.hpp"

const char SettingsFile[] PROGMEM = "/_MK52_Settings.txt";
const char StatusFile[] PROGMEM = "/_MK52_Status.MK52";
const char SD_DefaultExt[] PROGMEM = ".MK52";
const char SD_DefaultDateExt[] PROGMEM = ".DAT";

char *RPN_Functions::setOutputBuffer(char *text){
    strncpy( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer(char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    strncpy( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::setOutputBuffer_P(const char *text){
    strncpy_P( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer_P(const char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    strncpy_P( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH] = 0;
    return _text;
}

bool RPN_Functions::loadStateFile(){
    #ifdef __DEBUG
    Serial.println("Loading state file");
    #endif
    if( _sd->openFile_P(StatusFile)) return true;
    bool result = _readFile( true, true, true);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveStateFile(){
    #ifdef __DEBUG
    Serial.println("Saving state...");
    #endif
    if( _sd->openFile_P(StatusFile, true)) return true;
    bool result = _writeStackFile();
    if(!result) result = _writeRegisterFile();
    if(!result) result = _writeProgramFile();
    if(!result) result = _writeDataFile();
    _sd->closeFile();
    return result;
}

bool RPN_Functions::loadProgramFile(char *name){
    #ifdef __DEBUG
    Serial.println("Loading program file");
    #endif
    if( _sd->openFile(name)) return true;
    progMem->clear();
    bool result = _readFile( false, true, false);
    _sd->closeFile();
    Serial.println("File load done");
    return result;
}

bool RPN_Functions::saveProgramFile(char *name){
    Serial.print("Saving program file");
    if( name != NULL){
        Serial.print(" as ");
        Serial.println(name);
    }
    else{
        Serial.println();
    }
    if( _sd->openFile(name, true)) return true;
    bool result = _writeProgramFile();
    _sd->closeFile();
    _sd->readFolderItems();
    return result;
}

bool RPN_Functions::loadDataFile(char *name){
    #ifdef __DEBUG
    Serial.println("Loading data file");
    #endif
    if( _sd->openFile(name)) return true;
    bool result = _readFile( false, false, true);
    _sd->closeFile();
    return result;
}

bool RPN_Functions::saveDataFile(char *name){
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
    bool result = _writeDataFile();
    _sd->closeFile();
    _sd->readFolderItems();
    return result;
}

bool RPN_Functions::_writeStackFile(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 stack"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    sprintf_P( _text, PSTR("DMODE=%s"), rpnStack->getDModeName());
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
    if( rpnStack->customStackLabels()){
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

bool RPN_Functions::_writeRegisterFile(){
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

bool RPN_Functions::_writeProgramFile(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 program"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    uint32_t ctr = progMem->getCounter();
    sprintf_P( _text, PSTR("PC=%04u"), ctr);
    progMem->resetCounter();
    if(_sd->println(_text)) return true;
    while( !progMem->isAtEnd()){
        char *ptr = progMem->getCurrentLine();
        if( *ptr==0){ // empty lines ignored
            progMem->incrementCounter();
            continue;
        }
        snprintf_P( _text, PROGRAM_LINE_LENGTH, PSTR("P%04u: %s"), progMem->getCounter(), ptr);
        _text[PROGRAM_LINE_LENGTH-1] = 0;
        Serial.println(_text);
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

bool RPN_Functions::_writeDataFile(){
    if( _sd->println_P(PSTR("#"))) return true;
    if( _sd->println_P(PSTR("# MK-52 data"))) return true;
    if( _sd->println_P(PSTR("#"))) return true;
    sprintf_P( _text, PSTR("MC=%04u"), extMem->getCounter());
    if(_sd->println(_text)) return true;    
    for( uint32_t i=0; i<EXTENDED_MEMORY_NVALS; i++){
        uint8_t *ptr = extMem->getLine( i);
        if( *ptr==VALUE_TYPE_EMPTY) continue;
        #ifdef __DEBUG
        Serial.print("Preparing Data: ");
        Serial.println(i);
        #endif
        _tmpuv->fromLocation( ptr);
        sprintf_P( _text, PSTR("M%04u: "), i);
        _tmpuv->toString(_text+7);
        #ifdef __DEBUG
        Serial.print("Writing Data: [");
        Serial.print(_text);
        Serial.println("]");
        #endif
        if(!_sd->println(_text)) continue;
        return true;
    }
    #ifdef __DEBUG
    Serial.println("Data written");
    #endif
    return false;
}

bool RPN_Functions::_readFile(bool readStack, bool readProg, bool readMem){
    uint32_t pmemctr = progMem->getCounter();
    uint32_t ememctr = extMem->getCounter();
    uint8_t regAddress = 0;
    char *ptr = NULL;
    while( true){
        bool result = _sd->readln( _text, PROGRAM_LINE_LENGTH);
        if( result && _text[0] == 0) break;
        Serial.println( _text);
        if( _text[0] == 0) continue;
        if( _text[0] == '#') continue;
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
            if( UniversalValue::_startsWith_P( _text, PSTR("LX="))){
                rpnStack->setStackLabel( 0, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LY="))){
                rpnStack->setStackLabel( 1, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LZ="))){
                rpnStack->setStackLabel( 2, _text+3);
                continue;
            }
            if( UniversalValue::_startsWith_P( _text, PSTR("LT="))){
                rpnStack->setStackLabel( 3, _text+3);
                continue;
            }
            regAddress = UniversalValue::_isRegisterAddress(_text);
            if( regAddress < REGISTER_MEMORY_NVALS){
                _tmpuv->fromLocation( regMem->_registerAddress(regAddress));
                _tmpuv->fromString( _text+4);
                continue;
            }
        }
    }
    Serial.println("Read completed");
    progMem->setCounter( pmemctr);
    extMem->setCounter( ememctr);
    return false;
}
