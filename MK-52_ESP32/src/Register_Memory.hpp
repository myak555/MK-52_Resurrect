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
#include "RPN_Stack.hpp"
#include "Extended_Memory.hpp"

namespace MK52_Interpreter{

    class Register_Memory{
      public:
        unsigned long init( void *components[]);
        void clear();

        void MtoX(int8_t n);
        void XtoM(int8_t n);
        void K_MtoX(int8_t n);
        void K_XtoM(int8_t n);

        int8_t registerByName( char *name);

        inline void MtoX(char *name){
            MtoX( registerByName(name));};
        inline void XtoM(char *name){
            XtoM( registerByName(name));};
        inline void K_MtoX(char *name){
            K_MtoX( registerByName(name));};
        inline void K_XtoM(char *name){
            K_XtoM( registerByName(name));};

      private:
        uint8_t *_buffer = NULL;
        RPN_Stack *_rst = NULL;
        Extended_Memory *_emem = NULL;
        inline uint8_t *_registerAddress( int8_t n){
           return _buffer + n*9;};
        int8_t _chrfind_P( char c);
    };
};

#endif // REGISTER_MEMORY_HPP
