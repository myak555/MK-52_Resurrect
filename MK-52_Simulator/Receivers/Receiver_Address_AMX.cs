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
    public class Receiver_Address_AMX : Receiver_Address
    {        
        /// <summary>
        /// Sets memory counter
        /// </summary>
        public Receiver_Address_AMX(MK52_Host parent)
            : base( parent)
        {
            Moniker = "ADDRESS_AMX";
        }

        public override void activate(string prevReceiver)
        {
            _parent.getLCD().updateStatusMC("    ");
            base.activate("AUTO_N");
        }

        protected override void completeEntry( string value)
        {
            if (value.Length == 0)
            {
                _parent.getFunctions().execute(RPN_Functions.FUNC_A_M2X);
                _parent.getFunctions().execute(RPN_Functions.FUNC_DECREMENT_MC);
            }
            else
                _parent.getFunctions().execute( RPN_Functions.FUNC_A_M2X, value);
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusMC( toString());
            lm.forcePaint();
        }
    }
}
