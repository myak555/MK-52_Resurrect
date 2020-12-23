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
    public class InputReceiver_OFF: RPN_InputReceiver
    {
        private string _previousReceiver = "AUTO_N";

        public InputReceiver_OFF(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "OFF";
        }

        public override bool onButton(RPN_Button button)
        {
            if (button.Moniker != "Cx") return false;
            _parent.setReceiver(_previousReceiver);
            return true;
        }

        public override void onSet()
        {
            _previousReceiver = _parent.CurrentReceiver.Moniker;
        }
    }
}
