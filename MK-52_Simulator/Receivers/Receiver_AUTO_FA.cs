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
    // Implements a receiver for FA-modified buttons
    //
    public class Receiver_AUTO_FA : Receiver_AUTO
    {
        public Receiver_AUTO_FA(MK52_Host parent)
            : base(parent)
        {
            Moniker = "AUTO_FA";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE("FA ");
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch (scancode)
            {
                case 0: // keyboard inactive
                    return 0;

                // Column 0
                case 2:
                    return _rpnf.requestNextReceiver("AUTO_FK");
                case 3:
                    return _rpnf.requestNextReceiver("AUTO_A");
                case 4:
                    _parent._m_RPN_Stack.toggleAngleMode();
                    return base.tick(0);

                // Column 7
                case 29:
                    _parent._m_Hardware_KBD.LEDOn = true;
                    break;
                case 30:
                    _parent._m_Hardware_KBD.LEDOn = false;
                    break;
                case 32:
                    break;
                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("AUTO_N");
                    return 33;
                default: // all other buttons do nothing, keeping FA-mode
                    return 0;
            }
            return _rpnf.requestNextReceiver("AUTO_N");
        }
    }
}
