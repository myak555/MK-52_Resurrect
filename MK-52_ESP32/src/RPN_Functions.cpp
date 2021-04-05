//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "RPN_Functions.hpp"

//#define __DEBUG
//#define __DEBUG_PRINT_FUNCTIONS
using namespace MK52_Interpreter;

#include <math.h>
#include "../functions/functions.hpp"

//
// Inits the calculator program memory
//
void RPN_Functions::init( void *components[]) {
    #ifdef __DEBUG
    Serial.println( "Init Functions");
    #endif
    
    _components = components;
    rpnStack = (RPN_Stack*) components[COMPONENT_STACK];
    regMem = (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];
    progMem = (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];
    extMem = (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];
    _sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];

    _buffer = (char *)malloc( SCREEN_BUFFER_SIZE);
    _text = (char*)malloc( PROGRAM_LINE_LENGTH + 10);
    memset( _buffer, 0, SCREEN_BUFFER_SIZE);
    memset( _text, 0, PROGRAM_LINE_LENGTH + 10);
    char *ptr = _buffer;
    for( uint8_t i=0; i<SCREEN_ROWS; i++){
        _lines[i] = ptr;
        ptr += SCREEN_COLS + 1;
    }
    _tmpuv = new UniversalValue( (uint8_t *)(_text + PROGRAM_LINE_LENGTH+1));
    
    // first check for empty program line
    _appendFunction( new Func_Empty());
    // #define FUNC_COMMENT            1
    _appendFunction( new Func_Comment());
    // #define FUNC_DMOD_DEG       9
    _appendFunction( new Func_DMOD_DEG());
    // #define FUNC_DMOD_RAD       10
    _appendFunction( new Func_DMOD_RAD());
    // #define FUNC_DMOD_GRD       11
    _appendFunction( new Func_DMOD_GRD());
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
    // #define FUNC_POWYX              30a
    _appendFunction( new Func_PowYX());
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
    // #define FUNC_STOP               75
    _appendFunction( new Func_Stop());
    // #define FUNC_MKDIR              76
    _appendFunction( new Func_MkDir());
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
    // #define FUNC_LBX                104
    _appendFunction( new Func_LBX());
    // #define FUNC_LBY                105
    _appendFunction( new Func_LBY());
    // #define FUNC_LBZ                106
    _appendFunction( new Func_LBZ());
    // #define FUNC_LBT                107
    _appendFunction( new Func_LBT());
    // #define FUNC_LBR                108
    _appendFunction(new Func_LBR());
    // #define FUNC_SAVEALL            109
    _appendFunction(new Func_SaveAll());
    // #define FUNC_SAVEALLAS          110
    _appendFunction(new Func_SaveAllAs());
    // #define FUNC_LOADALL            111
    _appendFunction(new Func_LoadAll());
    // #define FUNC_LOADALLFROM        112
    _appendFunction(new Func_LoadAllFrom());

    // if the name is not found, it must be a number and should be placed to register X
    _appendFunction( new Func_Number());

    #ifdef __DEBUG_PRINT_FUNCTIONS
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

void RPN_Functions::execute( char *command){
    #ifdef __DEBUG
    Serial.print( "Execute: [");
    Serial.print( command);
    Serial.println( "]");
    #endif
    for(int16_t i=0; i<_nfunctions; i++){
        RPN_Function *pf = (RPN_Function *)_functions[i];
        if( !pf->checkName( command)) continue;
        int operand = strlen_P( pf->Name());
        pf->execute( _components, command+operand);
        pf->advancePC( _components);
        return;
    }
    rpnStack->setLabel(0, command);
    progMem->incrementCounter();
}

// 
// Resets the stop marker
// Returns true if the condition has been cleared
//
bool RPN_Functions::clearStopCondition()
{
    if (!_atStop) return false;
    if (progMem->isAtStop()) progMem->incrementCounter();
    _atStop = false;
    return true;
}

//
// Some original MK-52 programs used PP for data entry;
// must simulate the same, although not obvious for debugging.
// the commented line is to revert to the new logic
//
void RPN_Functions::executeStep(){
    // if( clearStopCondition()) return; // just move to the next line
    //clearStopCondition();
    //executeRun();
    //if (_atStop && progMem->isAtStop()) 
    //    rpnStack->setStackLabel_P(0, PSTR("STOP Reached"));
    _atStop = false;
    if (progMem->isAtStop()){
        rpnStack->setLabel_P(0, PSTR("STOP Reached"));
        progMem->incrementCounter();
        return;
    }
    executeRun();
}

//
// Executes one step during the run
//
void RPN_Functions::executeRun(){
    char *programLine = progMem->getCurrentLine();
    execute( programLine);
    if( progMem->isAtEnd()) _atStop = true;
}

void RPN_Functions::_appendFunction( RPN_Function *f){
    if( _nfunctions >= MK52_NFUNCTIONS) return;
    _functions[ _nfunctions++] = f;
}

#include "../functions/Func_Arithmetic.h"
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