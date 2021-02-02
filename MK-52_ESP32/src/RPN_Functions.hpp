//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef RPN_FUNCTIONS_HPP
#define RPN_FUNCTIONS_HPP

#include "SD_Manager.hpp"
#include "Program_Memory.hpp"
#include "Register_Memory.hpp"

namespace MK52_Interpreter{

    class RPN_Function{
        public:
            virtual bool checkID( uint16_t id);
            virtual bool checkName(char *name);
            virtual const char*Name();
            virtual const char*IOName();
            virtual void execute(void *components[], char *command=NULL);
        protected:
            RPN_Stack *_dealWithClergy1(void *components[]);
            RPN_Stack *_dealWithClergy2(void *components[]);
    };

    class RPN_Functions{
        public:
            bool _atStop = false;
            RPN_Stack *rpnStack;
            Program_Memory *progMem;
            Extended_Memory *extMem;

            inline char *getOutputBuffer(){return _text;};
            inline char *getOutputLine(int16_t n)
                {return _buffer + (SCREEN_COLS+1)*n;};
            inline char **getOutputLines() {return _lines;};

            unsigned long init( void *components[]);
            RPN_Function *getFunctionByID(int16_t id);
            RPN_Function *getFunctionByName(char *command);
            void execute( int16_t id=-1, char *command=NULL);
            void execute( char *command, bool pushNeeded=false);
            void executeStep();

            bool loadDataFile();
            bool saveDataFile();
            bool saveDataFileAs( char * name);

            inline char *formFileName(char *name){ return _sd->makeEntityName( name);};
            bool fileExists(char *name){ return _sd->checkEntityExists((const char *)name);};

      private:
            void **_components;
            MK52_Hardware::SD_Manager *_sd = NULL;
            uint16_t _nfunctions = 0;
            void *_functions[MK52_NFUNCTIONS];
            char *_text = NULL; // temporary output buffer
            UniversalValue *_tmpuv; // temporary value for number conversion
            char *_buffer = NULL;
            char *_lines[SCREEN_ROWS];
            void _appendFunction( RPN_Function *f);
            bool _writeDataFile(bool writeStack=false, bool writeProg=false, bool writeMem=false);
            bool _readDataFile(bool readStack=false, bool readProg=false, bool readMem=false);
    };
};

#endif // RPN_FUNCTIONS_HPP
