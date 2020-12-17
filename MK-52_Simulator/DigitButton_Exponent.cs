using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class DigitButton_Exponent : Button
    {
        public DigitButton_Exponent(int X, int Y)
            : base(X, Y)
        {
            standardNCommand = "EE";
            standardFCommand = "ПРГ";
            standardKCommand = "XOR";
            standardStoreCommand = "C";
        }

        protected override bool processNormal(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Normal) return false;
            switch (_parent.XEntry.Mode)
            {
                case RPN_XEntry.Mode_Off:
                    _parent.XEntry.FromValue(_parent.Memory.StackValues[0]);
                    break;
                case RPN_XEntry.Mode_Whole:
                    if (_parent.XEntry.WholePart.Length==0 ||
                        _parent.XEntry.WholePart == "0") 
                        _parent.XEntry.WholePart = "1";
                    _parent.XEntry.DecimalPart = "0";
                    _parent.XEntry.ExpSign = "+";
                    _parent.XEntry.Exponent = "000";
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Exponent;
                    break;
                case RPN_XEntry.Mode_Decimal:
                    if( _parent.XEntry.DecimalPart.Length == 0)
                        _parent.XEntry.DecimalPart = "0";
                    _parent.XEntry.ExpSign = "+";
                    _parent.XEntry.Exponent = "000";
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Exponent;
                    break;
                default:
                    _parent.XEntry.ExpSign = "+";
                    _parent.XEntry.Exponent = "000";
                    if (_parent.XEntry.DecimalPart == "0") _parent.XEntry.DecimalPart = "";
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Decimal;
                    break;
            }
            return true;
        }

        protected override bool processF(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_F) return false;
            // Here will be ПРГ
            _parent.X_Label = "ПРГ ещё не придумали";
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }
    }
}
