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
    public class Receiver_Address_PC : Receiver_Address
    {        
        /// <summary>
        /// Sets program counter
        /// </summary>
        public Receiver_Address_PC(MK52_Host parent)
            : base( parent)
        {
            Moniker = "ADDRESS_PC";
        }

        public override void activate(string prevReceiver)
        {
            _parent.getLCD().updateStatusPC("    ");
            base.activate(prevReceiver);
        }

        protected override void completeEntry( string value)
        {
            if (value.Length == 0) return;
            _parent._m_Program_Memory.setCounter(value);
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusPC( toString());
            lm.forcePaint();
        }
    }
}
