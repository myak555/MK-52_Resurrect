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
    sd->stepIn( sd->getItemFromListing());
}

void Func_SaveDataAs::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveDataFileAs( command);
}

void Func_LoadData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadDataFile();
}
