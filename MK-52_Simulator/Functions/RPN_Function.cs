using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function
    {
        public string Keyword = "";
        public string Description = "Unknown empty function";
        public bool containsAddress = false;
        public bool containsRegister = false;
        protected static MK52_Host _parent = null;

        public RPN_Function( MK52_Host parent)
        {
            _parent = parent;
        }

        public virtual void execute(string code)
        {
            return;
        }
        
        public virtual bool executeCODE( string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            execute(code);
            _parent.Program.Counter.Increment();
            return true;
        }

        protected static int getTrigQuadrant(RPN_Value v)
        {
            switch (_parent.dMode)
            {
                case MK52_Host.dMode_Degrees:
                    return getPeriodicDegrees(v, 90);
                case MK52_Host.dMode_Gradian:
                    return getPeriodicDegrees(v, 100);
                default:
                    return getPeriodicRadians(v, Math.PI * 0.5);
            }
        }

        protected static int getTrigOctant(RPN_Value v)
        {
            switch (_parent.dMode)
            {
                case MK52_Host.dMode_Degrees:
                    return getPeriodicDegrees(v, 45);
                case MK52_Host.dMode_Gradian:
                    return getPeriodicDegrees(v, 50);
                default:
                    return getPeriodicRadians(v, Math.PI*0.25);
            }
        }

        protected static double getRadiansByMode(RPN_Value v)
        {
            switch (_parent.dMode)
            {
                case MK52_Host.dMode_Radian:
                    return v.asReal;
                case MK52_Host.dMode_Degrees:
                    return v.asReal * Math.PI / 180.0;
                default:
                    return v.asReal * Math.PI / 200.0;
            }
        }

        protected static void setAngleByMode( double result)
        {
            RPN_Value v = _parent.CalcStack.X;
            switch (_parent.dMode)
            {
                case MK52_Host.dMode_Radian:
                    v.asReal = result;
                    break;
                case MK52_Host.dMode_Degrees:
                    v.asReal = result * 180.0 / Math.PI;
                    break;
                default:
                    v.asReal = result * 200.0 / Math.PI;
                    break;
            }
        }

        #region Private Functions
        private static int getPeriodicDegrees(RPN_Value v, int deg)
        {
            if (v.isInt && v.asInt % deg == 0) // integer degrees
                return Convert.ToInt16((v.asInt % (deg<<2)) / deg);
            double degr = (double)deg;
            double tmp = Math.IEEERemainder(v.asReal, degr);
            if (Math.Abs(tmp) > 2e-4) return -1; // not a quadrant
            tmp = Math.IEEERemainder(v.asReal, degr*4.0);
            return getComparison(tmp, deg);
        }
        private static int getPeriodicRadians(RPN_Value v, double rad)
        {
            double tmp = Math.IEEERemainder(v.asReal, rad);
            if (Math.Abs(tmp) > 1e-6) return -1; // not a quadrant
            tmp = Math.IEEERemainder(v.asReal, rad * 4.0);
            return getComparison(tmp, rad);
        }
        private static int getComparison(double v, double comp)
        {
            if (v < comp * 0.5) return 0;
            if (v < comp * 1.5) return 1;
            if (v < comp * 2.5) return 2;
            if (v < comp * 3.5) return 3;
            return 0;
        }
        #endregion
    }
}
