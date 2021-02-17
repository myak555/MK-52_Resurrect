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
            lm.Refresh();
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
            lm.Refresh();
            return 0;
        }

        //public override string tick(MK52_Button button)
        //{
        //    //if (_parent._m_Program_Memory.Counter.isActive)
        //    //{
        //    //    _parent._m_Program_Memory.Counter.onButton(button, true);
        //    //    return "Nothing";
        //    //}
        //    //if (_parent.Registers.isActive)
        //    //{
        //    //    _parent.Registers.onButton(button);
        //    //    return "Nothing";
        //    //}
        //    switch (button.Moniker)
        //    {
        //        // Column 0
        //        case "Func F":
        //            return "AUTO_F";
        //        case "Func K":
        //            return "AUTO_K";
        //        case "Func A":
        //            return "AUTO_A";
        //        case "Mode":
        //            _parent._m_RPN_Stack.toggleAngleMode();
        //            return "Nothing";

        //        // Column 1
        //        case "->":
        //            //_parent._m_Program_Memory.Counter.Increment();
        //            return "Nothing";
        //        case "<-":
        //            //_parent._m_Program_Memory.Counter.Decrement();
        //            return "Nothing";
        //        case "B/O":
        //            //_parent._m_Program_Memory.Counter.Set(0);
        //            //_parent.CallStack.Clear();
        //            return "Nothing";
        //        case "S/P":
        //            //if (_parent._m_Program_Memory.isAtStop)
        //            //    _parent._m_Program_Memory.Counter.Increment();
        //            _parent.setReceiver("AUTO_R");
        //            return "Nothing";

        //        // Column 2
        //        case "M->X":
        //            //_parent.Registers.ActivateEntry( Register_Memory.RegisterToStack);
        //            return "Nothing";
        //        case "X->M":
        //            //_parent.Registers.ActivateEntry(Register_Memory.StackToRegister);
        //            return "Nothing";
        //        case "GOTO":
        //            //_parent._m_Program_Memory.Counter.ActivateEntry();
        //            return "Nothing";
        //        case "GOSUB":
        //            //if (_parent._m_Program_Memory.isAtStop && _parent._m_RPN_Stack.X_Label.StartsWith("STOP"))
        //            //{
        //            //    //_parent.CalcStack.X_Label = "X:";
        //            //    _parent._m_Program_Memory.Counter.Increment();
        //            //    return "Nothing";
        //            //}
        //            //_parent._m_Program_Memory.ExecuteCurrentLine();
        //            //if (_parent.Program.isAtStop)
        //                //_parent.CalcStack.X_Label = "STOP reached";
        //            return "Nothing";
        //        default:
        //            //_parent.CalcStack.onButton(button);
        //            return "Nothing";
        //    }                
        //}

        //public override string DisplayName
        //{
        //    get
        //    {
        //        //if (_parent.CalcStack.isActive) return "NUM";
        //        //if (_parent.Program.Counter.isActive) return "PC?";
        //        //if (_parent.Registers.isActive) return "RG?";
        //        return _displayName;
        //    }
        //}
    }
}
