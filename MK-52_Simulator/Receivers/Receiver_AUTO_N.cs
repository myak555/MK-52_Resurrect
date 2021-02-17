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
    public class Receiver_AUTO_N : Receiver_AUTO
    {
        public Receiver_AUTO_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_N";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent._m_RPN_Functions;
            switch( scancode)
            {
                case 0: // keyboard inactive
                    return 0;

                // Column 0
                case 1:
                    _parent.setReceiver("AUTO_F");
                    return 0;
                case 2:
                    _parent.setReceiver("AUTO_K");
                    return 0;
                case 3:
                    _parent.setReceiver("AUTO_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    break;

                // Column 1
                case 5:
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
                    //_lcd->updateStatusPC(_rpnf->progMem->getCounter());
                    break;
                case 6:
                    _rpnf.execute(RPN_Functions.FUNC_DECREMENT_PC);
                    //_lcd->updateStatusPC(_rpnf->progMem->getCounter());
                    break;
                case 7:
                    _rpnf.execute(RPN_Functions.FUNC_RESET_PC);
                    //_lcd->updateStatusPC(_rpnf->progMem->getCounter());
                    break;
                case 8:
                    _parent.setReceiver("AUTO_R");
                    return 0;

                //// Column 2
                //case 9:
                //    _mode = 3;
                //    _rr->activate(0, 0);
                //    break;
                //case 10:
                //    _mode = 4;
                //    _rr->activate(0, 0);
                //    break;
                //case 11:
                //    _mode = 5;
                //    _ar->activate(0, 0);
                //    _lcd->updateStatusPC( _ar->toString());
                //    break;
                //case 12:
                //    _rpnf->executeStep();
                //    _lcd->updateStatusPC( _rpnf->progMem->getCounter());
                //    break;

                //// Column 5
                //case 24:
                //    _rpnf->execute( FUNC_NEGATE);
                //    break;

                //// Column 6
                //case 25:
                //    _rpnf->execute( FUNC_MINUS);
                //    break;
                //case 26:
                //    _rpnf->execute( FUNC_PLUS);
                //    break;
                //case 27:
                //    _rpnf->execute( FUNC_SWAP);
                //    break;

                //// Column 7
                //case 29:
                //    _rpnf->execute( FUNC_DIVIDE);
                //    break;
                //case 30:
                //    _rpnf->execute( FUNC_MULTIPLY);
                //    break;
                //case 31:
                //    _rpnf->execute( FUNC_ENTER);
                //    break;
                //case 32:
                //    if(_rpnf->rpnStack->customStackLabels()) _rpnf->rpnStack->resetStackLabels();              
                //    else _rpnf->execute( FUNC_CLEAR_X);
                //    break;

                default: // all other buttons activate number entry
                    _parent.setReceiver("NUMBER");
                    return scancode;
            }
            return base.tick(0);
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
