//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef RPN_FUNCTIONS_HPP
#define RPN_FUNCTIONS_HPP

#include "RPN_Function.hpp"

namespace MK52_Interpreter{
    class RPN_Functions{
        public:
            bool _atStop = false;
            RPN_Stack *rpnStack = NULL;
            Register_Memory *regMem = NULL;
            Program_Memory *progMem = NULL;
            Extended_Memory *extMem = NULL;

            void init( void *components[]);

            inline char *getOutputBuffer(){return _text;};
            char *setOutputBuffer(char *text);
            char *appendOutputBuffer(char *text);
            char *setOutputBuffer_P(const char *text);
            char *appendOutputBuffer_P(const char *text);
            inline char *getOutputLine(int16_t n){
                return _buffer + (SCREEN_COLS+1)*n;};
            inline char **getOutputLines() {return _lines;};

            RPN_Function *getFunctionByID(int16_t id);
            RPN_Function *getFunctionByName(char *command);
            RPN_Function *getFunctionByIOName(char *command);
            void execute( int16_t id=-1, char *command=NULL);
            void execute( char *command);
            bool clearStopCondition();
            void executeStep();
            void executeRun();

            bool loadState();
            bool saveState();

            bool loadProgram( char *name=NULL);
            bool saveProgram( char *name=NULL);

            bool loadData( char *name=NULL);
            bool saveData( char *name=NULL);

            bool loadAll( char *name=NULL);
            bool saveAll( char *name=NULL);

            inline char *formFileName(char *name){
                return _sd->makeEntityName( name);};
            bool fileExists(char *name){
                return _sd->checkEntityExists((const char *)name);};

            // TODO: add receivers
            inline void appendProgramLine_P( int16_t id){
                progMem->updateLine_P( getFunctionByID(id)->Name());}

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
            bool _writeStack();
            bool _writeRegisters();
            bool _writeProgram();
            bool _writeData();
            bool _writeReturnStack();
            bool _read(bool readStack=false, bool readProg=false, bool readMem=false);
    };
};

#endif // RPN_FUNCTIONS_HPP
