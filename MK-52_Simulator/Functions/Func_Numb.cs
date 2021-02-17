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
    public class Func_Whole : RPN_Function
    {
        public Func_Whole()
        {
            Description = "Computes the whole part";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_WHOLE;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "[X]";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            UniversalValue X = s.X;
            if (X.isInt()) return;
            double result = X.toReal();
            if (result < 0) result = -Math.Floor(-result);
            else result = Math.Floor(result);
            X.fromReal(result);
        }
    }

    public class Func_Frac : RPN_Function
    {
        public Func_Frac()
        {
            Description = "Computes fractional part of X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_FRAC;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "{X}";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            UniversalValue X = s.X;
            if (X.isInt())
            {
                X.fromInt(0);
                return;
            }
            double result = X.toReal();
            bool positive = true;
            if (result < 0)
            {
                result = -result;
                positive = false;
            }
            result = result - Math.Floor(result);
            X.fromReal(positive ? result : -result);
        }
    }

    public class Func_Max : RPN_Function
    {
        public Func_Max()
        {
            Description = "Swaps X and Y registers if Y>X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MAX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "MAX";
        }

        public override void execute(MK52_Host components, string command)
        {   RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();
            if (valueY > valueX) s.swap(); // keep both values in stack
        }
    }

    public class Func_Abs : RPN_Function
    {
        public Func_Abs()
        {
            Description = "Comutes absolute value of X-register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ABS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "|X|";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            UniversalValue X = s.X; 
            double result = X.toReal();
            if (result >= 0.0) return;
            if (X.isReal())
            {
                X.fromReal( - result);
                return;
            }
            X.fromInt( - X.toInt());
        }
    }

    public class Func_Sign : RPN_Function
    {
        public Func_Sign()
        {
            Description = "Computes sign (-1 for negative, 1 for positive)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SIGN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "SIGN";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            double result = s.X.toReal();
            if (result == 0.0) return;
            s.X.fromInt((result < 0.0) ? -1 : 1);
        }
    }
}
