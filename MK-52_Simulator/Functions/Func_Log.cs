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
    public class Func_Ln : RPN_Function
    {
        public Func_Ln()
        {
            Description = "Computes natural logarithm of X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "LN";
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
            double result = s.X.toReal();
            result = Math.Log(result);
            s.X.fromReal(result);
        }
    }

    public class Func_Lg : RPN_Function
    {
        public Func_Lg()
        {
            Description = "Computes logarithm base 10";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LG;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "LG";
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
            double result = s.X.toReal();
            result = Math.Log10(result);
            s.X.fromReal(result);
        }
    }

    public class Func_Log : RPN_Function
    {
        public Func_Log()
        {
            Description = "Computes log Y base X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOG;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "LOG";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            double x = s.X.toReal();
            double y = s.Y.toReal();
            s.pop(0);
            if (x <= 0.0 || y <= 0.0)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            if (y == 1.0)
            {
                s.X.fromReal(double.PositiveInfinity);
                return;
            }
            double result = Math.Log(y) / Math.Log(x);
            s.X.fromReal(result);
        }
    }

    public class Func_EE : RPN_Function
    {
        public Func_EE()
        {
            Description = "Puts E in stack";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_EE;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "e";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            s.push();
            s.X.fromReal(UniversalValue.__EE);
        }
    }
}
