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
        public const int KBD_RUNNING_DELAY = 300; // ms
        private DateTime _lastUIUpdate = DateTime.MinValue;

        public Receiver_AUTO_R(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_R";
        }

        public override void activate(string prevReceiver)
        {
            base.activate("AUTO_N");
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE("RUN");
            lm.forcePaint();
            _lastUIUpdate = DateTime.Now;
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            LCD_Manager lm = _parent.getLCD();
            while (true)
            {
                TimeSpan ts = DateTime.Now.Subtract(_lastUIUpdate);
                bool update_required = ts.TotalMilliseconds > KBD_RUNNING_DELAY;
                _rpnf.executeRun();
                if (_rpnf._atStop) break;
                if (update_required)
                {
                    if (_parent.getKBD().scanImmediate() == 8) break;
                    lm.updateStatusPC(_rpnf.progMem.getCounter());
                    lm.updateStatusMC(_rpnf.extMem.getCounter());
                    lm.updateCalcRegister(0, _rpnf.rpnStack.X.toString());
                    lm.forcePaint();
                }
            }
            _rpnf.requestNextReceiver("AUTO_N");
            //lm.outputStatus(fns.progMem.getCounter(), fns.extMem.getCounter(),
            //                  fns.rpnStack.getDModeName(), "   ");
            //lm.forcePaint();
            return 0;
        }
    }
}
