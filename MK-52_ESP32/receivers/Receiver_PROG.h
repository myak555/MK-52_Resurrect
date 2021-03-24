//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Parent receiver for PROG mode
//

Receiver_PROG::Receiver_PROG(void *components[]) : Receiver::Receiver(components){
}

void Receiver_PROG::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    long TargetTime = millis();
    Serial.print("Activating PROG: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print(prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate(prevReceiver);
    if( prevReceiver > N_DISPLAY_RECEIVERS || (_RECEIVER_PROG_N <= prevReceiver && prevReceiver <= _RECEIVER_PROG_A)){
        _lcd->updateStatusFMODE( _funlabel);
        tick(0);
        return;
    }
    char *buff = _rpnf->getOutputBuffer();
    Program_Memory *pm = _rpnf->progMem; 
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( pm->getCounter(), _rpnf->extMem->getCounter(), pm->getEModeName(), _funlabel);
    int32_t display_PC = (int32_t)pm->getCounter();
    pm->getPreviousLines(_displayLines, SCREEN_ROWS-1);
    for( int i=10, j=0; i>=0; i--, j++)
        _lcd->outputTerminalLine( i, _getTerminalLine( buff, display_PC--, _displayLines[j]));
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print("Activated in ");
    Serial.print ( TargetTime);
    Serial.print("PC = ");
    Serial.print ( pm->getCounter());
    Serial.println (" ms");
    #endif
}

uint8_t Receiver_PROG::tick( uint8_t scancode){
    unsigned long start = millis();
    Program_Memory *pm = _rpnf->progMem; 
    _lcd->updateStatusPC(pm->getCounter());
    _lcd->updateStatusMC(_rpnf->extMem->getCounter());
    char *buff = _rpnf->getOutputBuffer();
    int32_t cnt = (int32_t)pm->getCounter();
    pm->getPreviousLines(_displayLines, SCREEN_ROWS-1);
    int8_t lineNumber = 0;
    for( int8_t i=10; i>=0; i--){
        _lcd->updateTerminalLine( i, _getTerminalLine( buff, cnt--, _displayLines[lineNumber++]));
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return 0;
}

char *Receiver_PROG::_getTerminalLine( char *buff, int32_t lineNumber, char *text){
    memset( buff, 0, SCREEN_COLS+1);
    if( lineNumber < 0) return buff;
    uint32_t lNum = (uint32_t)lineNumber;
    snprintf_P( buff, 5, PSTR("%04u"), lNum);
    buff[4] = (lNum == _rpnf->progMem->getCounter())? '>': ' ';
    buff[5] = ' ';
    buff[6] = 0;
    int limit = SCREEN_COLS-6;
    if( text == NULL) return buff;
    snprintf_P( buff+6, limit, PSTR("%s"), text);
    return buff;
}

//
// PROG Normal entry
//

Receiver_PROG_N::Receiver_PROG_N(void *components[]) : Receiver_PROG::Receiver_PROG(components){
    Moniker = _RECEIVER_PROG_N;
}

uint8_t Receiver_PROG_N::tick( uint8_t scancode){
    switch (scancode)
    {
        case 0: // keyboard inactive
            return Receiver_PROG::tick(0);

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_A);
        case 4:
            _rpnf->progMem->toggleEditMode();
            return Receiver_PROG::tick(0);

        // Column 1
        case 5:
            // increment by itself!
            break;
        case 6:
            _rpnf->execute(FUNC_DECREMENT_PC);
            return Receiver_PROG::tick(0);
        case 7:
            _rpnf->appendProgramLine_P(FUNC_RETURN);
            break;
        case 8:
            _rpnf->appendProgramLine_P(FUNC_STOP);
            break;

        // Column 2
        case 9:
            _rpnf->appendProgramLine_P(FUNC_M2X);
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER);
        case 10:
            _rpnf->appendProgramLine_P(FUNC_X2M);
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER);
        case 11:
            _rpnf->appendProgramLine_P(FUNC_GOTO);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS);
        case 12:
            _rpnf->appendProgramLine_P(FUNC_GOSUB);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS);

        // Column 5
        case 24:
            _rpnf->appendProgramLine_P(FUNC_NEGATE);
            break;

        // Column 6
        case 25:
            _rpnf->appendProgramLine_P(FUNC_MINUS);
            break;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_PLUS);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_SWAP);
            break;

        // Column 7
        case 29:
            _rpnf->appendProgramLine_P(FUNC_DIVIDE);
            break;
        case 30:
            _rpnf->appendProgramLine_P(FUNC_MULTIPLY);
            break;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_ENTER);
            break;
        case 32:
            _rpnf->appendProgramLine_P(FUNC_CLEAR_X);
            break;
        case 33:
            return _rpnf->requestNextReceiver(_RECEIVER_OFF);

        default: // all other buttons activate number entry
            _rpnf->requestNextReceiver(_RECEIVER_NUMBER_PROG);
            return scancode;
    }
    _rpnf->execute(FUNC_INCREMENT_PC);
    return Receiver_PROG::tick(0);
}

