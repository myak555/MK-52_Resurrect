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
    public class Receiver_FILE_K: Receiver_FILE
    {
        public Receiver_FILE_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FILE_K";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" K ");
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
                case 3:
                    _rpnf.requestNextReceiver("FILE_A");
                    return 0;

                // Column 1 does nothing (for now)

                // Column 2
                case 9:
                    _rpnf.execute(RPN_Functions.FUNC_LOADALL);
                    _rpnf.requestNextReceiver("AUTO_N");
                    return 0;
                case 10:
                    _rpnf.requestNextReceiver("File_Overwrite_All");
                    return 0;
                case 12:
                    _rpnf.requestNextReceiver("File_All");
                    return 0;

                // Column 3 does nothing (for now)
                // Column 4 does nothing (for now)
                // Column 5 does nothing (for now)
                // Column 6 does nothing (for now)

                // Column 7
                case 32:
                    _rpnf.requestNextReceiver("Prog_Erase", "PROG_N");
                    return 0;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("FILE_N");
                    return 33;

                default: // all other buttons do nothing, keeping K-mode
                    return 0;
            }
            //_rpnf.requestNextReceiver("FILE_N");
            //return 0;
        }
    }
}
