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

#include <math.h>
#include "../functions/functions.hpp"

const char SettingsFile[] PROGMEM = "/_MK52_Settings.txt";
const char StatusFile[] PROGMEM = "/_MK52_Status.MK52";
const char SD_DefaultExt[] PROGMEM = ".MK52";

//
// Inits the calculator program memory
//
unsigned long RPN_Functions::init( void *components[]) {
    _components = components;
    rpnStack = (RPN_Stack *)components[COMPONENT_STACK];
    progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    _sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];

    _buffer = (char *)malloc( SCREEN_BUFFER_SIZE);
    _text = (char*)malloc( PROGRAM_LINE_LENGTH + 9);
    memset( _buffer, 0, SCREEN_BUFFER_SIZE);
    memset( _text, 0, PROGRAM_LINE_LENGTH + 9);
    char *ptr = _buffer;
    for( uint8_t i=0; i<SCREEN_ROWS; i++){
        _lines[i] = ptr;
        ptr += SCREEN_COLS + 1;
    }
    _tmpuv = new UniversalValue( (uint8_t *)(_text + PROGRAM_LINE_LENGTH));
    
    // #define FUNC_COMMENT            1
    _appendFunction( new Func_Comment());
    // #define FUNC_INCREMENT_PC       2
    _appendFunction( new Func_Increment_PC());
    // #define FUNC_DECREMENT_PC       3
    _appendFunction( new Func_Decrement_PC());
    // #define FUNC_INCREMENT_MC       4
    _appendFunction( new Func_Increment_MC());
    // #define FUNC_DECREMENT_MC       5
    _appendFunction( new Func_Decrement_MC());
    // #define FUNC_RESET_PC           6
    _appendFunction( new Func_Reset_PC());
    // #define FUNC_RESET_MC           7
    _appendFunction( new Func_Reset_MC());
    // #define FUNC_TOGGLE_DMOD        8
    _appendFunction( new Func_Toggle_DMOD());
    // #define FUNC_SET_DMOD_DEG       9
    _appendFunction( new Func_set_DMOD_DEG());
    // #define FUNC_SET_DMOD_RAD       10
    _appendFunction( new Func_set_DMOD_RAD());
    // #define FUNC_SET_DMOD_GRD       11
    _appendFunction( new Func_set_DMOD_GRD());
    // #define FUNC_NEGATE             12
    _appendFunction( new Func_Negate());
    // #define FUNC_ENTER              13
    _appendFunction( new Func_Enter());
    // #define FUNC_SWAP               14
    _appendFunction( new Func_Swap());
    // #define FUNC_PLUS               15
    _appendFunction( new Func_Plus());
    // #define FUNC_MINUS              16
    _appendFunction( new Func_Minus());
    // #define FUNC_MULTIPLY           17
    _appendFunction( new Func_Multiply());
    // #define FUNC_DIVIDE             18
    _appendFunction( new Func_Divide());
    // #define FUNC_CLEAR_X            19
    _appendFunction( new Func_Clear_X());
    // #define FUNC_SIN                20
    _appendFunction( new Func_Sin());
    // #define FUNC_ARCSIN             21
    _appendFunction( new Func_ArcSin());
    // #define FUNC_COS                22
    _appendFunction( new Func_Cos());
    // #define FUNC_ARCCOS             23
    _appendFunction( new Func_ArcCos());
    // #define FUNC_TG                 24
    _appendFunction( new Func_Tg());
    // #define FUNC_ARCTG              25
    _appendFunction( new Func_ArcTg());
    // #define FUNC_EXP                26
    _appendFunction( new Func_Exp());
    // #define FUNC_10X                27
    _appendFunction( new Func_10x());
    // #define FUNC_LG                 28
    _appendFunction( new Func_Lg());
    // #define FUNC_LN                 29
    _appendFunction( new Func_Ln());
    // #define FUNC_POW                30
    _appendFunction( new Func_Pow());
    // #define FUNC_LOG                31
    _appendFunction( new Func_Log());
    // #define FUNC_ROT                32
    _appendFunction( new Func_Rot());
    // #define FUNC_X2                 33
    _appendFunction( new Func_X2());
    // #define FUNC_1X                 34
    _appendFunction( new Func_1X());
    // #define FUNC_SQRT               35
    _appendFunction( new Func_SQRT());
    // #define FUNC_PI                 36
    _appendFunction( new Func_PI());
    // #define FUNC_EE                 37
    _appendFunction( new Func_EE());
    // #define FUNC_BX                 38
    _appendFunction( new Func_Bx());
    // #define FUNC_RAND               39
    _appendFunction( new Func_Rand());
    // #define FUNC_SEED               40
    _appendFunction( new Func_Seed());
    // #define FUNC_WHOLE              41
    _appendFunction( new Func_Whole());
    // #define FUNC_FRAC               42
    _appendFunction( new Func_Frac());
    // #define FUNC_MAX                43
    _appendFunction( new Func_Max());
    // #define FUNC_ABS                44
    _appendFunction( new Func_Abs());
    // #define FUNC_SIGN               45
    _appendFunction( new Func_Sign());
    // #define FUNC_AND                46
    _appendFunction( new Func_And());
    // #define FUNC_OR                 47
    _appendFunction( new Func_Or());
    // #define FUNC_XOR                48
    _appendFunction( new Func_Xor());
    // #define FUNC_NOT                49
    _appendFunction( new Func_Not());
    // #define FUNC_D2DM               50
    _appendFunction( new Func_D2DM());
    // #define FUNC_D2DMS              51
    _appendFunction( new Func_D2DMS());
    // #define FUNC_DM2D               52
    _appendFunction( new Func_DM2D());
    // #define FUNC_DMS2D              53
    _appendFunction( new Func_DMS2D());
    // #define FUNC_D2RAD              54
    _appendFunction( new Func_D2Rad());
    // #define FUNC_RAD2D              55
    _appendFunction( new Func_Rad2D());
    // #define FUNC_MM2IN              56
    _appendFunction( new Func_mm2in());
    // #define FUNC_IN2MM              57
    _appendFunction( new Func_in2mm());
    // #define FUNC_M2X                58
    _appendFunction( new Func_M2X());
    // #define FUNC_X2M                59
    _appendFunction( new Func_X2M());
    // #define FUNC_K_M2X              60
    _appendFunction( new Func_K_M2X());
    // #define FUNC_K_X2M              61
    _appendFunction( new Func_K_X2M());
    // #define FUNC_A_M2X              62
    _appendFunction( new Func_A_M2X());
    // #define FUNC_A_X2M              63
    _appendFunction( new Func_A_X2M());
    // #define FUNC_GOTO               64
    _appendFunction( new Func_GOTO());
    // #define FUNC_GOSUB              65
    _appendFunction( new Func_GOSUB());
    // #define FUNC_RETURN             66
    _appendFunction( new Func_Return());
    // #define FUNC_MEMSET             67
    _appendFunction( new Func_MemSet());
    // #define FUNC_MEMSWP             68
    _appendFunction( new Func_MemSwp());
    // #define FUNC_MEXTOX             69
    _appendFunction( new Func_MexToX());
    // #define FUNC_XTOMEX             70
    _appendFunction( new Func_XToMex());
    // #define FUNC_MEXTOR             71
    _appendFunction( new Func_MexToR());
    // #define FUNC_RTOMEX             72
    _appendFunction( new Func_RToMex());
    // #define FUNC_MEXCLR             73
    _appendFunction( new Func_MexClr());
    // #define FUNC_TOGGLE_EMOD        74
    _appendFunction( new Func_Toggle_EMOD());
    // #define FUNC_STOP               75
    _appendFunction( new Func_Stop());
    // #define FUNC_MKDIR              76
    _appendFunction( new Func_MkDir());
    // #define FUNC_UPDIR              77
    _appendFunction( new Func_UpDir());
    // #define FUNC_NEXTFILE           78
    _appendFunction( new Func_NextFile());
    // #define FUNC_PREVFILE           79
    _appendFunction( new Func_PrevFile());
    // #define FUNC_REMOVE             80
    _appendFunction( new Func_Remove());
    // #define FUNC_STEPIN             81
    _appendFunction( new Func_StepIn());
    // #define FUNC_SAVE               82
    _appendFunction( new Func_Save());
    // #define FUNC_SAVEAS             83
    _appendFunction( new Func_SaveAs());
    // #define FUNC_LOAD               84
    _appendFunction( new Func_Load());
    // #define FUNC_LOADFROM           85
    _appendFunction( new Func_LoadFrom());
    // #define FUNC_CHAIN              86
    _appendFunction( new Func_Chain());
    // #define FUNC_SAVEDATA           87
    _appendFunction( new Func_SaveData());
    // #define FUNC_SAVEDATAAS         88
    _appendFunction( new Func_SaveDataAs());
    // #define FUNC_LOADDATA           89
    _appendFunction( new Func_LoadData());
    // #define FUNC_LOADDATAFROM       90
    _appendFunction( new Func_LoadDataFrom());
    // #define FUNC_GOMEM              91
    _appendFunction( new Func_GOMEM());
    // #define FUNC_IFNOTLT0           92
    _appendFunction( new Func_IfNotLT0());
    // #define FUNC_IFNOTEQ0           93
    _appendFunction( new Func_IfNotEQ0());
    // #define FUNC_IFNOTGE0           94
    _appendFunction( new Func_IfNotGE0());
    // #define FUNC_IFNOTNE0           95
    _appendFunction( new Func_IfNotNE0());
    // #define FUNC_IFNOTLTY           96
    _appendFunction( new Func_IfNotLTY());
    // #define FUNC_IFNOTEQY           97
    _appendFunction( new Func_IfNotEQY());
    // #define FUNC_IFNOTGEY           98
    _appendFunction( new Func_IfNotGEY());
    // #define FUNC_IFNOTNEY           99
    _appendFunction( new Func_IfNotNEY());
    // #define FUNC_L0                 100
    _appendFunction( new Func_L0());
    // #define FUNC_L1                 101
    _appendFunction( new Func_L1());
    // #define FUNC_L2                 102
    _appendFunction( new Func_L2());
    // #define FUNC_L3                 103
    _appendFunction( new Func_L3());

    #ifdef __DEBUG
    Serial.print( _nfunctions);
    Serial.println(" functions defined:");
    for( int i=0; i<_nfunctions; i++){
        Serial.print(i);
        RPN_Function *funct = (RPN_Function *)_functions[i];
        if( funct->Name() == NULL){
            Serial.println( " - no name");
            continue;
        }
        Serial.print( " - [");
        sprintf_P( _text, funct->Name());
        Serial.print( _text);
        Serial.print( "] (");
        sprintf_P( _text, funct->IOName());
        Serial.print( _text);
        Serial.println( ")");
    }
    #endif
    return millis();
}

