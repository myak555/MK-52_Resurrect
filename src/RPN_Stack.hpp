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
            void clear();
            void resetLabels();
            bool customLabels();
            void setLabel(int n, char *text);
            void setLabel_P(int n, const char *text);

            inline uint8_t getDMode(){ return _dMode;}; 
            inline char *getDModeName(){ return _dModeName;}; 
            void setDMode(uint8_t m); 
            uint8_t toggleAngleMode();

            void push( uint16_t start=1);
            void pop( uint16_t start=1);
            void storeBx();
            void swap();
            void rotate();

            double XtoRadian();
            int8_t XtoOctant();
            void RadianToX(double value);
            void OctantToX(int8_t value);

            void setTrigAccuracyWarning( double value);
            bool setNegativeRootWarning( double value);
        private:
            uint8_t _stackValues[(RPN_STACK_SIZE+1)*9];
            char _stackLabels[SCREEN_COLS*4+4];
            uint8_t _dMode = DMODE_DEGREES;
            char _dModeName[5];
    };
}

#endif // RPN_STACK_HPP
