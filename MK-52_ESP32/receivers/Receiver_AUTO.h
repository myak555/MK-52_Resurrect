//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Parent receiver for AUTO mode
//

Receiver_AUTO::Receiver_AUTO(void *components[]) : Receiver::Receiver(components){
}

void Receiver_AUTO::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    long TargetTime = millis();
    Serial.print("Activating AUTO: ");
    Serial.print( Moniker);
    Serial.print(" [");
    Serial.print(prevReceiver);
    Serial.println("]");
    #endif
    Receiver::activate(prevReceiver);
    if( prevReceiver > N_DISPLAY_RECEIVERS || (_RECEIVER_AUTO_N <= prevReceiver && prevReceiver <= _RECEIVER_AUTO_R)){
        _lcd->updateStatusFMODE( _funlabel);
        tick(0);
        return;
    }
    char *text = _rpnf->getOutputBuffer();
    RPN_Stack *st = _rpnf->rpnStack;
    _lcd->dimScreen();
    _lcd->clearScreen(false);
    _lcd->outputStatus( _rpnf->progMem->getCounter(),
                        _rpnf->extMem->getCounter(),
                        st->getDModeName(),
                        _funlabel); 
    _lcd->outputCalcRegister(0, st->X->toString(text));
    _lcd->outputCalcLabel(0, st->X_Label);
    _lcd->outputCalcRegister(1, st->Y->toString(text));
    _lcd->outputCalcLabel(1, st->Y_Label);
    _lcd->outputCalcRegister(2, st->Z->toString(text));
    _lcd->outputCalcLabel(2, st->Z_Label);
    _lcd->outputCalcRegister(3, st->T->toString(text));
    _lcd->outputCalcLabel(3, st->T_Label);
    _lcd->undimScreen();

    #ifdef __DEBUG
    TargetTime = millis() - TargetTime;
    Serial.print("Activated in ");
    Serial.print ( TargetTime);
    Serial.println (" ms");
    #endif
}

uint8_t Receiver_AUTO::tick( uint8_t scancode){
    char *text = _rpnf->getOutputBuffer();
    RPN_Stack *st = _rpnf->rpnStack;
    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
    _lcd->updateStatusMC( _rpnf->extMem->getCounter());
    _lcd->updateStatusDMODE( st->getDModeName());
    _lcd->updateCalcRegister(0, st->X->toString(text));
    _lcd->updateCalcLabel(0, st->X_Label);
    _lcd->updateCalcRegister(1, st->Y->toString(text));
    _lcd->updateCalcLabel(1, st->Y_Label);
    _lcd->updateCalcRegister(2, st->Z->toString(text));
    _lcd->updateCalcLabel(2, st->Z_Label);
    _lcd->updateCalcRegister(3, st->T->toString(text));
    _lcd->updateCalcLabel(3, st->T_Label);
    return 0;
}

//
// AUTO Normal entry
//

Receiver_AUTO_N::Receiver_AUTO_N(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_N;
}

uint8_t Receiver_AUTO_N::tick( uint8_t scancode){
    RPN_Stack *st = _rpnf->rpnStack;
    switch( scancode){
        case 0: // keyboard inactive
            return Receiver_AUTO::tick(0);

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_F);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_K);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_A);
        case 4:
            st->toggleAngleMode();
            break;

        // Column 1
        case 5:
            _rpnf->progMem->incrementCounter();
            break;
        case 6:
            _rpnf->progMem->decrementCounter();
            break;
        case 7:
            _rpnf->progMem->resetCounter();
            break;
        case 8:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_R);

        // Column 2
        case 9:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_MX);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_XM);
        case 11:
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS_PC);
        case 12:
            _rpnf->executeStep();
            break;

        // Column 5
        case 24:
            _rpnf->execute(FUNC_NEGATE);
            break;

        // Column 6
        case 25:
            _rpnf->execute(FUNC_MINUS);
            break;
        case 26:
            _rpnf->execute(FUNC_PLUS);
            break;
        case 27:
            _rpnf->execute(FUNC_SWAP);
            break;

        // Column 7
        case 29:
            _rpnf->execute(FUNC_DIVIDE);
            break;
        case 30:
            _rpnf->execute(FUNC_MULTIPLY);
            break;
        case 31:
            _rpnf->execute(FUNC_ENTER);
            break;
        case 32:
            if (st->customLabels()) st->resetLabels();
            else _rpnf->execute(FUNC_CLEAR_X);
            break;
        case 33:
            return _rpnf->requestNextReceiver(_RECEIVER_OFF);

        default: // all other buttons activate number entry
            _rpnf->execute(FUNC_ENTER);
            Receiver_AUTO::tick(0); // redraw stack movement
            _rpnf->requestNextReceiver(_RECEIVER_NUMBER);
            return scancode;
    }
    return Receiver_AUTO::tick(0);
}

