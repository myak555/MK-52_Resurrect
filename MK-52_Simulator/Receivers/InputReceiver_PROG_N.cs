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
    public class InputReceiver_PROG_N: Receiver
    {
        public InputReceiver_PROG_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_N";
        }

        //public override string tick(MK52_Button button)
        //{
        //    //if ( _parent._m_Program_Memory.Number.isActive)
        //    //{
        //    //    if (button.Moniker != "Enter")
        //    //    {
        //    //        _parent._m_Program_Memory.Number.tick(button);
        //    //        return "Nothing";
        //    //    }
        //    //    _parent._m_Program_Memory.SetCurrentLine( _parent._m_Program_Memory.Number.ToString().Trim());
        //    //    _parent._m_Program_Memory.Counter.Increment();
        //    //    _parent._m_Program_Memory.Number.Clear();
        //    //    return "Nothing";
        //    //}
        //    //if (_parent._m_Program_Memory.Counter.isActive)
        //    //{

        //    //    if (_parent._m_Program_Memory.Counter.onButton(button, false))
        //    //    {
        //    //        _parent._m_Program_Memory.AppendCounterString();
        //    //        _parent._m_Program_Memory.Counter.Increment();
        //    //    }
        //    //    return "Nothing";
        //    //}
        //    //if (_parent.Registers.isActive)
        //    //{

        //    //    if (_parent.Registers.onButton(button))
        //    //    {
        //    //        _parent.Registers.AppendRegisterString();
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
        //        case "Func A":
        //            _parent.setReceiver("PROG_A");
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.Counter.Decrement();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.SetCurrentLine( "RETURN");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //        case "S/P":
        //            //_parent._m_Program_Memory.SetCurrentLine("STOP");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent._m_Program_Memory.SetCurrentLine("M->X ");
        //            //_parent.Registers.ActivateEntry( Register_Memory.None);
        //            return "Nothing";
        //        case "X->M":
        //            //_parent._m_Program_Memory.SetCurrentLine("X->M ");
        //            //_parent.Registers.ActivateEntry( Register_Memory.None);
        //            return "Nothing";
        //        case "GOTO":
        //            //_parent._m_Program_Memory.SetCurrentLine("GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "GOSUB":
        //            //_parent._m_Program_Memory.SetCurrentLine("GOSUB ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Number entry (columns 3-5)
        //        case "0":
        //        case "1":
        //        case "2":
        //        case "3":
        //        case "4":
        //        case "5":
        //        case "6":
        //        case "7":
        //        case "8":
        //        case "9":
        //        case ".":
        //        case "EE":
        //            //_parent._m_Program_Memory.Number.tick(button);
        //            return "Nothing";

        //        // Operations
        //        default:
        //            //_parent._m_Program_Memory.SetCurrentLine( button.Moniker);
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //    }            
        //}

        //public override string DisplayName
        //{
        //    get
        //    {
        //        //if (_parent._m_Program_Memory.Number.isActive) return _parent._m_Program_Memory.Number.DisplayName;
        //        //if (_parent._m_Program_Memory.Counter.isActive) return "PC?";
        //        //if (_parent.Registers.isActive) return "RG?";
        //        return _displayName;
        //    }
        //}
    }
}