char *RPN_Functions::setOutputBuffer(char *text){
    strncpy( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH-1] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer(char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    strncpy( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH-1] = 0;
    return _text;
}

char *RPN_Functions::setOutputBuffer_P(const char *text){
    strncpy_P( _text, text, PROGRAM_LINE_LENGTH);
    _text[PROGRAM_LINE_LENGTH-1] = 0;
    return _text;
}

char *RPN_Functions::appendOutputBuffer_P(const char *text){
    int ln = strlen( _text);
    if( ln >= PROGRAM_LINE_LENGTH) return _text;
    strncpy_P( _text+ln, text, PROGRAM_LINE_LENGTH-ln);
    _text[PROGRAM_LINE_LENGTH-1] = 0;
    return _text;
}


RPN_Function *RPN_Functions::getFunctionByID(int16_t id){
    if( id<0) return NULL;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkID( id)) continue;
        return pf;
    }
    return NULL;
}

RPN_Function *RPN_Functions::getFunctionByName(char *command){
    if( strlen(command)<=0) return NULL;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( command)) continue;
        return pf;
    }
    return NULL;
}

RPN_Function *RPN_Functions::getFunctionByIOName(char *command){
    if( strlen(command)<=0) return NULL;
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !UniversalValue::_startsWith_P( command, pf->IOName())) continue;
        return pf;
    }
    return NULL;
}

