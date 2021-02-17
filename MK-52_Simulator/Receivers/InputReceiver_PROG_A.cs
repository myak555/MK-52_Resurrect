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
    public class InputReceiver_PROG_A: Receiver
    {
        public InputReceiver_PROG_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_A";
        }

        //public override string tick(MK52_Button button)
        //{
        //    //if (_parent._m_Program_Memory.Text.isActive)
        //    //{
        //    //    _parent._m_Program_Memory.Text.tick(button);
        //    //    if (!_parent._m_Program_Memory.Text.isActive)
        //    //    {
        //    //        _parent._m_Program_Memory.AppendCurrentLine(_parent._m_Program_Memory.Text.EntryText);
        //    //        _parent._m_Program_Memory.Counter.Increment();
        //    //        _parent.setReceiver("PROG_N");
        //    //    }
        //    //    return "Nothing";
        //    //}
        //    //if (_parent.Memory.Counter.isActive)
        //    //{

        //    //    if (_parent.Memory.Counter.onButton(button, false))
        //    //    {
        //    //        _parent.Program.AppendCurrentLine(_parent.Memory.Counter.entryResult.ToString("000"));
        //    //        _parent.Program.Counter.Increment();
        //    //    }
        //    //    return "Nothing";
        //    //}
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func F":
        //            _parent.setReceiver("PROG_F");
        //            return "Nothing";
        //        case "Func K":
        //            _parent.setReceiver("PROG_K");
        //            return "Nothing";
        //        case "Mode":
        //            //_parent._m_Program_Memory.SetCurrentLine("GRAD");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.SetCurrentLine("LT> ");
        //            //_parent._m_Program_Memory.Text.ActivateEntry();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.SetCurrentLine("LZ> ");
        //            //_parent._m_Program_Memory.Text.ActivateEntry();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.SetCurrentLine("LY> ");
        //            //_parent._m_Program_Memory.Text.ActivateEntry();
        //            return "Nothing";
        //        case "S/P":
        //            //_parent._m_Program_Memory.SetCurrentLine("LX> ");
        //            //_parent._m_Program_Memory.Text.ActivateEntry();
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent._m_Program_Memory.SetCurrentLine("AM->X ");
        //            //_parent.Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "X->M":
        //            //_parent._m_Program_Memory.SetCurrentLine("AX->M ");
        //            //_parent.Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Column 3
        //        case "1":
        //            //_parent._m_Program_Memory.SetCurrentLine("e");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";

        //        // Column 5
        //        case "/-/":
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        case "EE":
        //            _parent.setReceiver("LIST_N");
        //            return "Nothing";
        //        case "Cx":
        //            _parent.setReceiver("PROG_N");
        //            _parent.Shutdown();
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
