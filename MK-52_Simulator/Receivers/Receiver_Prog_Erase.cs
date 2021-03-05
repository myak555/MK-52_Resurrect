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
    // Implements a text data entry editor
    //
    public class Receiver_Prog_Erase : Receiver_Confirmation
    {   
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Prog_Erase(MK52_Host parent)
            : base(parent)
        {
            Moniker = "Prog_Erase";
            _Question = "Program erase? (\u0018)";
        }

        protected override void performAction()
        {
            _parent._m_Program_Memory.clear();
        }
    }
}
