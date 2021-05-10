void Func_Save::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveProgram(command);
}

void Func_Load::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgram( command);
}

void Func_SaveData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveData( command);
}

void Func_LoadData::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadData( command);
}

void Func_SaveAll::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->saveAll( command);
}

void Func_LoadAll::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadAll( command);
}

void Func_Chain::execute( void *components[], char *command){
    RPN_Functions *rpnf = (RPN_Functions *)components[COMPONENT_FUNCTIONS];
    rpnf->loadProgram( command);
}
