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
#include "RPN_Stack.hpp"
#include "Program_Memory.hpp"
#include "Extended_Memory.hpp"
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
            RPN_Stack *Stack;
            Program_Memory *progMem;
            Extended_Memory *extMem;

            unsigned long init( void *components[]);
            void execute( int16_t id=-1);
            void execute( char *s);

      private:
            void **_components;
            void _appendFunction( RPN_Function *f);
            uint16_t _nfunctions = 0;
            void *_functions[MK52_NFUNCTIONS];
    };
};

#endif // RPN_FUNCTIONS_HPP
