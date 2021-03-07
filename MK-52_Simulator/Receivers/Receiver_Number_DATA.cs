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
    public class Receiver_Number_DATA : Receiver_Number
    {                
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Number_DATA(MK52_Host parent)
            : base( parent)
        {
            Moniker = "NUMBER_DATA";
        }

        protected override void completeEntry( string value)
        {
            Extended_Memory em = _parent._m_Extended_Memory;
            em.fromString(value);
            em.incrementCounter();
        }

        protected override void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            Extended_Memory em = _parent._m_Extended_Memory;
            StringBuilder sb = new StringBuilder();
            sb.Append(em.toCounterString());
            sb.Append(value.Trim());
            lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS-2, sb.ToString());
            lm.requestUpdate();
        }
    }
}
