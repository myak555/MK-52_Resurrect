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
            _parent.getFunctions().clearStopCondition();
            _lastUIUpdate = DateTime.Now;
            if (_parent._m_backgroundWorker.IsBusy)
                _parent._m_backgroundWorker.CancelAsync();
            else
                _parent._m_backgroundWorker.RunWorkerAsync();
            base.activate("AUTO_N");
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE("RUN");
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            if (!_parent._m_backgroundWorker.IsBusy)
                return _rpnf.requestNextReceiver("AUTO_N");
            if (scancode == 8)
            {
                _parent._m_backgroundWorker.CancelAsync();
                return 0;
            }
            TimeSpan ts = DateTime.Now.Subtract(_lastUIUpdate);
            bool update_required = ts.TotalMilliseconds > KBD_RUNNING_DELAY;
            if (!update_required) return 0;
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusPC(_rpnf.progMem.getCounter());
            lm.updateStatusMC(_rpnf.extMem.getCounter());
            lm.updateCalcRegister(0, _rpnf.rpnStack.X.toString());
            lm.requestUpdate();
            _lastUIUpdate = DateTime.Now;
            return 0;
        }
    }
}
