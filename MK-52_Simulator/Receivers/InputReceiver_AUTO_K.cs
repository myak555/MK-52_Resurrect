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
        public InputReceiver_AUTO_K(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_K";
            _displayName = " K ";
        }

        public override void onButton(RPN_Button button)
        {
            if (_parent.Registers.isActive)
            {
                _parent.Registers.onButton(button);
                return;
            }
            switch (button.Moniker)
            {
                // Column 1
                case "Func F":
                    _parent.setReceiver("AUTO_F");
                    return;
                case "Func A":
                    _parent.setReceiver("AUTO_A");
                    return;
                case "Mode":
                    _parent.SwapDegreeMode();
                    return;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    _parent.setReceiver("AUTO_N");
                    return;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    _parent.setReceiver("AUTO_N");
                    return;
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    _parent.setReceiver("AUTO_N");
                    return;

                // Column 2
                case "M->X":
                    _parent.Registers.ActivateEntry(RPN_Registers.ExtendedToStack);
                    return;
                case "X->M":
                    _parent.Registers.ActivateEntry(RPN_Registers.StackToExtended);
                    return;

                // Column 3
                case "7":
                    _parent.executeFunction("[X]");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "4":
                    _parent.executeFunction("|X|");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "1":
                    _parent.executeFunction("e");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "0":
                    _parent.setReceiver("AUTO_N"); //NOP
                    return;

                // Column 4
                case "8":
                    _parent.executeFunction("{X}");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "5":
                    _parent.executeFunction("SIGN");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "2":
                    _parent.executeFunction("LOG");
                    _parent.setReceiver("AUTO_N");
                    return;
                case ".":
                    _parent.executeFunction("AND");
                    _parent.setReceiver("AUTO_N");
                    return;

                // Column 5
                case "9":
                    _parent.executeFunction("MAX");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "6":
                    _parent.executeFunction("<-DM");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "3":
                    _parent.executeFunction("<-DMS");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "/-/":
                    _parent.executeFunction("OR");
                    _parent.setReceiver("AUTO_N");
                    return;

                // Column 6
                case "-":
                    // TODO: root
                    _parent.setReceiver("AUTO_N");
                    return;
                case "+":
                    _parent.executeFunction("DM->");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "Swap":
                    _parent.executeFunction("DMS->");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "EE":
                    _parent.executeFunction("XOR");
                    _parent.setReceiver("AUTO_N");
                    return;

                // Column 7
                case "/":
                    //TODO;
                    _parent.setReceiver("AUTO_N");
                    return;
                case "*":
                    //TODO Quadratic
                    _parent.setReceiver("AUTO_N");
                    return;
                case "Enter":
                    _parent.executeFunction("RAND");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "Cx":
                    _parent.executeFunction( "NOT");
                    _parent.setReceiver("AUTO_N");
                    return;
                default:
                    return;
            }                
        }
    }
}