//
// PROG F-mode entry
//

Receiver_PROG_F::Receiver_PROG_F(void *components[]) : Receiver_PROG::Receiver_PROG(components){
    Moniker = _RECEIVER_PROG_F;
    _funlabel[1] = 'F';
}

uint8_t Receiver_PROG_F::tick( uint8_t scancode){
    switch (scancode)
    {
        case 0: // keyboard inactive
            return Receiver_PROG::tick(0);

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_A);
        case 4:
            _rpnf->appendProgramLine_P(FUNC_SET_DMOD_DEG);
            break;

        // Column 1
        case 5:
            _rpnf->appendProgramLine_P(FUNC_IFNOTLT0);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 6:
            _rpnf->appendProgramLine_P(FUNC_IFNOTEQ0);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 7:
            _rpnf->appendProgramLine_P(FUNC_IFNOTGE0);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 8:
            _rpnf->appendProgramLine_P(FUNC_IFNOTNE0);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);

        // Column 2 does nothing (for now)
        case 9:
            _rpnf->appendProgramLine_P(FUNC_L0);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 10:
            _rpnf->appendProgramLine_P(FUNC_L1);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 11:
            _rpnf->appendProgramLine_P(FUNC_L2);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 12:
            _rpnf->appendProgramLine_P(FUNC_L3);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);

        // Column 3
        case 13:
            _rpnf->appendProgramLine_P(FUNC_SIN);
            break;
        case 14:
            _rpnf->appendProgramLine_P(FUNC_ARCSIN);
            break;
        case 15:
            _rpnf->appendProgramLine_P(FUNC_EXP);
            break;
        case 16:
            _rpnf->appendProgramLine_P(FUNC_10X);
            break;

        // Column 4
        case 17:
            _rpnf->appendProgramLine_P(FUNC_COS);
            break;
        case 18:
            _rpnf->appendProgramLine_P(FUNC_ARCCOS);
            break;
        case 19:
            _rpnf->appendProgramLine_P(FUNC_LG);
            break;
        case 20:
            _rpnf->appendProgramLine_P(FUNC_ROT);
            break;

        // Column 5
        case 21:
            _rpnf->appendProgramLine_P(FUNC_TG);
            break;
        case 22:
            _rpnf->appendProgramLine_P(FUNC_ARCTG);
            break;
        case 23:
            _rpnf->appendProgramLine_P(FUNC_LN);
            break;
        case 24:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);

        // Column 6
        case 25:
            _rpnf->appendProgramLine_P(FUNC_SQRT);
            break;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_PI);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_POW);
            break;
        case 28:
            // PROG is already on
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);

        // Column 7
        case 29:
            _rpnf->appendProgramLine_P(FUNC_1X);
            break;
        case 30:
            _rpnf->appendProgramLine_P(FUNC_X2);
            break;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_BX);
            break;
        case 32:
            // Clear F mode
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
            return 33;
        default: // all other buttons do nothing, keeping F-mode
            return 0;
    }
    _rpnf->execute(FUNC_INCREMENT_PC);
    return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
}

//
// PROG K-mode entry
//

Receiver_PROG_K::Receiver_PROG_K(void *components[]) : Receiver_PROG::Receiver_PROG(components){
    Moniker = _RECEIVER_PROG_K;
    _funlabel[1] = 'K';
}

