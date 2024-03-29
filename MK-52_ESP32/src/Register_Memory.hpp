//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef REGISTER_MEMORY_HPP
#define REGISTER_MEMORY_HPP

#include "RPN_Stack.hpp"
#include "Extended_Memory.hpp"

namespace MK52_Interpreter{

    class Register_Memory{
      public:
        void init( void *components[]);
        void clear();

        void MtoX(int8_t n);
        void XtoM(int8_t n);
        void K_MtoX(int8_t n);
        void K_XtoM(int8_t n);
        void A_MtoX(int64_t index);
        void A_XtoM(int64_t index);

        int8_t registerByName( char *name);
        inline uint8_t *_registerAddress( int8_t n){
            return _buffer + n*9;};

        inline void MtoX(char *name){
            MtoX( registerByName(name));};
        inline void XtoM(char *name){
            XtoM( registerByName(name));};
        inline void K_MtoX(char *name){
            K_MtoX( registerByName(name));};
        inline void K_XtoM(char *name){
            K_XtoM( registerByName(name));};
        void A_MtoX(char *address);
        void A_XtoM(char *address);

      private:
        uint8_t *_buffer = NULL;
        RPN_Stack *_rst = NULL;
        Extended_Memory *_emem = NULL;
        UniversalValue *_uv = NULL;
        int8_t _chrfind_P( char c);
        void _autoIncrement( int8_t n);
    };
};

#endif // REGISTER_MEMORY_HPP
