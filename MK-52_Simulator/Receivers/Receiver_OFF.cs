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
    // Implements a generic empty receiver for OFF mode - switching on only by Cx button
    //
    public class Receiver_OFF: Receiver
    {
        public Receiver_OFF(MK52_Host parent)
            : base( parent)
        {
            Moniker = "OFF";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            _parent.shutdown();
        }

        public override byte tick(byte scancode)
        {
            if (scancode != 32) return 0;
            if (_return_to.Length <= 0 || _return_to.StartsWith("Font")) _return_to = "AUTO_N";
            _parent.getFunctions().requestNextReceiver( "Splash", _return_to);
            return 0;
        }
    }
}
