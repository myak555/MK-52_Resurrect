using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a receiver for K-modified buttons
    //
    public class InputReceiver_AUTO_K: RPN_InputReceiver
    {
        public InputReceiver_AUTO_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_K";
            _displayName = " K ";
        }

        public override string tick(RPN_Button button)
        {
            if (_parent.Registers.isActive)
            {
                _parent.Registers.onButton(button);
                return "Nothing";
            }
            switch (button.Moniker)
            {
                // Column 1
                case "Func F":
                    return "AUTO_F";
                case "Func A":
                    return "AUTO_A";
                case "Mode":
                    _parent.SwapDegreeMode();
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    return "AUTO_N";
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    return "AUTO_N";
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    return "AUTO_N";

                // Column 2
                case "M->X":
                    _parent.Registers.ActivateEntry(RPN_Registers.ExtendedToStack);
                    return "Nothing";
                case "X->M":
                    _parent.Registers.ActivateEntry(RPN_Registers.StackToExtended);
                    return "Nothing";

                // Column 3
                case "7":
                    _parent.executeFunction("[X]");
                    return "AUTO_N";
                case "4":
                    _parent.executeFunction("|X|");
                    return "AUTO_N";
                case "1":
                    _parent.executeFunction("e");
                    return "AUTO_N";
                case "0":
                    return "AUTO_N"; // NOP

                // Column 4
                case "8":
                    _parent.executeFunction("{X}");
                    return "AUTO_N";
                case "5":
                    _parent.executeFunction("SIGN");
                    return "AUTO_N";
                case "2":
                    _parent.executeFunction("LOG");
                    return "AUTO_N";
                case ".":
                    _parent.executeFunction("AND");
                    return "AUTO_N";

                // Column 5
                case "9":
                    _parent.executeFunction("MAX");
                    return "AUTO_N";
                case "6":
                    _parent.executeFunction("<-DM");
                    return "AUTO_N";
                case "3":
                    _parent.executeFunction("<-DMS");
                    return "AUTO_N";
                case "/-/":
                    _parent.executeFunction("OR");
                    return "AUTO_N";

                // Column 6
                case "-":
                    // TODO: root
                    return "AUTO_N";
                case "+":
                    _parent.executeFunction("DM->");
                    return "AUTO_N";
                case "Swap":
                    _parent.executeFunction("DMS->");
                    return "AUTO_N";
                case "EE":
                    _parent.executeFunction("XOR");
                    return "AUTO_N";

                // Column 7
                case "/":
                    //TODO;
                    return "AUTO_N";
                case "*":
                    //TODO Quadratic
                    return "AUTO_N";
                case "Enter":
                    _parent.executeFunction("RAND");
                    return "AUTO_N";
                case "Cx":
                    _parent.executeFunction( "NOT");
                    return "AUTO_N";
                default:
                    return "Nothing";
            }                
        }
    }
}
