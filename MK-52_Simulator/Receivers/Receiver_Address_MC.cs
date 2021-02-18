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
    public class Receiver_Address_MC : Receiver_Address
    {        
        /// <summary>
        /// Sets memory counter
        /// </summary>
        public Receiver_Address_MC(MK52_Host parent)
            : base( parent)
        {
            Moniker = "ADDRESS_MC";
        }

        public override void activate(string prevReceiver)
        {
            _parent.getLCD().updateStatusMC("    ");
            base.activate(prevReceiver);
        }

        protected override void completeEntry( string value)
        {
            if (value.Length == 0) return;
            _parent._m_Extended_Memory.setCounter(value);
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusMC( toString());
            lm.forcePaint();
        }
    }
}
