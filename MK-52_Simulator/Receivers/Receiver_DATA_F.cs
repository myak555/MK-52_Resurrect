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
    // Implements a receiver for F-modified list
    //
    public class Receiver_DATA_F: Receiver_DATA
    {
        public Receiver_DATA_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "DATA_F";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" F ");
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
                    return _rpnf.requestNextReceiver("DATA_K");
                case 3:
                    return _rpnf.requestNextReceiver("DATA_A");
                case 4:
                    //_parent._m_RPN_Stack.toggleAngleMode();
                    //return base.tick(0);
                    return 0;

                // Column 1
                case 5:
                    for( int i=0; i<9; i++)
                        _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;
                case 6:
                    for (int i = 0; i < 9; i++)
                        _rpnf.execute(RPN_Functions.FUNC_DECREMENT_MC);
                    break;
                //case 7:
                //    TODO: goto to the next entry
                //    break;
                // Column 2 does nothing (for now)
                // Column 3 does nothing (for now)
                // Column 4 does nothing (for now)

                // Column 5
                case 24:
                    return _rpnf.requestNextReceiver("AUTO_N");

                // Column 6
                case 28:
                    return _rpnf.requestNextReceiver("PROG_N");

                // Column 7
                case 32:
                    // Clear F mode
                    break;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("DATA_N");
                    return 33;

                default: // all other buttons do nothing, keeping F-mode
                    return 0;
            }
            return _rpnf.requestNextReceiver("DATA_N");
        }
    }
}
