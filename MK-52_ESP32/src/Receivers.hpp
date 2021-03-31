//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef INPUT_RECEIVERS_HPP
#define INPUT_RECEIVERS_HPP

#include "Receiver.hpp"

#define _MODE_OFF             0
#define _MODE_NUMBER_WHOLE    1
#define _MODE_NUMBER_DECIMAL  2
#define _MODE_NUMBER_EXPONENT 3
#define _MODE_ENTRY_TEXT      1
#define _MODE_ENTRY_NUMBER    2
#define _MODE_ENTRY_SYMBOL    3
#define _MODE_ENTRY_CONFIRM   4

namespace MK52_Interpreter{

    class Receiver_OFF: public Receiver{
      public:
        Receiver_OFF(void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO: public Receiver{
      public:
        Receiver_AUTO(void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_N: public Receiver_AUTO{
      public:
        Receiver_AUTO_N( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_F: public Receiver_AUTO{
      public:
        Receiver_AUTO_F( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_K: public Receiver_AUTO{
      public:
        Receiver_AUTO_K( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_A: public Receiver_AUTO{
      public:
        Receiver_AUTO_A( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_AUTO_R: public Receiver_AUTO{
      public:
        Receiver_AUTO_R( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_DATA: public Receiver{
      public:
        Receiver_DATA( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_N: public Receiver_DATA{
      public:
        Receiver_DATA_N( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_F: public Receiver_DATA{
      public:
        Receiver_DATA_F( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_K: public Receiver_DATA{
      public:
        Receiver_DATA_K( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_DATA_A: public Receiver_DATA{
      public:
        Receiver_DATA_A( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_PROG: public Receiver{
      public:
        Receiver_PROG( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
      private:
        char *_displayLines[SCREEN_ROWS-1];
        char *_getTerminalLine( char *buff, int32_t lineNumber, char *text);
    };

    class Receiver_PROG_N: public Receiver_PROG{
      public:
        Receiver_PROG_N( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_PROG_F: public Receiver_PROG{
      public:
        Receiver_PROG_F( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_PROG_K: public Receiver_PROG{
      public:
        Receiver_PROG_K( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_PROG_A: public Receiver_PROG{
      public:
        Receiver_PROG_A( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_FILE: public Receiver{
      public:
        Receiver_FILE( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
      protected:
        MK52_Hardware::SD_Manager *_sd = NULL;
    };

    class Receiver_FILE_N: public Receiver_FILE{
      public:
        Receiver_FILE_N( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_FILE_F: public Receiver_FILE{
      public:
        Receiver_FILE_F( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_FILE_K: public Receiver_FILE{
      public:
        Receiver_FILE_K( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_FILE_A: public Receiver_FILE{
      public:
        Receiver_FILE_A( void *components[]);
        uint8_t tick( uint8_t scancode = 0);
    };

    class Receiver_Number: public Receiver{
      public:
        Receiver_Number( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        char *toTrimmedString();
      protected:
        char *_text = NULL;
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
      private:
        void _processDigit( int8_t ln, char c);
        void _processExponent( int8_t ln);
        bool _processCx( int8_t ln);
        inline void _swapSign( char *pos, char plusChar){ *pos = (*pos == '-')? plusChar: '-';};
    };

    class Receiver_Number_DATA: public Receiver_Number{
      public:
        Receiver_Number_DATA( void *components[]);
      protected:
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
    };

    class Receiver_Number_PROG: public Receiver_Number{
      public:
        Receiver_Number_PROG( void *components[]);
      protected:
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
    };

    class Receiver_Text: public Receiver{
      public:
        Receiver_Text( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        char *toTrimmedString();
      protected:
        char *_text = NULL;
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
    };

    class Receiver_Address: public Receiver{
      public:
        Receiver_Address( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        char *toTrimmedString();
      protected:
        char _text[5]; // temporary input buffer
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
    };

    class Receiver_Address_AMX: public Receiver_Address{
      public:
        Receiver_Address_AMX( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
        void updateDisplay( char *value);
    };

    class Receiver_Address_AXM: public Receiver_Address{
      public:
        Receiver_Address_AXM( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
        void updateDisplay( char *value);
    };

    class Receiver_Address_MC: public Receiver_Address{
      public:
        Receiver_Address_MC( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
        void updateDisplay( char *value);
    };

    class Receiver_Address_PC: public Receiver_Address{
      public:
        Receiver_Address_PC( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
        void updateDisplay( char *value);
    };

    class Receiver_Register: public Receiver{
      public:
        Receiver_Register( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
      private:
        char _text[3]; // temporary input buffer
        virtual void completeEntry( char *value);
    };

    class Receiver_Register_MX: public Receiver_Register{
      public:
        Receiver_Register_MX( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_Register_XM: public Receiver_Register{
      public:
        Receiver_Register_XM( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_Register_KMX: public Receiver_Register{
      public:
        Receiver_Register_KMX( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_Register_KXM: public Receiver_Register{
      public:
        Receiver_Register_KXM( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_Register_EM: public Receiver_Register{
      public:
        Receiver_Register_EM( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_Register_ME: public Receiver_Register{
      public:
        Receiver_Register_ME( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_FILE_Name: public Receiver{
      public:
        Receiver_FILE_Name( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
        inline char *toString(){ return _text;};
        char *toTrimmedString();
      protected:
        char *_text = NULL;
        char _Question[SCREEN_COLS+1];
        virtual void completeEntry( char *value);
        virtual void updateDisplay( char *value);
        virtual byte _mode1_Tick( uint8_t scancode);
        virtual byte _mode2_Tick( uint8_t scancode);
    };

    class Receiver_FILE_All: public Receiver_FILE_Name{
      public:
        Receiver_FILE_All( void *components[]);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_FILE_Data: public Receiver_FILE_Name{
      public:
        Receiver_FILE_Data( void *components[]);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_FILE_MkDir: public Receiver_FILE_Name{
      public:
        Receiver_FILE_MkDir( void *components[]);
      protected:
        void completeEntry( char *value);
    };

    class Receiver_CONFIRM: public Receiver{
      public:
        Receiver_CONFIRM( void *components[]);
        void activate( int8_t prevReceiver = NO_CHANGE);
        uint8_t tick( uint8_t scancode = 0);
      protected:
        char _Question[SCREEN_COLS+1];
        virtual void performAction();
    };

    class Receiver_PROG_Erase: public Receiver_CONFIRM{
      public:
        Receiver_PROG_Erase( void *components[]);
      protected:
        virtual void performAction();
    };

    class Receiver_DATA_Erase: public Receiver_CONFIRM{
      public:
        Receiver_DATA_Erase( void *components[]);
      protected:
        virtual void performAction();
    };

    class Receiver_FILE_Delete: public Receiver_CONFIRM{
      public:
        Receiver_FILE_Delete( void *components[]);
      protected:
        virtual void performAction();
    };

    class Receiver_FILE_Overwrite: public Receiver_CONFIRM{
      public:
        Receiver_FILE_Overwrite( void *components[]);
      protected:
        virtual void performAction();
    };

    class Receiver_FILE_Overwrite_All: public Receiver_CONFIRM{
      public:
        Receiver_FILE_Overwrite_All( void *components[]);
      protected:
        virtual void performAction();
    };

    class Receiver_FILE_Overwrite_Data: public Receiver_CONFIRM{
      public:
        Receiver_FILE_Overwrite_Data( void *components[]);
      protected:
        virtual void performAction();
    };
};

#endif // INPUT_RECEIVERS_HPP
