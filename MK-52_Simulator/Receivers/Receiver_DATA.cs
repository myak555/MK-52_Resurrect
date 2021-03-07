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
    // Implements a generic receiver for all keys in DATA mode
    //
    public class Receiver_DATA: Receiver
    {
        public Receiver_DATA(MK52_Host parent)
            : base( parent)
        {
            Moniker = "DATA";
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
            Extended_Memory em = _parent._m_Extended_Memory;
            lm.clearScreen();
            lm.outputStatus(
                _parent._m_Program_Memory.getCounter(),
                em.getCounter(),
                "MEM",
                "   ");
            int cnt = (int)em.getCounter();
            for (int i = 10, j = cnt; i >= 0; i--, j--)
            {
                string s = em.toString("", j);
                lm.outputTerminalLine((uint)i, s);
            }
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            LCD_Manager lm = _parent._m_Hardware_LCD;
            Extended_Memory em = _parent._m_Extended_Memory;
            lm.updateStatusPC(_parent._m_Program_Memory.getCounter());
            lm.updateStatusMC(em.getCounter());
            //lm.updateStatusDMODE(_parent._m_RPN_Stack.getDModeName());
            int cnt = (int)em.getCounter();
            for (int i = 10, j = cnt; i >= 0; i--, j--)
            {
                string s = em.toString("", j);
                lm.updateTerminalLine((uint)i, s);
            }
            lm.requestUpdate();
            return 0;
        }
    }
}
