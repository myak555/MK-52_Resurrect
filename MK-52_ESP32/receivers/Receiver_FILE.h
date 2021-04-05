//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Parent receiver for FILE mode
//

Receiver_FILE::Receiver_FILE(void *components[]) : Receiver::Receiver(components){
    _sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
}

void Receiver_FILE::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    long TargetTime = millis();
    Serial.print("Activating FILE: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print(prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate(prevReceiver);
    if( prevReceiver > N_DISPLAY_RECEIVERS || (_RECEIVER_FILE_N <= prevReceiver && prevReceiver <= _RECEIVER_FILE_A)){
        _lcd->updateStatusFMODE( _funlabel);
        tick(0);
        return;
    }
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    char **Lines = _rpnf->getOutputLines();
    _sd->getFolderListing( Lines, 11, SCREEN_COLS-1);
    _lcd->outputStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(), "DSK", _funlabel);
    for( int i=0; i<11; i++){
        _lcd->outputTerminalLine( i, Lines[i]);
    }
    _lcd->undimScreen();
    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print("Activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
}

uint8_t Receiver_FILE::tick( uint8_t scancode){
    unsigned long start = millis();
    char **Lines = _rpnf->getOutputLines();
    _sd->getFolderListing( Lines, 11, SCREEN_COLS-1);
    _lcd->updateStatus( _rpnf->progMem->getCounter(), _rpnf->extMem->getCounter(), "DSK", _funlabel);
    for( int i=0; i<11; i++){
        _lcd->updateTerminalLine( i, Lines[i]);
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return 0;
}

//
// FILE Normal entry
//

Receiver_FILE_N::Receiver_FILE_N(void *components[]) : Receiver_FILE::Receiver_FILE(components){
    Moniker = _RECEIVER_FILE_N;
}

uint8_t Receiver_FILE_N::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_FILE::tick(0);

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_A);

        // Column 1
        case 5:
            _rpnf->_sd->nextListingPosition();
            break;
        case 6:
            _rpnf->_sd->previousListingPosition();
            break;
        case 7:
            _rpnf->_sd->upFolder();
            break;
        case 8:
            _rpnf->execute(FUNC_STEPIN);
            break;

        // Column 2
        case 9:
            _rpnf->execute(FUNC_LOAD);
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Overwrite);
        case 11:
            // find program TODO
            break;
        case 12:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Name);

        // Column 3-5 - do nothing (for now)

        // Column 6
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_MkDir);

        // Column 7
        case 31:
            _rpnf->execute(FUNC_STEPIN);
            break;
        case 32:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Delete);

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_OFF);
            return 33;

        default: // all other buttons do nothing (for now)
            return 0;
    }
    return Receiver_FILE::tick(0);
}

//
// FILE F-mode entry
//

Receiver_FILE_F::Receiver_FILE_F(void *components[]) : Receiver_FILE::Receiver_FILE(components){
    Moniker = _RECEIVER_FILE_F;
    _funlabel[1] = 'F';
}

uint8_t Receiver_FILE_F::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_FILE::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_A);

        // Column 1
        case 5:
            for (int i = 0; i < 9; i++)
                _rpnf->_sd->nextListingPosition();
            break;
        case 6:
            for (int i = 0; i < 9; i++)
                _rpnf->_sd->previousListingPosition();
            break;

        // Column 2
        case 9:
            _rpnf->execute(FUNC_LOADDATA);
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Overwrite_Data);
        case 12:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Data);

        // Column 3 does nothing (for now)
        // Column 4 does nothing (for now)

        // Column 5
        case 24:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);

        // Column 6
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);

        // Column 7
        case 32:
            // Clear F mode
            break;

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
            return 33;

        default: // all other buttons do nothing, keeping F-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
}

//
// FILE K-mode entry
//

Receiver_FILE_K::Receiver_FILE_K(void *components[]) : Receiver_FILE::Receiver_FILE(components){
    Moniker = _RECEIVER_FILE_K;
    _funlabel[1] = 'K';
}

uint8_t Receiver_FILE_K::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_FILE::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_F);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_A);

        // Column 1 does nothing (for now)

        // Column 2
        case 9:
            _rpnf->execute(FUNC_LOADALL);
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_Overwrite_All);
        case 12:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_All);

        // Column 3 does nothing (for now)
        // Column 4 does nothing (for now)
        // Column 5 does nothing (for now)
        // Column 6
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_Erase);

        // Column 7
        case 32:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_Erase);

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
            return 33;

        default: // all other buttons do nothing, keeping K-mode
            return 0;
    }
    //return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
}

//
// FILE A-mode entry
//

Receiver_FILE_A::Receiver_FILE_A(void *components[]) : Receiver_FILE::Receiver_FILE(components){
    Moniker = _RECEIVER_FILE_A;
    _funlabel[1] = 'A'; 
}

uint8_t Receiver_FILE_A::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_FILE::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_K);

        // Column 1 does nothing (for now)
        // Column 2 does nothing (for now)
        // Column 3 does nothing (for now)
        // Column 4 does nothing (for now)
        // Column 5 does nothing (for now)

        // Column 6
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);

        // Column 7
        case 32:
        case 33:
            _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
            return 33;
        default: // all other buttons do nothing, keeping A-mode
            return 0;
    }
    //return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);
}