void RPN_Functions::execute( int16_t id, char *command){
    RPN_Function *pf = getFunctionByID( id);
    if( pf==NULL) return;
    pf->execute( _components, command);
}

void RPN_Functions::execute( char *command, bool pushNeeded){
    if( strlen(command)<=0) return;
    Serial.println(command);
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( command)) continue;
        int operand = strlen_P( pf->Name());
        pf->execute( _components, command+operand);
        Serial.println(pf->advanceRequired());
        if( pf->advanceRequired()) progMem->incrementCounter();
        return;
    }
    // if the name is not found, it must be a number and should be placed to register X
    if( pushNeeded){
        rpnStack->storeBx();
        rpnStack->push();
    }
    rpnStack->X->fromString( command);
    progMem->incrementCounter(); // after number is entered, advance!
}

//
// Executes one step at project counter
//
void RPN_Functions::executeStep(){
    if(_atStop){
        if( progMem->isAtStop()) progMem->incrementCounter();
        _atStop = false;
    }
    executeRun();
    if( _atStop)
        rpnStack->setStackLabel_P(0, PSTR("STOP Reached"));
}

//
// Executes one step during the run
//
void RPN_Functions::executeRun(){
    char *programLine = progMem->getCurrentLine();
    #ifdef __DEBUG
    Serial.print( "Running: [");
    Serial.print( programLine);
    Serial.println( "]");
    #endif
    execute( programLine, true);
}