//
// AUTO F-mode entry
//

Receiver_AUTO_F::Receiver_AUTO_F(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_F;
    _funlabel[1] = 'F';
}

uint8_t Receiver_AUTO_F::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return 0;

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_FK);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_FA);
        case 4:
            _rpnf->rpnStack->toggleAngleMode();
            return Receiver_AUTO::tick(0);

        // Column 1 does nothing (for now)
        case 5:
        case 6:
        case 7:
        case 8:

        // Column 2 does nothing (for now)
        case 9:
        case 10:
        case 11:
        case 12:
            return 0;

        // Column 3
        case 13:
            _rpnf->execute(FUNC_SIN);
            break;
        case 14:
            _rpnf->execute(FUNC_ARCSIN);
            break;
        case 15:
            _rpnf->execute(FUNC_EXP);
            break;
        case 16:
            _rpnf->execute(FUNC_10X);
            break;

        // Column 4
        case 17:
            _rpnf->execute(FUNC_COS);
            break;
        case 18:
            _rpnf->execute(FUNC_ARCCOS);
            break;
        case 19:
            _rpnf->execute(FUNC_LG);
            break;
        case 20:
            _rpnf->execute(FUNC_ROT);
            break;

        // Column 5
        case 21:
            _rpnf->execute(FUNC_TG);
            break;
        case 22:
            _rpnf->execute(FUNC_ARCTG);
            break;
        case 23:
            _rpnf->execute(FUNC_LN);
            break;
        case 24:
            // AUTO is already on
            break;

        // Column 6
        case 25:
            _rpnf->execute(FUNC_SQRT);
            break;
        case 26:
            _rpnf->execute(FUNC_PI);
            break;
        case 27:
            _rpnf->execute(FUNC_POW);
            break;
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_PROG_N);

        // Column 7
        case 29:
            _rpnf->execute(FUNC_1X);
            break;
        case 30:
            _rpnf->execute(FUNC_X2);
            break;
        case 31:
            _rpnf->execute(FUNC_BX);
            break;
        case 32:
            // Clear F mode
            break;
        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
            return 33;
        default: // all other buttons do nothing, keeping F-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}

//
// AUTO K-mode entry
//

Receiver_AUTO_K::Receiver_AUTO_K(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_K;
    _funlabel[1] = 'K';
}

uint8_t Receiver_AUTO_K::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return 0;

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_FK);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_A);
        case 4:
            _rpnf->rpnStack->toggleAngleMode();
            return Receiver_AUTO::tick(0);

        // Column 1 does nothing (for now)
        case 5:
        case 6:
        case 7:
        case 8:
            return 0;

        // Column 2
        case 9:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_KMX);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_REGISTER_KXM);
        case 11:
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-GOTO is bad for you!"));
            break;
        case 12:
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-GOSUB is bad for you!"));
            break;

        // Column 3
        case 13:
            _rpnf->execute(FUNC_WHOLE);
            break;
        case 14:
            _rpnf->execute(FUNC_ABS);
            break;
        case 15:
            _rpnf->execute(FUNC_EE);
            break;
        case 16:
            // NOP
            break;

        // Column 4
        case 17:
            _rpnf->execute(FUNC_FRAC);
            break;
        case 18:
            _rpnf->execute(FUNC_SIGN);
            break;
        case 19:
            _rpnf->execute(FUNC_LOG);
            break;
        case 20:
            _rpnf->execute(FUNC_AND);
            break;

        // Column 5
        case 21:
            _rpnf->execute(FUNC_MAX);
            break;
        case 22:
            _rpnf->execute(FUNC_DM2D);
            break;
        case 23:
            _rpnf->execute(FUNC_DMS2D);
            break;
        case 24:
            _rpnf->execute(FUNC_OR);
            break;

        // Column 6
        case 25:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-SQRT is available!"));
            break;
        case 26:
            _rpnf->execute(FUNC_D2DM);
            break;
        case 27:
            _rpnf->execute(FUNC_D2DMS);
            break;
        case 28:
            _rpnf->execute(FUNC_XOR);
            break;

        // Column 7
        case 29:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-1/X is available!"));
            break;
        case 30:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("K-X2 is available!"));
            break;
        case 31:
            _rpnf->execute(FUNC_RAND);
            break;
        case 32:
            _rpnf->execute(FUNC_NOT);
            break;

        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
            return 33;
        default: // all other buttons do nothing, keeping K-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}

//
// AUTO FK-mode entry
//

Receiver_AUTO_FK::Receiver_AUTO_FK(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_FK;
    _funlabel[0] = 'F';
    _funlabel[1] = 'K';
}

