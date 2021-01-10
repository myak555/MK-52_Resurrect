//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Pin assignment:
//
// 33 - POWER HOLD
#define SYSTEM_POWER_HOLD      33

#ifndef MK52_HOST_HPP
#define MK52_HOST_HPP

#include "Common.h"
#include "KBD_Manager.hpp"
#include "LCD_Manager.hpp"
#include "SD_Manager.hpp"
#include "Input_Receivers.hpp"
#include "Displays.hpp"

namespace MK52_Interpreter{
    class MK52_Host{

      public:
        Input_Receiver *current_Receiver = NULL;
        Display *current_Display = NULL;
        unsigned long init();

        inline MK52_Hardware::LCD_Manager *getLCD(){
          return (MK52_Hardware::LCD_Manager*)_components[COMPONENT_LCD_MANAGER];};
        inline MK52_Hardware::KBD_Manager *getKBD(){
          return (MK52_Hardware::KBD_Manager*)_components[COMPONENT_KBD_MANAGER];};
        inline MK52_Hardware::SD_Manager *getSD(){
          return (MK52_Hardware::SD_Manager*)_components[COMPONENT_SD_MANAGER];};

        inline Display *getDisplay( int id){
          return (Display *)_components[id];};
        inline void setDisplay(int id){
          current_Display = getDisplay( id);};

        inline Input_Receiver *getReceiver( int id){
          return (Input_Receiver *)_components[id];};
        inline void setReceiver(int id){
          current_Receiver = getReceiver( id);};

        inline void shutdown(){ digitalWrite( SYSTEM_POWER_HOLD, LOW); };

      protected:
        void *_components[];
    };    
};

#endif // MK52_HOST_HPP
