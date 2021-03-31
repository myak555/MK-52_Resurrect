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

Receiver_CONFIRM::Receiver_CONFIRM(void *components[]) : Receiver::Receiver(components){
}

void Receiver_CONFIRM::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print("Activating CONFIRM: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print( prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate( prevReceiver);
    _lcd->outputTerminalLine(SCREEN_ROWS-2, _Question);
}

uint8_t Receiver_CONFIRM::tick( uint8_t scancode){
    switch( scancode){
        case 0:
            return 0;
        case 31:
            performAction();
            return _rpnf->requestNextReceiver(_return_to);
        case 33:
            _rpnf->requestNextReceiver(_return_to);
            return 33;
        default:
            break;
    }
    return _rpnf->requestNextReceiver(_return_to);
}

void Receiver_CONFIRM::performAction(){
}

//
// Confirms Extended Memory clear
//

Receiver_DATA_Erase::Receiver_DATA_Erase(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_DATA_Erase;
    strcpy_P( _Question, PSTR("Ext. memory erase? (\x18)"));
}

void Receiver_DATA_Erase::performAction(){
    _rpnf->extMem->clear();
    _return_to = _RECEIVER_DATA_N;
}

//
// Confirms Program Memory clear
//

Receiver_PROG_Erase::Receiver_PROG_Erase(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_PROG_Erase;
    strcpy_P( _Question, PSTR("Program erase? (\x18)"));
}

void Receiver_PROG_Erase::performAction(){
    _rpnf->progMem->clear();
    _return_to = _RECEIVER_PROG_N;
}

//
// Confirms file deletion
//

Receiver_FILE_Delete::Receiver_FILE_Delete(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_FILE_Delete;
    strcpy_P( _Question, PSTR("Delete? (\x18)"));
}

void Receiver_FILE_Delete::performAction(){
    _rpnf->execute(FUNC_REMOVE);
}

//
// Confirms Program overwrite
//

Receiver_FILE_Overwrite::Receiver_FILE_Overwrite(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_FILE_Overwrite;
    strcpy_P( _Question, PSTR("Overwrite program? (\x18)"));
}

void Receiver_FILE_Overwrite::performAction(){
    _rpnf->execute(FUNC_SAVE);
}

//
// Confirms All overwrite
//

Receiver_FILE_Overwrite_All::Receiver_FILE_Overwrite_All(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_FILE_Overwrite_All;
    strcpy_P( _Question, PSTR("Overwrite all? (\x18)"));
}

void Receiver_FILE_Overwrite_All::performAction(){
    _rpnf->execute(FUNC_SAVEALL);
}

//
// Confirms All overwrite
//

Receiver_FILE_Overwrite_Data::Receiver_FILE_Overwrite_Data(void *components[]) : Receiver_CONFIRM::Receiver_CONFIRM(components){
    Moniker = _RECEIVER_FILE_Overwrite_Data;
    strcpy_P( _Question, PSTR("Overwrite data? (\x18)"));
}

void Receiver_FILE_Overwrite_Data::performAction(){
    _rpnf->execute(FUNC_SAVEDATA);
}
