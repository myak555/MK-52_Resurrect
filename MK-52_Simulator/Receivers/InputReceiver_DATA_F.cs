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
using System.IO;

namespace MK52Simulator
{
    //
    // Implements a receiver for F-modified list
    //
    public class InputReceiver_DATA_F: Receiver
    {
        public InputReceiver_DATA_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "LIST_F";
        }

        //public override string tick(MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        case "Func K":
        //            _parent.setReceiver("LIST_K");
        //            return "Nothing";
        //        case "Func A":
        //            _parent.setReceiver("LIST_A");
        //            return "Nothing";
        //        case "/-/":
        //            _parent.setReceiver("AUTO_N");
        //            return "Nothing";
        //        case "EE":
        //            _parent.setReceiver("PORG_N");
        //            return "Nothing";
        //        case "Cx":
        //            _parent.setReceiver("LIST_N");
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
