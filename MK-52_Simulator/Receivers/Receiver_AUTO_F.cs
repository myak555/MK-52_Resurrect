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
    public class Receiver_AUTO_F : Receiver_AUTO
    {
        public Receiver_AUTO_F(MK52_Host parent)
            : base(parent)
        {
            Moniker = "AUTO_F";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" F ");
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            if (scancode == 0) return 0;
            _parent.setReceiver("AUTO_N");
            return 0;
        }

        //public override string tick(MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func K":
        //            return "AUTO_K";
        //        case "Func A":
        //            return "AUTO_A";
        //        case "Mode":
        //            _parent._m_RPN_Stack.toggleAngleMode();
        //            return "Nothing";

        //        // Column 1
        //        // Does nothing

        //        // Column 2
        //        // Does nothing

        //        // Column 3
        //        case "7":
        //            //_parent.executeFunction("SIN");
        //            return "AUTO_N";
        //        case "4":
        //            //_parent.executeFunction("arcSIN");
        //            return "AUTO_N";
        //        case "1":
        //            //_parent.executeFunction("EXP");
        //            return "AUTO_N";
        //        case "0":
        //            //_parent.executeFunction("10^X");
        //            return "AUTO_N";

        //        // Column 4
        //        case "8":
        //            //_parent.executeFunction("COS");
        //            return "AUTO_N";
        //        case "5":
        //            //_parent.executeFunction("arcCOS");
        //            return "AUTO_N";
        //        case "2":
        //            //_parent.executeFunction("LG");
        //            return "AUTO_N";
        //        case ".":
        //            //_parent.executeFunction("Rotate");
        //            return "AUTO_N";

        //        // Column 5
        //        case "9":
        //            //_parent.executeFunction("TG");
        //            return "AUTO_N";
        //        case "6":
        //            //_parent.executeFunction("arcTG");
        //            return "AUTO_N";
        //        case "3":
        //            //_parent.executeFunction("LN");
        //            return "AUTO_N";
        //        case "/-/":
        //            return "AUTO_N";

        //        // Column 6
        //        case "-":
        //            //_parent.executeFunction("SQRT");
        //            return "AUTO_N";
        //        case "+":
        //            //_parent.executeFunction("pi");
        //            return "AUTO_N";
        //        case "Swap":
        //            //_parent.executeFunction("X^Y");
        //            return "AUTO_N";
        //        case "EE":
        //            return "PROG_N";

        //        // Column 7
        //        case "/":
        //            //_parent.executeFunction("1/X");
        //            return "AUTO_N";
        //        case "*":
        //            //_parent.executeFunction("X^2");
        //            return "AUTO_N";
        //        case "Enter":
        //            //_parent.executeFunction("Bx");
        //            return "AUTO_N";
        //        case "Cx":
        //            return "AUTO_N";
        //        default:
        //            return "Nothing";
        //    }                
        //}
    }
}
