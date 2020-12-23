using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a register entry 0 to E or L0 to L3
    //
    public class InputReceiver_AUTO_XM: RPN_InputReceiver
    {
        public InputReceiver_AUTO_XM(RPN_Calculator parent, RPN_Screen display)
            : base( parent, display)
        {
            Moniker = "AUTO_XM";
            DisplayName = "X-->M";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("AUTO_F");
                    return true;
                case "Func K":
                    _parent.setReceiver("AUTO_K");
                    return true;
                case "Func A":
                    _parent.setReceiver("AUTO_A");
                    return true;
                case "Mode":
                    _parent.SwapDegreeMode();
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "0":
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                case ".":
                case "/-/":
                case "EE":
                case "Cx":
                case "Enter":
                case "*":
                case "M->X":
                case "X->M":
                case "GOTO":
                case "GOSUB":
                    _parent.Stack.SetMemoryFromStack(button.Register);
                    _parent.setReceiver("AUTO_N");
                    return true;
                default:
                    return false;
            }
        }
    }
}
