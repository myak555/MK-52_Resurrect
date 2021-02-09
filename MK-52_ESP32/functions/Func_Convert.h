void Func_in2mm::execute( void *components[], char *command){
    RPN_Stack *s = _Stack( components);
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( x * 24.5);
}

void Func_mm2in::execute( void *components[], char *command){
    RPN_Stack *s = _Stack( components);
    s->storeBx();
    double x = s->X->toReal();
    s->X->fromReal( x / 24.5);
}

void Func_D2DM::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()) return;
    double x = s->X->toReal();
    bool positive = true;
    if( x<0.0){
        positive = false;
        x = -x;
    }
    double degr = floor(x);
    double mins = (x-degr) * 0.6;
    x = degr + mins;
    s->X->fromReal( positive? x: -x);
}

void Func_D2DMS::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()) return;
    double x = s->X->toReal();
    bool positive = true;
    if( x<0.0){
        positive = false;
        x = -x;
    }
    double degr = floor(x);
    double sec = (x-degr) * 3600.0;
    double min = floor(sec / 60.0);
    sec -= min * 60.0;
    x = degr + 0.01 * ( min + sec * 0.01);
    s->X->fromReal( positive? x: -x);
}

void Func_DM2D::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()) return;
    double x = s->X->toReal();
    bool positive = true;
    if( x<0.0){
        positive = false;
        x = -x;
    }
    double degr = floor(x);
    double mins = (x-degr) * 100.0;
    if( mins>=60.0){
        s->X->fromReal( NAN);
        return;
    }
    x = degr + mins / 60.0;
    s->X->fromReal( positive? x: -x);
}

void Func_DMS2D::execute( void *components[], char *command){
    RPN_Stack *s = _dealWithClergy1(components);
    if( s == NULL) return;
    s->storeBx();
    if( s->X->isInt()) return;
    double x = s->X->toReal();
    bool positive = true;
    if( x<0.0){
        positive = false;
        x = -x;
    }
    double degr = floor(x);
    x = (x-degr) * 100.0;
    double mins = floor(x);
    if( mins>=60.0){
        s->X->fromReal( NAN);
        return;
    }
    double sec = (x-mins) * 100.0;
    if( sec>=60.0){
        s->X->fromReal( NAN);
        return;
    }
    x = degr + (mins*60.0 + sec) / 3600.0;
    s->X->fromReal( positive? x: -x);
}
