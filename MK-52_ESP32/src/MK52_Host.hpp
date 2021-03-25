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

#include "../receivers/receivers.h"
#include "Receivers.hpp"

namespace MK52_Interpreter{
    class MK52_Host{

      public:
        Receiver *current_Receiver = NULL;

        void init();

        inline MK52_Hardware::LCD_Manager *getLCD(){
          return (MK52_Hardware::LCD_Manager*)_components[COMPONENT_LCD_MANAGER];};
        inline MK52_Hardware::KBD_Manager *getKBD(){
          return (MK52_Hardware::KBD_Manager*)_components[COMPONENT_KBD_MANAGER];};
        inline MK52_Hardware::SD_Manager *getSD(){
          return (MK52_Hardware::SD_Manager*)_components[COMPONENT_SD_MANAGER];};
        inline RPN_Functions *getFunctions(){
          return (RPN_Functions*)_components[COMPONENT_FUNCTIONS];};

        void tick();
        inline Receiver *getReceiver( int id){
          return (Receiver *)_receivers[id];};
        bool setReceiver(int id);
        bool setRequestedReceiver();

        void shutdown();

      protected:
        void *_components[N_COMPONENTS];
        void *_receivers[N_RECEIVERS];
        Receiver *_addReceiver( Receiver *rc);
        void _addReceivers();
    };    
};

#endif // MK52_HOST_HPP
