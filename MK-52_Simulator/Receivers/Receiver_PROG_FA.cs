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
    public class Receiver_PROG_FA : Receiver_PROG
    {
        public Receiver_PROG_FA(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_FA";
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
                    return _rpnf.requestNextReceiver("PROG_FK");
                case 3:
                    return _rpnf.requestNextReceiver("PROG_A");
                case 4:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_DMOD_DEG);
                    break;

                // Column 1
                case 5:
                    for( int i=0; i<9; i++)
                        _rpnf.progMem.incrementCounter();
                    return base.tick(0);
                case 6:
                    for (int i = 0; i < 9; i++)
                        _rpnf.progMem.decrementCounter();
                    return base.tick(0);
                case 7:
                    _rpnf.progMem.resetCounter();
                    return _rpnf.requestNextReceiver("PROG_N");

                // Column 2
                case 11:
                    return _rpnf.requestNextReceiver("ADDRESS_PC", "PROG_N");
                case 12:
                    _rpnf.progMem.setCounterToBottom();
                    return _rpnf.requestNextReceiver("PROG_N");

                // Column 7
                case 31:
                    _rpnf.progMem.updateLine(_rpnf.rpnStack.X.toString());
                    break;
                case 32:
                    // Clear FA mode
                    return _rpnf.requestNextReceiver("PROG_N");
                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("PROG_N");
                    return 33;
                default: // all other buttons do nothing, keeping FA-mode
                    return 0;
            }
            _rpnf.progMem.incrementCounter();
            return _rpnf.requestNextReceiver("PROG_N");
        }
    }
}
