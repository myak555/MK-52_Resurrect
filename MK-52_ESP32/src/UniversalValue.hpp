//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef UNIVERSAL_VALUE_HPP
#define UNIVERSAL_VALUE_HPP

#include "Common.h"

namespace MK52_Interpreter{
    class UniversalValue{
        public:
            UniversalValue( uint8_t *location);
            inline uint8_t getType(){return *_ptr;};
            inline bool isEmpty(){return *_ptr == VALUE_TYPE_EMPTY;};
            inline bool isInt(){return *_ptr == VALUE_TYPE_INTEGER;};
            inline bool isReal(){return *_ptr == VALUE_TYPE_DOUBLE;};
            void fromEmpty();
            void fromInt(int64_t value);
            void fromReal(double value);
            inline uint8_t fromLocation( uint8_t *location)
              {
                memcpy(_ptr, location, 9);
                return *_ptr;};
            uint8_t fromString( char *text);
            int64_t toInt();
            double toReal();
            inline uint8_t *toBytes(){return (uint8_t *)_ptr;};
            char *toString( char *text);
        private:
            uint8_t *_ptr = NULL;
            inline uint64_t *_asIntPtr(){return (uint64_t *)(_ptr+1);};
            inline double *_asRealPtr(){return (double *)(_ptr+1);};
            char *_composeDouble(char *text, double value); 
            char *_composeInt64(char *text, int64_t value);
    };
}

#endif // UNIVERSAL_VALUE_HPP
