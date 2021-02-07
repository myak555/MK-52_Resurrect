void Func_MkDir::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    sd->createFolder( command);
}

void Func_UpDir::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    sd->upFolder();
}

void Func_NextFile::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    sd->nextListingPosition();
}

void Func_PrevFile::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    sd->previousListingPosition();
}

void Func_Remove::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    sd->deleteEntity( sd->getItemFromListing());
    int16_t tmp = sd->listingPosition;
    sd->readFolderItems();
    sd->setListingPosition(tmp);
}

void Func_StepIn::execute( void *components[], char *command){
    MK52_Hardware::SD_Manager *sd = (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];
    char *filename = sd->getItemFromListing();
    if( !sd->stepIn( filename)) return;
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    if( UniversalValue::_endsWith_P( filename, PSTR(".DAT")))
        rpnf->loadDataFile( filename);
    else
        rpnf->loadProgramFile( filename);
}

void Func_Save::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveProgramFile();
}

void Func_SaveAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveProgramFile( command);
}

void Func_Load::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgramFile();
}

void Func_LoadFrom::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgramFile( command);
}

void Func_Chain::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgramFile( command);
}

void Func_SaveData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveDataFile();
}

void Func_SaveDataAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveDataFile( command);
}

void Func_LoadData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadDataFile();
}

void Func_LoadDataFrom::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadDataFile(command);
}
