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
    // Implements a generic empty receiver for Splash mode - it is for simulator only
    //
    public class Receiver_Splash: Receiver
    {
        private DateTime _splashed = DateTime.MinValue;

        public Receiver_Splash(MK52_Host parent)
            : base( parent)
        {
            Moniker = "Splash";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.clearScreen();
            lm.showSplash();
            lm.forcePaint();
            _splashed = DateTime.Now;
        }

        public override byte tick(byte scancode)
        {
            while (true)
            {
                TimeSpan ts = DateTime.Now.Subtract(_splashed);
                if (ts.Milliseconds > 500) break;
            }
            if (_return_to == "Undefined") return 0;
            if (_return_to.Length <= 0 || _return_to.StartsWith( "Font")) _return_to = "AUTO_N";
            _parent.getFunctions().requestNextReceiver(_return_to);
            return 0;
        }
    }
}
