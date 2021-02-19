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
    // Implements a register entry
    //
    public class Receiver_Register_ME : Receiver_Register
    {
        /// <summary>
        /// Inputs register name in the Data mode
        /// </summary>
        public Receiver_Register_ME(MK52_Host parent)
            : base( parent)
        {
            Moniker = "REGISTER_ME";
        }

        public override void activate(string prevReceiver)
        {
            base.activate("DATA_N");
        }

        protected override void completeEntry(string value)
        {
            if (value.Length < 1) return;
            _parent.getFunctions().execute(RPN_Functions.FUNC_RTOMEX, value);
        }
    }
}
