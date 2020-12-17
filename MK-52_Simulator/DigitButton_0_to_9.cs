using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator.Functions;

namespace MK52Simulator
{
    public class DigitButton_0_to_9 : Button
    {
        public DigitButton_0_to_9(int X, int Y, string cN, string cF, string cK)
            :
            base(X, Y, cN, cF, cK)
        {
            standardStoreCommand = cN;
        }
        public DigitButton_0_to_9(int X, int Y, string cN, string cF, string cK, string cA)
            :
            base(X, Y, cN, cF, cK, cA)
        {
            standardStoreCommand = cN;
        }

        protected override bool processNormal(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Normal) return false;
            switch (_parent.XEntry.Mode)
            {
                case RPN_XEntry.Mode_Off:
                    _parent.XEntry.NewEntry(standardNCommand);
                    break;
                case RPN_XEntry.Mode_Whole:
                    if (_parent.XEntry.WholePart == "0") _parent.XEntry.WholePart = ""; // ignore multiple zeros
                    if (_parent.XEntry.WholePart.Length < 12) _parent.XEntry.WholePart += standardNCommand;
                    break;
                case RPN_XEntry.Mode_Decimal:
                    if (_parent.XEntry.WholePart.Length + _parent.XEntry.DecimalPart.Length < 13)
                        _parent.XEntry.DecimalPart += standardNCommand;
                    break;
                default:
                    _parent.XEntry.Exponent += standardNCommand;
                    if (_parent.XEntry.Exponent.Length > 3)
                        _parent.XEntry.Exponent = _parent.XEntry.Exponent.Substring(_parent.XEntry.Exponent.Length - 3);
                    _parent.XEntry.Exponent = _parent.XEntry.Exponent.PadLeft(3, '0');
                    break;
            }
            return true;
        }
    }
}
