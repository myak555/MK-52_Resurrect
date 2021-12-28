//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef RPN_FUNCTION_HPP
#define RPN_FUNCTION_HPP

#include "KBD_Manager.hpp"
#include "LCD_Manager.hpp"
#include "SD_Manager.hpp"
#include "Program_Memory.hpp"
#include "Register_Memory.hpp"
#include "../receivers/receivers.h"

namespace MK52_Interpreter{

    class RPN_Function{
        public:
            virtual bool checkID( uint16_t id){return false;};
            virtual bool checkName(char *name){return false;};
            //virtual const char*Name(){return NULL;};
            virtual const char*Name(){return PSTR("");}; // must return a valid empty string
            virtual const char*IOName(){return Name();};
            virtual void execute(void *components[], char *command=NULL);
            virtual void advancePC(void *components[]);
            virtual bool containsPC(){return false;};
            virtual bool containsMC(){return false;};
            virtual bool containsRegister(){return false;};
        protected:
            inline MK52_Hardware::KBD_Manager *_KBD(void *components[])
                { return (MK52_Hardware::KBD_Manager *)components[COMPONENT_KBD_MANAGER];};
            inline MK52_Hardware::LCD_Manager *_LCD(void *components[])
                { return (MK52_Hardware::LCD_Manager *)components[COMPONENT_LCD_MANAGER];};
            inline MK52_Hardware::SD_Manager *_SDM(void *components[])
                { return (MK52_Hardware::SD_Manager *)components[COMPONENT_SD_MANAGER];};
            inline RPN_Stack *_Stack(void *components[])
                { return (RPN_Stack *)components[COMPONENT_STACK];};
            inline Register_Memory *_RegMem(void *components[])
                { return (Register_Memory *)components[COMPONENT_REGISTER_MEMORY];};
            inline Program_Memory *_ProgMem(void *components[])
                { return (Program_Memory *)components[COMPONENT_PROGRAM_MEMORY];};
            inline Extended_Memory *_ExtMem(void *components[])
                { return (Extended_Memory *)components[COMPONENT_EXTENDED_MEMORY];};
            RPN_Stack *_dealWithClergy1(void *components[]);
            RPN_Stack *_dealWithClergy2(void *components[]);
            RPN_Stack *_dealWithClergy3(void *components[]);
            RPN_Stack *_dealWithClergy4(void *components[]);
            void _executeLoop(void *components[], char *command, uint8_t reg);
    };
};

#endif // RPN_FUNCTION_HPP
