//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef EXTENDED_MEMORY_HPP
#define EXTENDED_MEMORY_HPP

#include "UniversalValue.hpp"

namespace MK52_Interpreter{

    class Extended_Memory{
      public:
        unsigned long init( void *components[]);
        void clear();
        void resetCounter();

        inline uint32_t getCounter(){ return _counter;};
        uint32_t setCounter(uint32_t c);
        uint32_t setCounter(char *s);
        bool incrementCounter();
        bool decrementCounter();

        inline uint8_t *getCurrentLine(){return _buffer + _counter * 9;};
        inline uint8_t *getLine( uint32_t n){return _buffer + n * 9;};

        char *toString( char *buff, int32_t n);

      private:
        uint32_t _counter = 0;
        uint8_t *_buffer = NULL;
        inline uint8_t *_memoryAddress( int32_t index){
           return _buffer + index*9;};
    };
};

#endif // EXTENDED_MEMORY_HPP
