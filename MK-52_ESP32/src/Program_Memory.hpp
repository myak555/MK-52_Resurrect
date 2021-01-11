//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef PROGRAM_MEMORY_HPP
#define PROGRAM_MEMORY_HPP

#include "Common.h"
#include "SD_Manager.hpp"

namespace MK52_Interpreter{

    class Program_Memory{
      public:
        unsigned long init( void *components[]);
        void clear();
        void resetCounter();

        inline uint32_t getCounter(){ return _counter;};
        uint32_t setCounter(uint32_t c);
        bool incrementCounter();
        bool decrementCounter();

        inline uint32_t free(){return (uint32_t)(_limit-_bottom);};
        inline char *getCurrentLine(){return (char*)_pointer;};
        inline char *getNextLine(){return (char*)_pointer + strlen((char *)_pointer) + 1;};

        bool appendLine(char *line);
        bool appendLine_P(const char *line);
        bool replaceLine(char *line);
        bool replaceLine_P(const char *line);
        bool insertLine(char *line);
        bool insertLine_P(const char *line);
        void deleteLine();

      private:
        uint32_t _counter = 0;
        uint8_t *_buffer = NULL;
        uint8_t *_bottom = NULL;
        uint8_t *_limit = NULL;
        uint8_t *_pointer = NULL;
    };
};

#endif // PROGRAM_MEMORY_HPP
