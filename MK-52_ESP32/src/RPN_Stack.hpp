//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef RPN_STACK_HPP
#define RPN_STACK_HPP

#include "UniversalValue.hpp"

namespace MK52_Interpreter{
    class RPN_Stack{
        public:
            UniversalValue *Bx = NULL;
            UniversalValue *X = NULL;
            UniversalValue *Y = NULL;
            UniversalValue *Z = NULL;
            UniversalValue *T = NULL;
            char *X_Label = NULL;
            char *Y_Label = NULL;
            char *Z_Label = NULL;
            char *T_Label = NULL;

            void init( void *components[]);
            void clearStack();
            void resetStackLabels();
            bool customStackLabels();
            void setStackLabel(int n, char *text);
            void setStackLabel_P(int n, const char *text);

            inline uint8_t getDMode(){ return _dMode;}; 
            inline char *getDModeName(){ return _dModeName;}; 
            void setDMode(uint8_t m); 
            uint8_t flipDMode(); 
        private:
            uint8_t _stackValues[(RPN_STACK_SIZE+1)*9];
            char _stackLabels[SCREEN_COLS*4+4];
            uint8_t _dMode = DMODE_DEGREES;
            char _dModeName[4];
    };
}

#endif // RPN_STACK_HPP
