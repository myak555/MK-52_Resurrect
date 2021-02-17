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
    // Implements a receiver for F-modified buttons
    //
    public class InputReceiver_PROG_F: Receiver
    {
        public InputReceiver_PROG_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_F";
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
        //    switch (button.Moniker)
        //    {
        //        case "Func K":
        //            _parent.setReceiver("PROG_K");
        //            return "Nothing";
        //        case "Mode":
        //            //_parent._m_Program_Memory.SetCurrentLine("DEG");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "Func A":
        //            _parent.setReceiver("PROG_A");
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X<0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X==0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X>=0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "S/P":
        //            //_parent._m_Program_Memory.SetCurrentLine("IFNOT X!=0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent._m_Program_Memory.SetCurrentLine("WHILE L0>0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "X->M":
        //            //_parent._m_Program_Memory.SetCurrentLine("WHILE L1>0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "GOTO":
        //            //_parent._m_Program_Memory.SetCurrentLine("WHILE L2>0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "GOSUB":
        //            //_parent._m_Program_Memory.SetCurrentLine("WHILE L3>0 GOTO ");
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";

        //        // Column 3
        //        case "7":
        //            //_parent._m_Program_Memory.SetCurrentLine("SIN");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "4":
        //            //_parent._m_Program_Memory.SetCurrentLine("arcSIN");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "1":
        //            //_parent._m_Program_Memory.SetCurrentLine("EXP");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "0":
        //            //_parent._m_Program_Memory.SetCurrentLine("10^X");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        // Column 4
        //        case "8":
        //            //_parent._m_Program_Memory.SetCurrentLine("COS");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "5":
        //            //_parent._m_Program_Memory.SetCurrentLine("arcCOS");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "2":
        //            //_parent._m_Program_Memory.SetCurrentLine("LG");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case ".":
        //            //_parent._m_Program_Memory.SetCurrentLine("Rotate");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        // Column 5
        //        case "9":
        //            //_parent._m_Program_Memory.SetCurrentLine("TG");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //        case "6":
        //            //_parent._m_Program_Memory.SetCurrentLine("arcTG");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "3":
        //            //_parent._m_Program_Memory.SetCurrentLine("LN");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "/-/":
        //            _parent.setReceiver("AUTO_N");
        //            return "Nothing";

        //        // Column 6
        //        case "-":
        //            //_parent._m_Program_Memory.SetCurrentLine("SQRT");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "+":
        //            //_parent._m_Program_Memory.SetCurrentLine("pi");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "Swap":
        //            //_parent._m_Program_Memory.SetCurrentLine("X^Y");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "EE":
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";

        //        // Column 7
        //        case "/":
        //            //_parent._m_Program_Memory.SetCurrentLine("1/X");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "*":
        //            //_parent._m_Program_Memory.SetCurrentLine("X^2");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "Enter":
        //            //_parent._m_Program_Memory.SetCurrentLine("Bx");
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        case "Cx":
        //            _parent.setReceiver("PROG_N");
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
