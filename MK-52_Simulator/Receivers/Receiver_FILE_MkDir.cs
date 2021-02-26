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
    public class Receiver_FILE_MkDir : Receiver_FILE_Name
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_FILE_MkDir(MK52_Host parent)
            : base(parent)
        {
            Moniker = "File_MkDir";
            _Question = "Folder name?";
        }

        protected override void completeEntry(string value)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            string tmpName = _rpnf.formFileName(value);
            _rpnf.execute(RPN_Functions.FUNC_MKDIR, value);
            _parent.getFunctions().requestNextReceiver(_return_to);
            return;
        }
    }
}
