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
    public class Receiver_FILE_All : Receiver_FILE_Name
    {
        public Receiver_FILE_All(MK52_Host parent)
            : base(parent)
        {
            Moniker = "File_All";
        }

        protected override void completeEntry(string value)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            string tmpName = _rpnf.formFileName(value);
            if (!UniversalValue._endsWith_P(value, _Ext)) tmpName += _Ext;
            if( _rpnf.fileExists(tmpName))
            {
                _mode = _Overwrite;
                updateDisplay(toString());
                return;
            }
            _rpnf.saveAll( tmpName);
            _parent.getFunctions().requestNextReceiver(_return_to);
            return;
        }
    }
}