uint8_t Receiver_AUTO_FK::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return 0;

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_F);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_A);
        case 4:
            _rpnf->rpnStack->toggleAngleMode();
            return Receiver_AUTO::tick(0);

        // Column 6
        case 27:
            _rpnf->execute(FUNC_POWYX);
            break;

        // Column 7
        case 32:
            // Clear F mode
            break;
        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
            return 33;
        default: // all other buttons do nothing, keeping FK-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}

//
// AUTO A-mode entry
//

Receiver_AUTO_A::Receiver_AUTO_A(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_A;
    _funlabel[1] = 'A'; 
}

uint8_t Receiver_AUTO_A::tick( uint8_t scancode){
    switch (scancode)
    {
        case 0: // keyboard inactive
            return 0;

        // Column 0
        case 1:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_FA);
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_K);
        case 4:
            _rpnf->rpnStack->toggleAngleMode();
            return Receiver_AUTO::tick(0);

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
            return 0;

        // Column 2
        case 9:
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS_AMX);
        case 10:
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS_AXM);
        case 11:
            return _rpnf->requestNextReceiver(_RECEIVER_ADDRESS_MC, _RECEIVER_AUTO_N);
        case 12:
            _rpnf->execute(FUNC_A_M2X);
            _rpnf->extMem->incrementCounter();
            break;

        // Column 3 does nothing
        // Column 4 does nothing

        // Column 5
        case 22:
            _rpnf->execute(FUNC_D2RAD);
            break;
        case 23:
            _rpnf->execute(FUNC_MM2IN);
            break;
        case 24:
            return _rpnf->requestNextReceiver(_RECEIVER_FILE_N);

        // Column 6
        case 25:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("A-SQRT is available!"));
            break;
        case 26:
            _rpnf->execute(FUNC_RAD2D);
            break;
        case 27:
            _rpnf->execute(FUNC_IN2MM);
            break;
        case 28:
            return _rpnf->requestNextReceiver(_RECEIVER_DATA_N);

        // Column 7
        case 29:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("A-1/X is available!"));
            break;
        case 30:
            // TODO
            _rpnf->rpnStack->setLabel_P(0, PSTR("A-X2 is available!"));
            break;
        case 31:
            _rpnf->execute(FUNC_SEED);
            break;
        case 32:
        case 33:
            _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
            return 33;
        default: // all other buttons do nothing, keeping A-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}

//
// AUTO FK-mode entry
//

Receiver_AUTO_FA::Receiver_AUTO_FA(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_FA;
    _funlabel[0] = 'F';
    _funlabel[1] = 'A';
}

uint8_t Receiver_AUTO_FA::tick( uint8_t scancode){
    switch (scancode){
        case 0: // keyboard inactive
            return 0;

        // Column 0
        case 2:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_F);
        case 3:
            return _rpnf->requestNextReceiver(_RECEIVER_AUTO_A);
        case 4:
            _rpnf->rpnStack->toggleAngleMode();
            return Receiver_AUTO::tick(0);

        // Column 7
        case 32:
            // Clear F mode
            break;
        case 33:
            // Shutdown signal
            _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
            return 33;
        default: // all other buttons do nothing, keeping FK-mode
            return 0;
    }
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}

//
// AUTO Running program
//

Receiver_AUTO_R::Receiver_AUTO_R(void *components[]) : Receiver_AUTO::Receiver_AUTO(components){
    Moniker = _RECEIVER_AUTO_R;
    strcpy_P( _funlabel, PSTR("RUN"));
}

void Receiver_AUTO_R::activate( int8_t prevReceiver){
    #ifdef __DEBUG
    Serial.print(_funlabel);
    Serial.println("!");
    #endif
    _rpnf->_atStop = false;
    _lcd->updateStatusFMODE( _funlabel);
    if( _rpnf->progMem->isAtStop())
        _rpnf->progMem->incrementCounter();
}

uint8_t Receiver_AUTO_R::tick( uint8_t scancode){
    while( true){
        bool update_required = (millis() - _kbd->lastScanTime) > KBD_RUNNING_DELAY;
        _rpnf->executeRun();
        if( _rpnf->_atStop) break;
        if( update_required){
            if( _kbd->scanImmediate() == 8) break;
            _lcd->updateStatusPC( _rpnf->progMem->getCounter());
            _lcd->updateStatusMC( _rpnf->extMem->getCounter());
            _lcd->updateCalcRegister( 0, _rpnf->rpnStack->X->toString( _rpnf->getOutputBuffer()));
        }
    }
    while( _kbd->scanImmediate() != 0) delay( KBD_JITTER_DELAY);
    #ifdef __DEBUG
    Serial.println("STOP/PAUSE");
    #endif
    _kbd->resetLastPressed();
    return _rpnf->requestNextReceiver(_RECEIVER_AUTO_N);
}
