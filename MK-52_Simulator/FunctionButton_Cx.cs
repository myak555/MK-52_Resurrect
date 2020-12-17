using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class FunctionButton_Cx : Button
    {
        public FunctionButton_Cx(int X, int Y)
            : base(X, Y)
        {
            standardNCommand = "Cx";
            standardKCommand = "NOT";
            standardStoreCommand = "D";
        }

        protected override bool processNormal(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Normal) return false;
            switch (_parent.XEntry.Mode)
            {
                case RPN_XEntry.Mode_Off:
                    _parent.Memory.StackValues[0].Clear();
                    _parent.ClearLabels();
                    break;
                case RPN_XEntry.Mode_Whole:
                    if (_parent.XEntry.WholePart.Length > 0)
                        _parent.XEntry.WholePart = _parent.XEntry.WholePart.Substring(0, _parent.XEntry.WholePart.Length - 1);
                    else
                    {
                        _parent.Memory.StackValues[0].Clear();
                        _parent.XEntry.Mode = RPN_XEntry.Mode_Off;
                        break;
                    }
                    break;
                case RPN_XEntry.Mode_Decimal:
                    if (_parent.XEntry.DecimalPart.Length > 0)
                        _parent.XEntry.DecimalPart = _parent.XEntry.DecimalPart.Substring(0, _parent.XEntry.DecimalPart.Length - 1);
                    else
                    {
                        _parent.XEntry.Mode = RPN_XEntry.Mode_Whole;
                        break;
                    }
                    break;
                default:
                    _parent.XEntry.Exponent = "000";
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Decimal;
                    break;
            }
            return true;
        }

        protected override bool processF(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_F) return false;
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }

        protected override bool processA(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_A) return false;
            _parent.fMode = RPN_Calculator.fMode_Off;
            return true;
        }

        protected override bool processOff(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Off) return false;
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }
    }
}
