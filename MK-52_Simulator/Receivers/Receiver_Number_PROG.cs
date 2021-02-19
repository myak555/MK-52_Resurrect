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

namespace MK52Simulator
{
    //
    // Implements a numeric data entry editor
    //
    public class Receiver_Number_PROG : Receiver_Number
    {                
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Number_PROG(MK52_Host parent)
            : base( parent)
        {
            Moniker = "NUMBER_PROG";
        }

        protected override void completeEntry( string value)
        {
            Program_Memory pm = _parent._m_Program_Memory;
            pm.replaceLine(value);
            pm.incrementCounter();
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            Program_Memory pm = _parent._m_Program_Memory;
            uint cnt = (uint)pm.getCounter();
            StringBuilder sb = new StringBuilder();
            sb.Append(cnt.ToString("0000"));
            sb.Append("> ");
            sb.Append(value.Trim());
            lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS-2, sb.ToString());
            lm.forcePaint();
        }
    }
}
