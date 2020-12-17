using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class Button
    {
        public int X = 0;
        public int Y = 0;
        public int sX = 40;
        public int sY = 30;
        public string standardNCommand = "";
        public string standardFCommand = "";
        public string standardKCommand = "";
        public string standardACommand = "";
        public string standardStoreCommand = "";

        public Button( int X, int Y)
        {
            this.X = X;
            this.Y = Y;
        }

        public Button(int X, int Y, string cN, string cF)
        {
            this.X = X;
            this.Y = Y;
            standardNCommand = cN;
            standardFCommand = cF;
        }

        public Button(int X, int Y, string cN, string cF, string cK)
        {
            this.X = X;
            this.Y = Y;
            standardNCommand = cN;
            standardFCommand = cF;
            standardKCommand = cK;
        }

        public Button(int X, int Y, string cN, string cF, string cK, string cA)
        {
            this.X = X;
            this.Y = Y;
            standardNCommand = cN;
            standardFCommand = cF;
            standardKCommand = cK;
            standardACommand = cA;
        }

        public Button(int X, int Y, string cN, string cF, string cK, string cA, string cS)
        {
            this.X = X;
            this.Y = Y;
            standardNCommand = cN;
            standardFCommand = cF;
            standardKCommand = cK;
            standardACommand = cA;
            standardStoreCommand = cS;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            if (standardNCommand != "") sb.Append(standardNCommand);
            else sb.Append("Unknown");
            return sb.ToString();
        }

        public bool isPressed(int x, int y)
        {
            if (x < this.X) return false;
            if (y < this.Y) return false;
            if (x > this.X + sX) return false;
            if (y > this.Y + sY) return false;
            return true;
        }

        public virtual bool processPress(RPN_Calculator calc)
        {
            if (processNormal(calc)) return true;
            if (processF(calc)) return true;
            if (processK(calc)) return true;
            if (processA(calc)) return true;
            if (processMX(calc)) return true;
            if (processOff(calc)) return true;
            return false;
        }

        protected virtual bool processNormal(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Normal) return false;
            if (standardNCommand.Length > 0) _parent.executeFunction(standardNCommand);
            return true;
        }

        protected virtual bool processF(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_F) return false;
            if (standardFCommand.Length > 0) _parent.executeFunction(standardFCommand);
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }

        protected virtual bool processK(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_K) return false;
            if (standardKCommand.Length > 0) _parent.executeFunction(standardKCommand);
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }

        protected virtual bool processA(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_A) return false;
            if (standardACommand.Length > 0) _parent.executeFunction(standardACommand);
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }

        protected virtual bool processMX(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_MX &&
                _parent.fMode != RPN_Calculator.fMode_XM) return false;
            if (standardStoreCommand.Length > 0) _parent.Memory.AddEntry(standardStoreCommand);
            return true;
        }

        protected virtual bool processOff(RPN_Calculator _parent)
        {
            if (_parent.fMode != RPN_Calculator.fMode_Off) return false;
            return true;
        }
    }
}
