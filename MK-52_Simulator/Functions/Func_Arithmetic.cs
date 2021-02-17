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
    public class Func_Negate : RPN_Function
    {
        public Func_Negate()
        {
            Description = "Sign change";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_NEGATE;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            return "/-/";
        }

        public override string IOName()
        {
            return "/-/";
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            if( s.X.isEmpty()) return;
            if( s.X.isInt())
            {   
                s.X.fromInt( -s.X.toInt());
                return;
            }
            double value = s.X.toReal();
            if( double.IsNaN( value)) return;
            if( double.IsNegativeInfinity(value))
            {
                s.X.fromReal(double.PositiveInfinity);
                return;
            }
            if( double.IsPositiveInfinity(value))
            {
                s.X.fromReal(double.NegativeInfinity);
                return;
            }
            s.X.fromReal( -value);
        }
    }    

    public class Func_Plus : RPN_Function
    {
        public Func_Plus()
        {
            Description = "Add X and Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_PLUS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            return "+";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if( s == null) return;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();
            double result = valueY + valueX;
            if (result < UniversalValue.HUGE_NEGATIVE_AS_REAL || 
                UniversalValue.HUGE_POSITIVE_AS_REAL < result ||
                s.X.isReal() || s.Y.isReal())
            {
                s.pop(0); // store Bx, remove X
                s.X.fromReal( result); 
                return;
            }
            Int64 res = s.Y.toInt() + s.X.toInt();
            s.pop(0); // store Bx, remove X
            s.X.fromInt( res);
        }
    }

    public class Func_Minus : RPN_Function
    {
        public Func_Minus()
        {
            Description = "Subtract X from Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MINUS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            return "-";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if( s == null) return;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();
            double result = valueY - valueX;
            if(  result < UniversalValue.HUGE_NEGATIVE_AS_REAL ||
                UniversalValue.HUGE_POSITIVE_AS_REAL < result ||
                s.X.isReal() || s.Y.isReal() )
            {
                s.pop(0); // store Bx, remove X
                s.X.fromReal( result); 
                return;
            }
            Int64 res = s.Y.toInt() - s.X.toInt();
            s.pop(0); // store Bx, remove X
            s.X.fromInt( res);
        }
    }

    public class Func_Multiply : RPN_Function
    {
        public Func_Multiply()
        {
            Description = "Multiply X and Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MULTIPLY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            return "*";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if( s == null) return;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();
            double result = valueY * valueX;
            if(  result < UniversalValue.HUGE_NEGATIVE_AS_REAL ||
                UniversalValue.HUGE_POSITIVE_AS_REAL < result ||
                s.X.isReal() || s.Y.isReal() )
            {
                s.pop(0); // store Bx, remove X
                s.X.fromReal( result); 
                return;
            }
            Int64 res = s.Y.toInt() * s.X.toInt();
            s.pop(0); // store Bx, remove X
            s.X.fromInt( res);
        }
    }

    public class Func_Divide : RPN_Function
    {
        public Func_Divide()
        {
            Description = "Divide Y by X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DIVIDE;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            return "/";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy2(components);
            if( s == null) return;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();
            double result = valueY / valueX;
            if( double.IsNaN(result) ||
                double.IsNegativeInfinity(result) ||
                double.IsPositiveInfinity(result) ||
                s.X.isReal() || s.Y.isReal())
            {
                s.pop(0); // store Bx, remove X
                s.X.fromReal( result); 
                return;
            }
            Int64 frac = s.Y.toInt() % s.X.toInt();
            Int64 res = s.Y.toInt() / s.X.toInt();
            s.pop(0); // store Bx, remove X
            if( frac == 0) s.X.fromInt( res); // exact division
            else s.X.fromReal( result);
        }
    }
}
