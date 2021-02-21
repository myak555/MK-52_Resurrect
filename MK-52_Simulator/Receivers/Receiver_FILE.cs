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
    public class Receiver_FILE: Receiver
    {
        protected int _nLinesShown = 11;
   
        public Receiver_FILE(MK52_Host parent)
            : base( parent)
        {
            Moniker = "FILE";
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
            lm.clearScreen();
            lm.outputStatus(
                _parent._m_Program_Memory.getCounter(),
                _parent._m_Extended_Memory.getCounter(),
                "   ",
                "   ");

            string[] Lines = _parent._m_RPN_Functions.getOutputLines();
            _parent._m_Hardware_SD.getFolderListing(Lines, _nLinesShown, LCD_Manager.SCREEN_COLS - 1);
            for (int i = 0; i < _nLinesShown; i++)
            {
                lm.outputTerminalLine((uint)i, Lines[i]);
            }
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.updateStatusPC(_parent._m_Program_Memory.getCounter());
            lm.updateStatusMC(_parent._m_Extended_Memory.getCounter());
            //lm.updateStatusDMODE(_parent._m_RPN_Stack.getDModeName());
            string[] Lines = _parent._m_RPN_Functions.getOutputLines();
            _parent._m_Hardware_SD.getFolderListing(Lines, _nLinesShown, LCD_Manager.SCREEN_COLS - 1);
            for (int i = 0; i < _nLinesShown; i++)
            {
                lm.updateTerminalLine((uint)i, Lines[i]);
            }
            lm.forcePaint();
            return 0;
        }
    }
}
