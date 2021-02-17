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
            virtual bool checkID( uint16_t id){return false;};
            virtual bool checkName(char *name){return false;};
            virtual const char*Name(){return NULL;};
            virtual const char*IOName(){return Name();};
            virtual void execute(void *components[], char *command=NULL);
            virtual void advancePC(void *components[]);
            virtual bool containsPC(){return false;};
            virtual bool containsMC(){return false;};
            virtual bool containsRegister(){return false;};
        protected:
            inline MK52_Hardware::SD_Manager *_SDM(void *components[]){ return (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];};
            inline RPN_Stack *_Stack(void *components[]){ return (RPN_Stack *)components[COMPONENT_STACK];};
            inline Register_Memory *_RegMem(void *components[]){ return (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];};
            inline Program_Memory *_ProgMem(void *components[]){ return (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];};
            inline Extended_Memory *_ExtMem(void *components[]){ return (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];};
            RPN_Stack *_dealWithClergy1(void *components[]);
            RPN_Stack *_dealWithClergy2(void *components[]);
            void _executeLoop(void *components[], char *command, uint8_t reg);
    };

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
            void executeStep();
            void executeRun();

            bool loadStateFile();
            bool saveStateFile();

            bool loadProgramFile( char *name=NULL);
            bool saveProgramFile( char *name=NULL);

            bool loadDataFile( char *name=NULL);
            bool saveDataFile( char *name=NULL);

            inline char *formFileName(char *name){
                return _sd->makeEntityName( name);};
            bool fileExists(char *name){
                return _sd->checkEntityExists((const char *)name);};

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
            bool _writeStackFile();
            bool _writeRegisterFile();
            bool _writeProgramFile();
            bool _writeDataFile();
            bool _readFile(bool readStack=false, bool readProg=false, bool readMem=false);
    };
};

#endif // RPN_FUNCTIONS_HPP
