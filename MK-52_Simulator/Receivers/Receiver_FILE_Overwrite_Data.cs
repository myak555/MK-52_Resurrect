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
    public class Receiver_FILE_Overwrite_Data : Receiver_Confirmation
    {   
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_FILE_Overwrite_Data(MK52_Host parent)
            : base(parent)
        {
            Moniker = "File_Overwrite_Data";
            _Question = "Overwrite data? (\u0018)";
        }

        protected override void performAction()
        {
            _parent.getFunctions().execute(RPN_Functions.FUNC_SAVEDATA);
        }
    }
}
