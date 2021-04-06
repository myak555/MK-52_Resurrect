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

namespace MK52Simulator
{
    public class Func_Exp : RPN_Function
    {
        public Func_Exp()
        {
            Description = "Computes exponent";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_EXP;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "EXP";
        }

        public override string IOName()
        {
            return "EXP";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double result = s.X.toReal();
            result = Math.Exp(result);
            s.X.fromReal(result);
        }
    }

    public class Func_10x : RPN_Function
    {
        public Func_10x()
        {
            Description = "Computes 10 power X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_10X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "10^x";
        }

        public override string IOName()
        {
            return "10^x";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double result = 1.0;
            UniversalValue X = s.X;
            if (X.isReal())
            {
                result = Math.Pow(10.0, X.toReal());
                X.fromReal(result);
                return;
            }
            Int64 p = X.toInt();
            if (p > 300)
            {
                X.fromReal(double.PositiveInfinity);
                return;
            }
            if (p < -300)
            {
                X.fromInt(0);
                return;
            }
            if (0 <= p && p <= 18)
            {
                Int64 r2 = 1;
                while (p > 0)
                {
                    r2 *= 10L;
                    p--;
                }
                X.fromInt(r2);
                return;
            }
            while (p > 0)
            {
                result *= 10.0;
                p--;
            }
            while (p < 0)
            {
                result *= 0.1;
                p++;
            }
            X.fromReal(result);
        }
    }

    public class Func_Pow : RPN_Function
    {
        public Func_Pow()
        {
            Description = "Computes X power Y (leaves Y in stack)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_POW;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "X^Y";
        }

        public override string IOName()
        {
            return "X^Y";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            UniversalValue X_ = s.X;
            UniversalValue Y_ = s.Y;
            if (Y_.isEmpty())
            {
                X_.fromInt(1);
                return;
            }
            double result = 1.0;
            double x = X_.toReal();
            if (Y_.isReal())
            {
                result = Math.Pow(x, Y_.toReal());
                X_.fromReal(result);
                return;
            }
            Int64 p = Y_.toInt();
            Int64 p2 = p;
            if (x == 0.0 && p == 0) // special case
            {
                X_.fromInt(1);
                return;
            }
            if (x == 0.0 && p < 0)
            {
                X_.fromReal( double.PositiveInfinity);
                return;
            }
            while (p > 0)
            {
                result *= x;
                p--;
            }
            x = 1.0 / x;
            while (p < 0)
            {
                result *= x;
                p++;
            }
            if (p2 <= 0 || X_.isReal() || Math.Abs(result) > UniversalValue.HUGE_POSITIVE_AS_REAL)
            {
                X_.fromReal(result);
                return;
            }
            // Try to keep as integer
            Int64 result2 = X_.toInt();
            Int64 mul = result2;
            while (p2 > 1)
            {
                result2 *= mul;
                p2--;
            }
            X_.fromInt(result2);
        }
    }

    public class Func_PowYX : RPN_Function
    {
        public Func_PowYX()
        {
            Description = "Computes Y power X (classic HP)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_POWYX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "Y^X";
        }

        public override string IOName()
        {
            return "Y^X";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            s.pop(0);
            UniversalValue X_ = s.X;
            UniversalValue Y_ = s.Bx;
            if (Y_.isEmpty())
            {
                X_.fromInt(1);
                return;
            }
            double result = 1.0;
            double x = X_.toReal();
            if (Y_.isReal())
            {
                result = Math.Pow(x, Y_.toReal());
                X_.fromReal(result);
                return;
            }
            Int64 p = Y_.toInt();
            Int64 p2 = p;
            if (x == 0.0 && p == 0) // special case
            {
                X_.fromInt(1);
                return;
            }
            if (x == 0.0 && p < 0)
            {
                X_.fromReal(double.PositiveInfinity);
                return;
            }
            while (p > 0)
            {
                result *= x;
                p--;
            }
            x = 1.0 / x;
            while (p < 0)
            {
                result *= x;
                p++;
            }
            if (p2 <= 0 || X_.isReal() || Math.Abs(result) > UniversalValue.HUGE_POSITIVE_AS_REAL)
            {
                X_.fromReal(result);
                return;
            }
            // Try to keep as integer
            Int64 result2 = X_.toInt();
            Int64 mul = result2;
            while (p2 > 1)
            {
                result2 *= mul;
                p2--;
            }
            X_.fromInt(result2);
        }
    }

    public class Func_X2 : RPN_Function
    {
        public Func_X2()
        {
            Description = "Computes X squared";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_X2;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "X^2";
        }

        public override string IOName()
        {
            return "X^2";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(x * x);
        }
    }

    public class Func_SQRT : RPN_Function
    {
        public Func_SQRT()
        {
            Description = "Computes square root of X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SQRT;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "SQRT";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double x = s.X.toReal();
            if (s.setNegativeRootWarning(x)) x = -x;
            s.X.fromReal(Math.Sqrt(x));
        }
    }

    public class Func_1X : RPN_Function
    {
        public Func_1X()
        {
            Description = "Computes inverse of X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_1X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "1/X";
        }

        public override string IOName()
        {
            return "1/X";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(1.0 / x);
        }
    }
}



