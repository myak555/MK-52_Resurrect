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
    public class Func_Rand : RPN_Function
    {
        public Func_Rand()
        {
            Description = "Computes a pseudo-random value from 0.0 to 1.0";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_RAND;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "RAND";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            s.push();
            double result = components._m_RPN_Functions.myRNG.NextDouble();
            s.X.fromReal(result);
        }
    }

    public class Func_Seed : RPN_Function
    {
        public Func_Seed()
        {
            Description = "Sets seed value for the pseudo-random generator";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SEED;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "SEED";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            int result = 1;
            if( s != null)
                result = (int)(s.X.toInt() & 0x7FFF);
            components._m_RPN_Functions.myRNG = new Random(result);
            s.pop(0);
        }
    }
}
