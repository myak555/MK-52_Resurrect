void Func_Delay::execute( void *components[], char *command){
    int32_t ms = UniversalValue::_recoverAddress(command);
    delay( ms);
}

void Func_LEDOn::execute( void *components[], char *command){
    MK52_Hardware::KBD_Manager *_kbd = _KBD( components);
    _kbd->LEDOn = true;
    _kbd->reset();
}

void Func_LEDOff::execute( void *components[], char *command){
    MK52_Hardware::KBD_Manager *_kbd = _KBD( components);
    _kbd->LEDOn = false;
    _kbd->reset();
}

void Func_Update::execute( void *components[], char *command){
    RPN_Functions *_rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    MK52_Hardware::LCD_Manager *_lcd = _LCD( components);
    RPN_Stack *_st = _rpnf->rpnStack;
    Program_Memory *_pm = _rpnf->progMem;
    Extended_Memory *_em = _rpnf->extMem;
    char *buff = _rpnf->getOutputBuffer();
    _lcd->updateStatus( _pm->getCounter(), _em->getCounter(), _st->getDModeName(), "RUN");
    _lcd->updateCalcRegister( 0, _st->X->toString( buff));
    _lcd->updateCalcLabel( 0, _st->X_Label);
    _lcd->updateCalcRegister( 1, _st->Y->toString( buff));
    _lcd->updateCalcLabel( 1, _st->Y_Label);
    _lcd->updateCalcRegister( 2, _st->Z->toString( buff));
    _lcd->updateCalcLabel( 2, _st->Z_Label);
    _lcd->updateCalcRegister( 3, _st->T->toString( buff));
    _lcd->updateCalcLabel( 3, _st->T_Label);
}
