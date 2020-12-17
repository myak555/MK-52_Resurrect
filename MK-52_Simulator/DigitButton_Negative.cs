using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class DigitButton_Negative : Button
    {
        public DigitButton_Negative(int X, int Y)
            : base(X, Y)
        {
            standardNCommand = "/-/";
            standardFCommand = "АВТ";
            standardKCommand = "OR";
            standardStoreCommand = "B";
        }

        protected override bool processNormal(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Normal) return false;
            switch (_parent.XEntry.Mode)
            {
                case RPN_XEntry.Mode_Off:
                    _parent.executeFunction("/-/");
                    break;
                case RPN_XEntry.Mode_Whole:
                case RPN_XEntry.Mode_Decimal:
                    _parent.XEntry.Sign = (_parent.XEntry.Sign == "-") ? " " : "-";
                    break;
                default:
                    _parent.XEntry.ExpSign = (_parent.XEntry.ExpSign == "-") ? "+" : "-";
                    break;
            }
            return true;
        }

        protected override bool processF(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_F) return false;
            // Here will be AVT
            _parent.X_Label = "АВТ ещё не придумали";
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }
    }
}
