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
    // Implements a generic receiver for all keys in auto mode
    //
    public class Receiver_AUTO: Receiver
    {
        public Receiver_AUTO(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO";
        }

        public override void activate( string prevReceiver)
        {
            base.activate(prevReceiver);
            if (prevReceiver.StartsWith( Moniker))
            {
                tick(0);
                return;
            }
            LCD_Manager lm = _parent.getLCD();
            RPN_Stack st = _parent._m_RPN_Stack;
            lm.clearScreen();
            lm.outputStatus(
                _parent._m_Program_Memory.getCounter(),
                _parent._m_Extended_Memory.getCounter(),
                _parent._m_RPN_Stack.getDModeName(),
                "   ");
            lm.outputCalcRegister(0, st.X.toString());
            lm.outputCalcLabel(0, st.X_Label);
            lm.outputCalcRegister(1, st.Y.toString());
            lm.outputCalcLabel(1, st.Y_Label);
            lm.outputCalcRegister(2, st.Z.toString());
            lm.outputCalcLabel(2, st.Z_Label);
            lm.outputCalcRegister(3, st.T.toString());
            lm.outputCalcLabel(3, st.T_Label);
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            LCD_Manager lm = _parent.getLCD();
            RPN_Stack st = _parent._m_RPN_Stack;
            lm.updateStatusPC( _parent._m_Program_Memory.getCounter());
            lm.updateStatusMC( _parent._m_Extended_Memory.getCounter());
            lm.updateStatusDMODE( st.getDModeName());
            lm.updateCalcRegister(0, st.X.toString());
            lm.updateCalcLabel(0, st.X_Label);
            lm.updateCalcRegister(1, st.Y.toString());
            lm.updateCalcLabel(1, st.Y_Label);
            lm.updateCalcRegister(2, st.Z.toString());
            lm.updateCalcLabel(2, st.Z_Label);
            lm.updateCalcRegister(3, st.T.toString());
            lm.updateCalcLabel(3, st.T_Label);
            lm.forcePaint();
            return 0;
        }
    }
}
