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
    public class Receiver_Address_AXM : Receiver_Address
    {        
        /// <summary>
        /// Sets memory counter
        /// </summary>
        public Receiver_Address_AXM(MK52_Host parent)
            : base( parent)
        {
            Moniker = "ADDRESS_AXM";
        }

        public override void activate(string prevReceiver)
        {
            _parent.getLCD().updateStatusMC("    ");
            base.activate("AUTO_N");
        }

        protected override void completeEntry( string value)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            if (value.Length == 0)
            {
                _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                _rpnf.execute(RPN_Functions.FUNC_A_X2M);
            }
            else
                _rpnf.execute(RPN_Functions.FUNC_A_X2M, value);
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusMC( toString());
            lm.requestUpdate();
        }
    }
}
