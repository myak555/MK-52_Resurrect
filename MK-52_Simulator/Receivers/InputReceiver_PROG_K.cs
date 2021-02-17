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
    public class InputReceiver_PROG_K: Receiver
    {
        public InputReceiver_PROG_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_K";
        }

        //public override string tick(MK52_Button button)
        //{
        //    //if (_parent._m_Program_Memory.Counter.isActive)
        //    //{

        //    //    if (_parent._m_Program_Memory.Counter.onButton(button, false))
        //    //    {
        //    //        _parent._m_Program_Memory.AppendCounterString();
        //    //        _parent._m_Program_Memory.Counter.Increment();
        //    //        _parent.setReceiver("PROG_N");
        //    //    }
        //    //    return "Nothing";
        //    //}
        //    //if (_parent.Registers.isActive)
        //    //{

        //    //    if (_parent.Registers.onButton(button))
        //    //    {
        //    //        _parent.Registers.AppendRegisterString();
        //    //        _parent.Program.Counter.Increment();
        //    //        _parent.setReceiver("PROG_N");
        //    //    }
        //    //    return "Nothing";
        //    //}
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func F":
        //            _parent.setReceiver("PROG_F");
        //            return "Nothing";
        //        case "Func A":
        //            _parent.setReceiver("PROG_A");
        //            return "Nothing";
        //        case "Mode":
        //            //_parent._m_Program_Memory.SetCurrentLine("RAD");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X<Y GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X==Y GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X>=Y GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "S/P":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X!=Y GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent._m_Program_Memory.SetCurrentLine("KM->X ");
        //            //_parent.Registers.ActivateEntry(Register_Memory.None);
        //            return "Nothing";
        //        case "X->M":
        //            //_parent._m_Program_Memory.SetCurrentLine("KX->M ");
        //            //_parent.Registers.ActivateEntry(Register_Memory.None);
        //            return "Nothing";

        //        case "/-/":
        //            _parent.setReceiver("AUTO_N");
        //            _parent.Shutdown();
        //            return "Nothing";

        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
