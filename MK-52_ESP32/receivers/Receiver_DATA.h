//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Parent receiver for DATA mode
//

Receiver_DATA::Receiver_DATA(void *components[]) : Receiver::Receiver(components){
}

void Receiver_DATA::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    long TargetTime = millis();
    Serial.print("Activating DATA: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print(prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate(prevReceiver);
    if( prevReceiver > N_DISPLAY_RECEIVERS || (_RECEIVER_DATA_N <= prevReceiver && prevReceiver <= _RECEIVER_DATA_A)){
        _lcd->updateStatusFMODE( _funlabel);
        tick(0);
        return;
    }
    char *buff = _rpnf->getOutputBuffer();
    Extended_Memory *em = _rpnf->extMem; 
    _lcd->dimScreen();
    _lcd->clearScreen( false);
    _lcd->outputStatus( _rpnf->progMem->getCounter(),
                        em->getCounter(),
                        "EXT", _funlabel);
    int32_t cnt = (int32_t)em->getCounter();
    for( int32_t i=10, j=cnt; i>=0; i--, j--){
        _lcd->outputTerminalLine( i, em->toString(buff, j));
    }
    _lcd->undimScreen();

    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print("Activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
}

uint8_t Receiver_DATA::tick( uint8_t scancode){
    unsigned long start = millis();
    Extended_Memory *em = _rpnf->extMem; 
    _lcd->updateStatusPC(_rpnf->progMem->getCounter());
    _lcd->updateStatusMC(em->getCounter());
    char *buff = _rpnf->getOutputBuffer();
    int32_t cnt = (int32_t)em->getCounter();
    for( int32_t i=10, j=cnt; i>=0; i--, j--){
        _lcd->updateTerminalLine( i, em->toString(buff, j));
        if( millis()-start > KBD_IDLE_DELAY) break; // we can do the rest of redraw later!
    }
    return 0;
}

//
// DATA Normal entry
//

Receiver_DATA_N::Receiver_DATA_N(void *components[]) : Receiver_DATA::Receiver_DATA(components){
    Moniker = _RECEIVER_DATA_N;
}

uint8_t Receiver_DATA_N::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            break;

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_A);
        case 4:
            // TODO: Data Insert mode
            //_rpnf->rpnStack->toggleAngleMode();
            // return Receiver_DATA::tick(0);
            return 0;

        // Column 1
        case 5:
            _rpnf->extMem->incrementCounter();
            break;
        case 6:
            _rpnf->extMem->decrementCounter();
            break;
        case 7:
            _rpnf->extMem->resetCounter();
            break;
        case 8:
            _rpnf->execute(FUNC_MEXTOX);
            _rpnf->extMem->incrementCounter();
            break;

        // Column 2
        case 9:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_ME);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_EM);
        case 11:
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS_MC, _RECEIVER_DATA_N);
        case 12:
            _rpnf->execute(FUNC_XTOMEX);
            _rpnf->extMem->incrementCounter();
            break;

        // Column 3-5 - number entry

        // Column 6
        case 25:
        case 26:
            break;
        case 27:
            _rpnf->execute(FUNC_MEMSWP);
            _rpnf->extMem->incrementCounter();
            break;

        // Column 7
        case 29:
        case 30:
            break;
        case 31:
            _rpnf->execute(FUNC_MEMSET,_rpnf->rpnStack->_DataEntry);
            _rpnf->extMem->incrementCounter();
            break;
        case 32:
            _rpnf->extMem->clearCurrent();
            _rpnf->extMem->incrementCounter();
            break;

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_OFF);
            return 33;

        default: // all other buttons activate number entry
            _rpnf->requestNextReceiver(_RECEIVER_NUMBER_DATA);
            return scancode;
    }
    return Receiver_DATA::tick(0);
}

//
// DATA F-mode entry
//

Receiver_DATA_F::Receiver_DATA_F(void *components[]) : Receiver_DATA::Receiver_DATA(components){
    Moniker = _RECEIVER_DATA_F;
    _funlabel[1] = 'F';
}

uint8_t Receiver_DATA_F::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_DATA::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_A);
        case 4:
            //_rpnf->rpnStack->toggleAngleMode();
            //return Receiver_DATA::tick(0);
            return 0;

        // Column 1
        case 5:
            for( int8_t i=0; i<9; i++)
                _rpnf->extMem->incrementCounter();
            break;
        case 6:
            for (int8_t i = 0; i < 9; i++)
                _rpnf->extMem->decrementCounter();
            break;
        //case 7:
        //    TODO: goto to the next entry
        //    break;
        // Column 2 does nothing (for now)
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
            _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
            return 33;

        default: // all other buttons do nothing, keeping F-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
}

//
// DATA K-mode entry
//

Receiver_DATA_K::Receiver_DATA_K(void *components[]) : Receiver_DATA::Receiver_DATA(components){
    Moniker = _RECEIVER_DATA_K;
    _funlabel[1] = 'K';
}

uint8_t Receiver_DATA_K::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_DATA::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_F);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_A);
        case 4:
            //_rpnf->rpnStack->toggleAngleMode();
            //    return Receiver_DATA::tick(0);
            return 0;

        // Column 1 does nothing (for now)
        // Column 2 does nothing (for now)
        // Column 3 does nothing (for now)
        // Column 4 does nothing (for now)
        // Column 5 does nothing (for now)
        // Column 6 does nothing (for now)

        // Column 7
        case 32:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_Erase);

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
            return 33;

        default: // all other buttons do nothing, keeping K-mode
            return 0;
    }
    //return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
}

//
// DATA A-mode entry
//

Receiver_DATA_A::Receiver_DATA_A(void *components[]) : Receiver_DATA::Receiver_DATA(components){
    Moniker = _RECEIVER_DATA_A;
    _funlabel[1] = 'A'; 
}

uint8_t Receiver_DATA_A::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return Receiver_DATA::tick(0); // redraw the rest of the screen if needed

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_K);
        case 4:
            //_rpnf->rpnStack->toggleAngleMode();
            // return Receiver_DATA::tick(0);
            return 0;

        // Column 1 does nothing (for now)
        // Column 2 does nothing (for now)
        // Column 3 does nothing (for now)
        // Column 4 does nothing (for now)

        // Column 5
        case 24:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);

        // Column 6 does nothing (for now)

        // Column 7
        case 32:
        case 33:
            _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
            return 33;
        default: // all other buttons do nothing, keeping A-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);
}
