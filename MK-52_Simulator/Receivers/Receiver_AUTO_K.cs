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
    // Implements a receiver for K-modified buttons
    //
    public class Receiver_AUTO_K : Receiver_AUTO
    {
        public Receiver_AUTO_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_K";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" K ");
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
        //    //if (_parent.Registers.isActive)
        //    //{
        //    //    _parent.Registers.onButton(button);
        //    //    return "Nothing";
        //    //}
        //    switch (button.Moniker)
        //    {
        //        // Column 1
        //        case "Func F":
        //            return "AUTO_F";
        //        case "Func A":
        //            return "AUTO_A";
        //        case "Mode":
        //            _parent._m_RPN_Stack.toggleAngleMode();
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent.Memory.Counter.Increment();
        //            return "AUTO_N";
        //        case "<-":
        //            //_parent.Memory.Counter.Decrement();
        //            return "AUTO_N";
        //        case "B/O":
        //            //_parent.Memory.Counter.Set(0);
        //            return "AUTO_N";

        //        // Column 2
        //        case "M->X":
        //            //_parent.Registers.ActivateEntry(Register_Memory.ExtendedToStack);
        //            return "Nothing";
        //        case "X->M":
        //            //_parent.Registers.ActivateEntry(Register_Memory.StackToExtended);
        //            return "Nothing";

        //        // Column 3
        //        case "7":
        //            //_parent.executeFunction("[X]");
        //            return "AUTO_N";
        //        case "4":
        //            //_parent.executeFunction("|X|");
        //            return "AUTO_N";
        //        case "1":
        //            //_parent.executeFunction("e");
        //            return "AUTO_N";
        //        case "0":
        //            return "AUTO_N"; // NOP

        //        // Column 4
        //        case "8":
        //            //_parent.executeFunction("{X}");
        //            return "AUTO_N";
        //        case "5":
        //            //_parent.executeFunction("SIGN");
        //            return "AUTO_N";
        //        case "2":
        //            //_parent.executeFunction("LOG");
        //            return "AUTO_N";
        //        case ".":
        //            //_parent.executeFunction("AND");
        //            return "AUTO_N";

        //        // Column 5
        //        case "9":
        //            //_parent.executeFunction("MAX");
        //            return "AUTO_N";
        //        case "6":
        //            //_parent.executeFunction("<-DM");
        //            return "AUTO_N";
        //        case "3":
        //            //_parent.executeFunction("<-DMS");
        //            return "AUTO_N";
        //        case "/-/":
        //            //_parent.executeFunction("OR");
        //            return "AUTO_N";

        //        // Column 6
        //        case "-":
        //            // TODO: root
        //            return "AUTO_N";
        //        case "+":
        //            //_parent.executeFunction("DM->");
        //            return "AUTO_N";
        //        case "Swap":
        //            //_parent.executeFunction("DMS->");
        //            return "AUTO_N";
        //        case "EE":
        //            //_parent.executeFunction("XOR");
        //            return "AUTO_N";

        //        // Column 7
        //        case "/":
        //            //TODO;
        //            return "AUTO_N";
        //        case "*":
        //            //TODO Quadratic
        //            return "AUTO_N";
        //        case "Enter":
        //            //_parent.executeFunction("RAND");
        //            return "AUTO_N";
        //        case "Cx":
        //            //_parent.executeFunction( "NOT");
        //            return "AUTO_N";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
