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
    public class InputReceiver_AUTO_N: RPN_InputReceiver
    {
        public InputReceiver_AUTO_N(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_N";
        }

        public override bool onButton(RPN_Button button)
        {
            if (_parent.Program.isAddressEntry)
            {
                _parent.Program.AddDigitToAddress(button.Moniker);
                return true;
            }
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
                    return true;

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return true;
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return true;
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    return true;
                case "S/P":
                    _parent.setReceiver("AUTO_R");
                    return true;

                // Column 2
                case "M->X":
                    _parent.setReceiver("AUTO_MX");
                    return true;
                case "X->M":
                    _parent.setReceiver("AUTO_XM");
                    return true;
                case "GOTO":
                    _parent.Program.Counter.ActivateEntry();
                    return true;
                case "GOSUB":
                    _parent.executeCodeStep();
                    return true;
                default:
                    _parent.Stack.onButton(button.Moniker);
                    return true;
            }                
        }
    }
}
