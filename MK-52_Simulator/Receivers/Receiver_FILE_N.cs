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
    // Implements a generic empty receiver
    //
    public class Receiver_FILE_N: Receiver_FILE
    {
        public Receiver_FILE_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FILE_N";
        }

        public override void activate(string prevReceiver)
        {
            _nLinesShown = LCD_Manager.SCREEN_ROWS - 1;
            base.activate(prevReceiver);
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
                case 3:
                    _rpnf.requestNextReceiver("FILE_A");
                    return 0;

                // Column 1
                case 5:
                    _rpnf.execute(RPN_Functions.FUNC_NEXTFILE);
                    break;
                case 6:
                    _rpnf.execute(RPN_Functions.FUNC_PREVFILE);
                    break;
                case 7:
                    _rpnf.execute(RPN_Functions.FUNC_UPDIR);
                    break;
                case 8:
                    _rpnf.execute(RPN_Functions.FUNC_STEPIN);
                    break;

                // Column 2
                case 9:
                    _rpnf.execute(RPN_Functions.FUNC_LOAD);
                    _rpnf.requestNextReceiver("PROG_N");
                    return 0;
                case 10:
                    _rpnf.requestNextReceiver("File_Overwrite");
                    return 0;
                case 11:
                    // find program TODO
                    break;
                case 12:
                    _rpnf.requestNextReceiver("File_Name");
                    return 0;

                // Column 3-5 - do nothing (for now)

                // Column 6
                case 28:
                    _rpnf.requestNextReceiver("File_MkDir");
                    break;

                // Column 7
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_STEPIN);
                    break;
                case 32:
                    _rpnf.requestNextReceiver("File_Delete");
                    return 0;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("OFF");
                    return 33;

                default: // all other buttons do nothing (for now)
                    return 0;
            }
            return base.tick(0);
        }
    }
}
