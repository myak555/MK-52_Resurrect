//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef REGISTER_MEMORY_HPP
#define REGISTER_MEMORY_HPP

#include "UniversalValue.hpp"

namespace MK52_Interpreter{

    class Register_Memory{
      public:
        bool EditOverwrite = true;
        unsigned long init( void *components[]);
        void clear();
        void resetCounter();

        inline uint32_t getCounter(){ return _counter;};
        uint32_t setCounter(uint32_t c);
        uint32_t setCounter(char *s);
        bool incrementCounter();
        bool decrementCounter();

        inline uint32_t getFree(){return (uint32_t)(_limit-_bottom);};
        inline char *getCurrentLine(){return (char*)_pointer;};
        inline char *getNextLine(){return (char*)_pointer + strlen((char *)_pointer) + 1;};

        bool appendLine(char *line=NULL);
        bool appendLine_P(const char *line);
        bool replaceLine(char *line=NULL);
        bool replaceLine_P(const char *line);
        bool insertLine(char *line=NULL);
        bool insertLine_P(const char *line);
        bool updateLine(char *line=NULL);
        bool updateLine_P(const char *line);
        void deleteLine();

        inline void clearText(){*_text=0;}; 
        char *appendText( char *text);
        char *appendText_P( const char *text);
        inline char *toString(){return _text;};
        inline void setInputMode(const char * m){ strcpy_P( _inputMode, m);};
        inline char *getInputMode(){ return _inputMode;};
        inline char *getEditMode(){ return EditOverwrite? _editModeOverwrite: _editModeInsert;};

      private:
        uint32_t _counter = 0;
        uint8_t *_buffer = NULL;
        uint8_t *_bottom = NULL;
        uint8_t *_limit = NULL;
        uint8_t *_pointer = NULL;
        char _text[PROGRAM_LINE_LENGTH]; // temporary input buffer
        char _inputMode[4];
        char *_editModeOverwrite = "OVR";
        char *_editModeInsert = "INS";
    };
};

#endif // REGISTER_MEMORY_HPP
