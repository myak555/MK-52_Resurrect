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
    public class Receiver_Data_Erase : Receiver_Confirmation
    {   
        public Receiver_Data_Erase(MK52_Host parent)
            : base(parent)
        {
            Moniker = "Data_Erase";
            _Question = "Ext. memory erase? (\u0018)";
        }

        protected override void performAction()
        {
            _parent._m_Extended_Memory.clear();
        }
    }
}
