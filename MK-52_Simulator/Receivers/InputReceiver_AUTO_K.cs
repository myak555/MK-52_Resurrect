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
    public class InputReceiver_AUTO_K: RPN_InputReceiver
    {
        public InputReceiver_AUTO_K(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_K";
            DisplayName = "  K  ";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 1
                case "Func F":
                    _parent.setReceiver("AUTO_F");
                    return true;
                case "Func A":
                    _parent.setReceiver("AUTO_A");
                    return true;
                case "Mode":
                    _parent.SwapDegreeMode();
                    return true;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 2
                // Does nothing

                // Column 3
                case "7":
                    _parent.executeFunction("[X]");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "4":
                    _parent.executeFunction("|X|");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "1":
                    _parent.executeFunction("e");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "0":
                    _parent.setReceiver("AUTO_N"); //NOP
                    return true;

                // Column 4
                case "8":
                    _parent.executeFunction("{X}");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "5":
                    _parent.executeFunction("SIGN");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "2":
                    _parent.executeFunction("LOG");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case ".":
                    _parent.executeFunction("AND");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 5
                case "9":
                    _parent.executeFunction("MAX");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "6":
                    _parent.executeFunction("<-DM");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "3":
                    _parent.executeFunction("<-DMS");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "/-/":
                    _parent.executeFunction("OR");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 6
                case "-":
                    // TODO: root
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "+":
                    _parent.executeFunction("DM->");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Swap":
                    _parent.executeFunction("DMS->");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "EE":
                    _parent.executeFunction("XOR");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 7
                case "/":
                    //TODO;
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "*":
                    //TODO Quadratic
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Enter":
                    _parent.executeFunction("RAND");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Cx":
                    _parent.executeFunction( "NOT");
                    _parent.setReceiver("AUTO_N");
                    return true;
                default:
                    return false;
            }                
        }
    }
}
