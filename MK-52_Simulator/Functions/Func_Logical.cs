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
    public class Func_And : RPN_Function
    {
        public Func_And()
        {
            Description = "Computes logical AND between X and Y (as integers)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_AND;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "AND";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            Int64 valueX = s.X.toInt();
            Int64 valueY = s.Y.toInt();
            s.pop(0);
            s.X.fromInt(valueX & valueY);
        }
    }

    public class Func_Or : RPN_Function
    {
        public Func_Or()
        {
            Description = "Computes logical OR between X and Y (as integers)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_OR;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "OR";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            Int64 valueX = s.X.toInt();
            Int64 valueY = s.Y.toInt();
            s.pop(0);
            s.X.fromInt(valueX | valueY);
        }
    }

    public class Func_Xor : RPN_Function
    {
        public Func_Xor()
        {
            Description = "Computes logical XOR between X and Y (as integers)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_XOR;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "XOR";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if (s == null) return;
            Int64 valueX = s.X.toInt();
            Int64 valueY = s.Y.toInt();
            s.pop(0);
            s.X.fromInt(valueX ^ valueY);
        }
    }

    public class Func_Not : RPN_Function
    {
        public Func_Not()
        {
            Description = "Computes logical inverse of X (as an integer)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_NOT;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }
        public override string Name()
        {
            return "NOT";
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
            Int64 result = s.X.toInt();
            s.X.fromInt(~result);
        }
    }
}
