using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator.Functions;

namespace MK52Simulator
{
    public class DigitButton_Decimal : Button
    {
        public DigitButton_Decimal(int X, int Y)
            : base(X, Y)
        {
            standardNCommand = ".";
            standardFCommand = "Rotate";
            standardKCommand = "AND";
            standardStoreCommand = "A";
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
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Decimal;
                    _parent.XEntry.DecimalPart = "";
                    break;
                default:
                    _parent.XEntry.Mode = RPN_XEntry.Mode_Whole;
                    _parent.XEntry.DecimalPart = "";
                    _parent.XEntry.ExpSign = "+";
                    _parent.XEntry.Exponent = "000";
                    break;
            }
            return true;
        }
    }
}
