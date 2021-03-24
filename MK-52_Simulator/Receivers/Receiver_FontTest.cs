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
    // Test-only; shows all the characters
    //
    public class Receiver_FontTest: Receiver
    {
        public Receiver_FontTest(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FontTest";
        }

        public override void activate( string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.clearScreen();
            for (int i = 0; i < 256; i++)
            {
                int x = (i % 29) * 11;
                int y = (i / 29) * 20;
                lm.outputChar(x, y, (byte)i, System.Drawing.Color.Orange, System.Drawing.Color.Black);
            }
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            if (scancode != 32) return 0;
            return _parent.getFunctions().requestNextReceiver( _return_to);
        }
    }
}
