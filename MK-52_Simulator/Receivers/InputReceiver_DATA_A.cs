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
    // Implements a generic empty receiver
    //
    public class InputReceiver_DATA_A: Receiver
    {
        public InputReceiver_DATA_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "LIST_A";
        }

        //public override string tick(MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func F":
        //            _parent.setReceiver("LIST_F");
        //            return "Nothing";
        //        case "Func K":
        //            _parent.setReceiver("LIST_K");
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.Counter.Decrement();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.Counter.Set(0);
        //            return "Nothing";

        //        case "EE":
        //            //_parent.setReceiver("LIST_N");
        //            return "Nothing";

        //        case "Cx":
        //            _parent.setReceiver("LIST_N");
        //            _parent.Shutdown();
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
