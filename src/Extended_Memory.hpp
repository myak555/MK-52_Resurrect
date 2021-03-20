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
        void init( void *components[]);
        void clear();
        void clearCurrent();
        void resetCounter();

        inline uint32_t getCounter(){ return _counter;};
        uint32_t setCounter(uint32_t address);
        uint32_t setCounter(char *text);
        bool incrementCounter();
        bool decrementCounter();

        inline uint8_t *getCurrentLine(){return _buffer + _counter * 9;};
        inline uint8_t *getLine( uint32_t n){return _buffer + n * 9;};

        char *toString( char *text, int32_t n);
        char *toCounterString( char *text);
        void fromString( char *text);
        inline UniversalValue *getTemporaryUV(){return _uv;};
        void fromUV( UniversalValue *uv);
        void toUV( UniversalValue *uv);
        void swapWithUV( UniversalValue *uv);

      private:
        uint32_t _counter = 0;
        uint8_t *_buffer = NULL;
        UniversalValue *_uv = NULL;
        inline uint8_t *_memoryAddress( int32_t index){
           return _buffer + index*9;};
    };
};

#endif // EXTENDED_MEMORY_HPP
