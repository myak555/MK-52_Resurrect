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
    // Implements a generic empty receiver that stops execution at S/P button
    //
    public class Receiver_AUTO_R : Receiver_AUTO
    {
        public Receiver_AUTO_R(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_R";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            if (prevReceiver == Moniker)
            {
                return;
            }
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE("RUN");
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            if (scancode != 8) return 0;
            _parent.setReceiver("AUTO_N");
            return 0;
        }

        //public override string tick(MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        // Column 1
        //        case "S/P":
        //            _parent.setReceiver("AUTO_N");
        //            return "Nothing";
        //        default:
        //            //_parent._m_Program_Memory.ExecuteCurrentLine();
        //            return "Nothing";
        //    }                
        //}
    }
}
