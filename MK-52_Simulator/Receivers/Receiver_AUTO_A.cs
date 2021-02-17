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
    // Implements a receiver for A-modified buttons
    //
    public class Receiver_AUTO_A : Receiver_AUTO
    {
        public Receiver_AUTO_A(MK52_Host parent)
            : base(parent)
        {
            Moniker = "AUTO_A";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" A ");
            lm.Refresh();
        }

        public override byte tick(byte scancode)
        {
            if (scancode == 0) return 0;
            _parent.setReceiver("AUTO_N");
            return 0;
        }

        //public override string tick(MK52_Button button)
        //{
        //    //if (_parent.Memory.Counter.isActive)
        //    //{
        //    //    _parent.Memory.onButton(button);
        //    //    return "Nothing";
        //    //}
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func F":
        //            return "AUTO_F";
        //        case "Func K":
        //            return "AUTO_K";
        //        case "Mode":
        //            _parent._m_RPN_Stack.toggleAngleMode();
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent.Memory.Counter.Increment();
        //            return "Nothing";
        //        case "<-":
        //            //_parent.Memory.Counter.Decrement();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent.Memory.Counter.Set(0);
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent.Memory.ActivateEntry( Extended_Memory.MemoryToStack);
        //            return "Nothing";
        //        case "X->M":
        //            //_parent.Memory.ActivateEntry(Extended_Memory.StackToMemory);
        //            return "Nothing";
        //        case "GOTO":
        //            //_parent.Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Column 3
        //        // Does nothing

        //        // Column 4
        //        // Does nothing

        //        // Column 5
        //        case "6":
        //            //_parent.executeFunction("<-RAD");
        //            return "AUTO_N";
        //        case "3":
        //            //_parent.executeFunction("<-IN");
        //            return "AUTO_N";

        //        // Column 6
        //        case "+":
        //            //_parent.executeFunction("RAD->");
        //            return "AUTO_N";
        //        case "Swap":
        //            //_parent.executeFunction("IN->");
        //            return "AUTO_N";
        //        case "EE":
        //            return "DATA_N";

        //        // Column 7
        //        case "Enter":
        //            //_parent.executeFunction("SEED");
        //            return "AUTO_N";
        //        case "Cx":
        //            //_parent.CalcStack.CompleteEntry();
        //            _parent.setReceiver("AUTO_N");
        //            _parent.Shutdown();
        //            return "OFF";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}