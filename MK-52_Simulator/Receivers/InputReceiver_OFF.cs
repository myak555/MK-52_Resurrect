using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver for OFF mode - switching on only by Cx button
    //
    public class InputReceiver_OFF: RPN_InputReceiver
    {
        private string _previousReceiver = "AUTO_N";

        public InputReceiver_OFF(MK52_Host parent)
            : base( parent)
        {
            Moniker = "OFF";
        }

        public override string tick(RPN_Button button)
        {
            if (button.Moniker != "Cx") return "Nothing";
            _parent.setDisplay("AUTO");
            return "AUTO_N";
        }

        public override void activate()
        {
            _previousReceiver = _parent.current_Receiver.Moniker;
        }
    }
}
