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
    public class Receiver_FILE_F: Receiver_FILE
    {
        public Receiver_FILE_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FILE_F";
        }

        public override void activate(string prevReceiver)
        {
            _nLinesShown = LCD_Manager.SCREEN_ROWS - 1;
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
                    return _rpnf.requestNextReceiver("FILE_K");
                case 3:
                    return _rpnf.requestNextReceiver("FILE_A");

                // Column 1
                case 5:
                    for (int i = 0; i < 9; i++)
                        _rpnf.execute(RPN_Functions.FUNC_NEXTFILE);
                    break;
                case 6:
                    for (int i = 0; i < 9; i++)
                        _rpnf.execute(RPN_Functions.FUNC_PREVFILE);
                    break;

                // Column 2
                case 9:
                    _rpnf.execute(RPN_Functions.FUNC_LOADDATA);
                    return _rpnf.requestNextReceiver("DATA_N");
                case 10:
                    return _rpnf.requestNextReceiver("File_Overwrite_Data");
                case 12:
                    return _rpnf.requestNextReceiver("File_Data");

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
                    _rpnf.requestNextReceiver("FILE_N");
                    return 33;

                default: // all other buttons do nothing, keeping F-mode
                    return 0;
            }
            return _rpnf.requestNextReceiver("FILE_N");
        }
    }
}