void RPN_Functions::_appendFunction( RPN_Function *f){
    if( _nfunctions >= MK52_NFUNCTIONS) return;
    _functions[ _nfunctions++] = f;
}

bool RPN_Functions::loadStateFile(){
    #ifdef __DEBUG
    Serial.println("Loading state file");
    #endif
    if( !_sd->openFile_P(StatusFile)) return true;
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
    rpnStack->Z->toString(_text+2);
    if(_sd->println(_text)) return true;
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
        _tmpuv->fromLocation( ptr);
        sprintf_P( _text, PSTR("M%04u: "), i);
        _tmpuv->toString(_text+7);
        if(!_sd->println(_text)) continue;
        return true;
    }
    return false;
}

bool RPN_Functions::_readFile(bool readStack, bool readProg, bool readMem){
    uint32_t pmemctr = progMem->getCounter();
    uint32_t ememctr = extMem->getCounter();
    char *ptr = NULL;
    while( true){
        if( _sd->readln( _text, PROGRAM_LINE_LENGTH)) break;
        if( _text[0] == 0 || _text[0] == '#') continue;
        if( readProg){
            Serial.print( "Prog: ");
            Serial.println( _text);
            if( UniversalValue::_startsWith_P( _text, PSTR("PC="))){
                execute( FUNC_GOTO, _text+3);
                pmemctr = extMem->getCounter();
                continue;
            }
            if( UniversalValue::_isProgramAddress(_text)){
                ptr = UniversalValue::_selectAddress(_text);
                while( *ptr==' ') ptr++;
                if( *ptr == 0) continue; // string too short or incorrectly formed
                execute( FUNC_GOTO, _text+1);
                progMem->replaceLine( ptr); // TODO: name conversion
                continue;
            }
        }
        if( readMem){
            if( UniversalValue::_startsWith_P( _text, PSTR("MC="))){
                execute( FUNC_GOMEM, _text+3);
                ememctr = extMem->getCounter();
                continue;
            }
            if( UniversalValue::_isMemoryAddress(_text)){
                ptr = UniversalValue::_selectAddress(_text);
                if( *ptr == 0) continue; // string too short or incorrectly formed
                execute( FUNC_GOMEM, _text+1);
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
                rpnStack->setDMode(1);
                continue;
            }
        }
    }
    progMem->setCounter( pmemctr);
    extMem->setCounter( ememctr);
    return false;
}

#include "../functions/Func_Divide.h"
#include "../functions/Func_Minus.h"
#include "../functions/Func_Multiply.h"
#include "../functions/Func_Negate.h"
#include "../functions/Func_Plus.h"
#include "../functions/Func_Trig.h"
#include "../functions/Func_Pow.h"
#include "../functions/Func_Log.h"
#include "../functions/Func_Rand.h"
#include "../functions/Func_Numb.h"
#include "../functions/Func_Logical.h"
#include "../functions/Func_Convert.h"
#include "../functions/Func_Memory.h"
#include "../functions/Func_Goto.h"
#include "../functions/Func_File.h"
#include "../functions/Func_If.h"
