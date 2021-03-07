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
    // Implements a generic receiver for all keys in PROG mode
    //
    public class Receiver_PROG: Receiver
    {
        public Receiver_PROG(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG";
        }

        public override void activate( string prevReceiver)
        {
            base.activate(prevReceiver);
            if (prevReceiver.StartsWith( Moniker))
            {
                tick(0);
                return;
            }
            LCD_Manager lm = _parent._m_Hardware_LCD;
            Program_Memory pm = _parent._m_Program_Memory;
            lm.clearScreen();
            lm.outputStatus(
                _parent._m_Extended_Memory.getCounter(),
                pm.getCounter(),
                pm.getEModeName(),
                "   ");
            int display_PC = (int)pm.getCounter();
            string[] _displayLines = pm.getPreviousLines(LCD_Manager.SCREEN_ROWS - 1);
            for (int i = 10, j = 0, k = display_PC; i >= 0; i--, j++, k--)
            {
                if (k < 0)
                {
                    lm.eraseTerminalLine((uint)i);
                    continue;
                }
                string s = k.ToString("0000");
                s += (k == display_PC) ? "> " : "  ";
                lm.outputTerminalLine((uint)i, s + _displayLines[j]);
            }
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            LCD_Manager lm = _parent._m_Hardware_LCD;
            Program_Memory pm = _parent._m_Program_Memory;
            lm.updateStatusPC(pm.getCounter());
            lm.updateStatusMC(_parent._m_Extended_Memory.getCounter());
            lm.updateStatusDMODE(pm.getEModeName());
            int display_PC = (int)pm.getCounter();
            string[] _displayLines = pm.getPreviousLines(LCD_Manager.SCREEN_ROWS - 1);
            for (int i = 10, j = 0, k = display_PC; i >= 0; i--, j++, k--)
            {
                if (k < 0)
                {
                    lm.eraseTerminalLine((uint)i);
                    continue;
                }
                string s = k.ToString("0000");
                s += (k == display_PC) ? "> " : "  ";
                lm.updateTerminalLine((uint)i, s + _displayLines[j]);
            }
            lm.requestUpdate();
            return 0;
        }
    }
}
