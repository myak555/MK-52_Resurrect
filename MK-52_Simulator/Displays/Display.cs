//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the generic interface to calculator display
    //
    public class Display
    {
        public string Moniker = "Undefined";
        protected MK52_Host _parent = null;

        public virtual void init( MK52_Host parent)
        {
            _parent = parent;
        }

        public virtual void activate( string prevDisplay)
        {
            _parent._m_Hardware_LCD.outputStatus(
                _parent._m_Program_Memory.getCounter(),
                _parent._m_Extended_Memory.getCounter(),
                _parent._m_RPN_Stack.getDModeName(),
                "   ");
        }
        
        public virtual void updateStatusPC( uint pc)
        {
            _parent._m_Hardware_LCD.updateStatusPC(pc);
        }

        public virtual void updateStatusPC(string pc)
        {
            _parent._m_Hardware_LCD.updateStatusPC(pc);
        }

        public virtual void updateStatusMC(uint mc)
        {
            _parent._m_Hardware_LCD.updateStatusMC(mc);
        }

        public virtual void updateStatusMC(string mc)
        {
            _parent._m_Hardware_LCD.updateStatusPC(mc);
        }

        public virtual void updateStatusFunc(string func)
        {
            _parent._m_Hardware_LCD.updateStatusFMODE(func);
        }

        public virtual void updateBody()
        {
        }

        public virtual void updateLastLine()
        {
        }
    }
 }
