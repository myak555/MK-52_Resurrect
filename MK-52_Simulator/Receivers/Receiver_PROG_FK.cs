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
    // Implements a receiver for FK-modified buttons
    //
    public class Receiver_PROG_FK : Receiver_PROG
    {
        public Receiver_PROG_FK(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_FK";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE("FK ");
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
                    return _rpnf.requestNextReceiver("PROG_K");
                case 3:
                    return _rpnf.requestNextReceiver("PROG_FA");
                case 4:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_DMOD_DEG);
                    break;

                // Column 6
                case 27:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_POWYX);
                    break;

                // Column 7
                case 32:
                    // Clear FK mode
                    return _rpnf.requestNextReceiver("PROG_N");
                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("PROG_N");
                    return 33;
                default: // all other buttons do nothing, keeping FK-mode
                    return 0;
            }
            _rpnf.progMem.incrementCounter();
            return _rpnf.requestNextReceiver("PROG_N");
        }
    }
}
