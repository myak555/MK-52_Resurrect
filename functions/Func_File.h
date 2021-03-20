void Func_Remove::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = _SDM( components);
    sd->deleteEntity( sd->getItemFromListing());
    int16_t tmp = sd->listingPosition;
    sd->readFolderItems();
    sd->setListingPosition(tmp);
}

void Func_StepIn::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = _SDM( components);
    char *filename = sd->getItemFromListing();
    if( !sd->stepIn( filename)) return;
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    if( UniversalValue::_endsWith_P( filename, PSTR(".DAT")))
        rpnf->loadData( filename);
    else
        rpnf->loadProgram( filename);
}

void Func_Save::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveProgram();
}

void Func_SaveAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveProgram( command);
}

void Func_Load::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgram();
}

void Func_LoadFrom::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgram( command);
}

void Func_SaveData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveData();
}

void Func_SaveDataAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveData( command);
}

void Func_LoadData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadData();
}

void Func_LoadDataFrom::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadData(command);
}

void Func_SaveAll::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveData(); // TODO
}

void Func_SaveAllAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveData( command); // TODO
}

void Func_LoadAll::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadData(); // TODO
}

void Func_LoadAllFrom::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadData(command); // TODO
}

void Func_Chain::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgram( command); // TODO
}