uint8_t Receiver_PROG_K::tick( uint8_t scancode){
    Program_Memory *pm = _rpnf->progMem;
    switch (scancode)
    {
        case 0: // keyboard inactive
            return Receiver_PROG::tick(0);

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_F);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_A);
        case 4:
            _rpnf->appendProgramLine_P(FUNC_SET_DMOD_RAD);
            break;

        // Column 1
        case 5:
            _rpnf->appendProgramLine_P(FUNC_IFNOTLTY);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 6:
            _rpnf->appendProgramLine_P(FUNC_IFNOTEQY);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 7:
            _rpnf->appendProgramLine_P(FUNC_IFNOTGEY);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 8:
            _rpnf->appendProgramLine_P(FUNC_IFNOTNEY);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);

        // Column 2
        case 9:
            _rpnf->appendProgramLine_P(FUNC_K_M2X);
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER, _RECEIVER_PROG_N);
        case 10:
            _rpnf->appendProgramLine_P(FUNC_K_X2M);
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER, _RECEIVER_PROG_N);
        case 11:
            pm->updateLine_P("# K-GOTO is bad!");
            break;
        case 12:
            pm->updateLine_P("# K-GOSUB is bad!");
            break;

        // Column 3
        case 13:
            _rpnf->appendProgramLine_P(FUNC_WHOLE);
            break;
        case 14:
            _rpnf->appendProgramLine_P(FUNC_ABS);
            break;
        case 15:
            _rpnf->appendProgramLine_P(FUNC_EE);
            break;
        case 16:
            pm->commentLine();
            break;

        // Column 4
        case 17:
            _rpnf->appendProgramLine_P(FUNC_FRAC);
            break;
        case 18:
            _rpnf->appendProgramLine_P(FUNC_SIGN);
            break;
        case 19:
            _rpnf->appendProgramLine_P(FUNC_LOG);
            break;
        case 20:
            _rpnf->appendProgramLine_P(FUNC_AND);
            break;

        // Column 5
        case 21:
            _rpnf->appendProgramLine_P(FUNC_MAX);
            break;
        case 22:
            _rpnf->appendProgramLine_P(FUNC_DM2D);
            break;
        case 23:
            _rpnf->appendProgramLine_P(FUNC_DMS2D);
            break;
        case 24:
            _rpnf->appendProgramLine_P(FUNC_OR);
            break;

        // Column 6
        case 25:
            // TODO
            pm->updateLine_P("#K-SQRT");
            break;
        case 26:
            _rpnf->appendProgramLine_P(FUNC_D2DM);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_D2DMS);
            break;
        case 28:
            _rpnf->appendProgramLine_P(FUNC_XOR);
            break;

        // Column 7
        case 29:
            // TODO
            pm->updateLine_P("#K-1/X");
            break;
        case 30:
            // TODO
            pm->updateLine_P("#K-X^2");
            break;
        case 31:
            _rpnf->appendProgramLine_P(FUNC_RAND);
            break;
        case 32:
            _rpnf->appendProgramLine_P(FUNC_NOT);
            break;

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
            return 33;
        default: // all other buttons do nothing, keeping K-mode
            return 0;
    }
    _rpnf->execute(FUNC_INCREMENT_PC);
    return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
}

//
// PROG A-mode entry
//

Receiver_PROG_A::Receiver_PROG_A(void *components[]) : Receiver_PROG::Receiver_PROG(components){
    Moniker = _RECEIVER_PROG_A;
    _funlabel[1] = 'A'; 
}

uint8_t Receiver_PROG_A::tick( uint8_t scancode){
    Program_Memory *pm = _rpnf->progMem;
    switch (scancode)
    {
        case 0: // keyboard inactive
            return Receiver_PROG::tick(0);

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_K);
        case 4:
            _rpnf->appendProgramLine_P(FUNC_SET_DMOD_GRD);
            break;

        // Column 1
        case 5:
            _rpnf->appendProgramLine_P(FUNC_LBT);
            return _rpnf->requestNextReceiver(_RECEIVER_TEXT, _RECEIVER_PROG_N);
        case 6:
            _rpnf->appendProgramLine_P(FUNC_LBZ);
            return _rpnf->requestNextReceiver(_RECEIVER_TEXT, _RECEIVER_PROG_N);
        case 7:
            _rpnf->appendProgramLine_P(FUNC_LBY);
            return _rpnf->requestNextReceiver(_RECEIVER_TEXT, _RECEIVER_PROG_N);
        case 8:
            _rpnf->appendProgramLine_P(FUNC_LBX);
            return _rpnf->requestNextReceiver(_RECEIVER_TEXT, _RECEIVER_PROG_N);

        // Column 2
        case 9:
            _rpnf->appendProgramLine_P(FUNC_A_M2X);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 10:
            _rpnf->appendProgramLine_P(FUNC_A_X2M);
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS, _RECEIVER_PROG_N);
        case 11:
            _rpnf->appendProgramLine_P(FUNC_LBR);
            break;
        case 12:
            pm->deleteLine();
            break;

        // Column 3
        case 16:
            pm->commentLine();
            return _rpnf->requestNextReceiver(_RECEIVER_TEXT, _RECEIVER_PROG_N);

        // Column 5
        case 22:
            _rpnf->appendProgramLine_P(FUNC_D2RAD);
            break;
        case 23:
            _rpnf->appendProgramLine_P(FUNC_MM2IN);
            break;
        case 24:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);

        // Column 6
        case 26:
            _rpnf->appendProgramLine_P(FUNC_RAD2D);
            break;
        case 27:
            _rpnf->appendProgramLine_P(FUNC_IN2MM);
            break;
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);

        // Column 7
        case 31:
            _rpnf->appendProgramLine_P(FUNC_SEED);
            break;
        case 32:
        case 33:
            _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
            return 33;
        default: // all other buttons do nothing, keeping A-mode
            return 0;
    }
    _rpnf->execute(FUNC_INCREMENT_PC);
    return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
}
