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
    public class Receiver_FILE_A: Receiver_FILE
    {
        public Receiver_FILE_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FILE_A";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" A ");
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
                case 1:
                    _rpnf.requestNextReceiver("FILE_F");
                    return 0;
                case 2:
                    _rpnf.requestNextReceiver("FILE_K");
                    return 0;
                case 4:
                    // _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    // base.tick(0);
                    return 0;

                // Column 1 does nothing (for now)
                // Column 2 does nothing (for now)
                // Column 3 does nothing (for now)
                // Column 4 does nothing (for now)
                // Column 5 does nothing (for now)

                // Column 6
                case 28:
                    _rpnf.requestNextReceiver("DATA_N");
                    return 0;

                // Column 7
                case 32:
                case 33:
                    _rpnf.requestNextReceiver("FILE_N");
                    return 33;
                default: // all other buttons do nothing, keeping A-mode
                    return 0;
            }
            //_rpnf.requestNextReceiver("DATA_N");
            //return 0;
        }
    }
}
