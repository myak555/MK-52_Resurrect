using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver
    //
    public class InputReceiver_AUTO_F: RPN_InputReceiver
    {
        public InputReceiver_AUTO_F(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_F";
            DisplayName = "  F  ";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func K":
                    _parent.setReceiver("AUTO_K");
                    return true;
                case "Func A":
                    _parent.setReceiver("AUTO_A");
                    return true;
                case "Mode":
                    _parent.SwapDegreeMode();
                    return true;

                // Column 1
                // Does nothing

                // Column 2
                // Does nothing

                // Column 3
                case "7":
                    _parent.executeFunction("SIN");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "4":
                    _parent.executeFunction("arcSIN");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "1":
                    _parent.executeFunction("EXP");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "0":
                    _parent.executeFunction("10^X");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 4
                case "8":
                    _parent.executeFunction("COS");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "5":
                    _parent.executeFunction("arcCOS");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "2":
                    _parent.executeFunction("LG");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case ".":
                    _parent.executeFunction("Rotate");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 5
                case "9":
                    _parent.executeFunction("TG");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "6":
                    _parent.executeFunction("arcTG");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "3":
                    _parent.executeFunction("LN");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 6
                case "-":
                    _parent.executeFunction("SQRT");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "+":
                    _parent.executeFunction("pi");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Swap":
                    _parent.executeFunction("X^Y");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "EE":
                    _parent.setReceiver("PROG_N");
                    return true;

                // Column 7
                case "/":
                    _parent.executeFunction("1/X");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "*":
                    _parent.executeFunction("X^2");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Enter":
                    _parent.executeFunction("Bx");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Cx":
                    _parent.setReceiver("AUTO_N");
                    return true;
                default:
                    return false;
            }                
        }
    }
}
