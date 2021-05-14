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
    public class Func_Sin : RPN_Function
    {
        public Func_Sin()
        {
            Description = "Computes sine";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SIN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "SIN";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            switch (s.XtoOctant())
            {
                case -1:
                    break;
                case 0:
                case 4:
                    s.X.fromInt(0);
                    return;
                case 2:
                    s.X.fromInt(1);
                    return;
                case 6:
                    s.X.fromInt(-1);
                    return;
                default:
                    break;
            }
            double result = s.XtoRadian();
            if (double.IsInfinity(result))
            {
                s.X.fromReal(double.NaN);
                return;
            }
            if (s.X.isReal()) s.setTrigAccuracyWarning(result);
            result = Math.Sin(result);
            s.X.fromReal(result);
        }
    }

    public class Func_ArcSin : RPN_Function
    {
        public Func_ArcSin()
        {
            Description = "Computes arc-sine";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ARCSIN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "ArcSIN";
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
            if (s.X.isInt())
            {
                switch (s.X.toInt())
                {
                    case -1:
                        s.OctantToX(-2);
                        return;
                    case 0:
                        s.OctantToX(0);
                        return;
                    case 1:
                        s.OctantToX(-2);
                        return;
                    default:
                        s.X.fromReal(double.NaN);
                        return;
                }

            }
            double result = s.X.toReal();
            if (result < -1.0 || 1.0 < result)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            result = Math.Asin(result);
            s.RadianToX(result);
        }
    }

    public class Func_Cos : RPN_Function
    {
        public Func_Cos()
        {
            Description = "Computes cosine";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_COS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "COS";
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
            switch (s.XtoOctant())
            {
                case -1:
                    break;
                case 0:
                    s.X.fromInt(1);
                    return;
                case 2:
                case 6:
                    s.X.fromInt(0);
                    return;
                case 4:
                    s.X.fromInt(-1);
                    return;
                default:
                    break;
            }
            double result = s.XtoRadian();
            if (double.IsInfinity(result))
            {
                s.X.fromReal(double.NaN);
                return;
            }
            if (s.X.isReal()) s.setTrigAccuracyWarning(result);
            result = Math.Cos(result);
            s.X.fromReal(result);
        }
    }

    public class Func_ArcCos : RPN_Function
    {
        public Func_ArcCos()
        {
            Description = "Computes arc-cosine";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ARCCOS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "ArcCOS";
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
            if (s.X.isInt())
            {
                switch (s.X.toInt())
                {
                    case -1:
                        s.OctantToX(-4);
                        return;
                    case 0:
                        s.OctantToX(2);
                        return;
                    case 1:
                        s.OctantToX(0);
                        return;
                    default:
                        s.X.fromReal(double.NaN);
                        return;
                }

            }
            double result = s.X.toReal();
            if (result < -1.0 || 1.0 < result)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            result = Math.Acos(result);
            s.RadianToX(result);
        }
    }

    public class Func_Tg : RPN_Function
    {
        public Func_Tg()
        {
            Description = "Computes tangent";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_TG;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "TG";
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
            switch (s.XtoOctant())
            {
                case -1:
                    break;
                case 0:
                case 4:
                    s.X.fromInt(0);
                    return;
                case 1:
                case 5:
                    s.X.fromInt(1);
                    return;
                case 2:
                    s.X.fromReal(double.PositiveInfinity);
                    return;
                case 3:
                case 7:
                    s.X.fromInt(-1);
                    return;
                case 6:
                    s.X.fromReal(double.NegativeInfinity);
                    return;
                default:
                    break;
            }
            double result = s.XtoRadian();
            if (double.IsInfinity(result))
            {
                s.X.fromReal(double.NaN);
                return;
            }
            s.setTrigAccuracyWarning(result);
            result = Math.Tan(result);
            s.X.fromReal(result);
        }
    }

    public class Func_ArcTg : RPN_Function
    {
        public Func_ArcTg()
        {
            Description = "Computes arc-tangent";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ARCTG;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "ArcTG";
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
            if (s.X.isInt())
            {
                switch (s.X.toInt())
                {
                    case -1:
                        s.OctantToX(-1);
                        return;
                    case 0:
                        s.OctantToX(0);
                        return;
                    case 1:
                        s.OctantToX(1);
                        return;
                    default:
                        break;
                }

            }
            double result = s.X.toReal();
            if (double.IsNegativeInfinity(result))
            {
                s.OctantToX(-2);
                return;
            }
            if (double.IsPositiveInfinity(result))
            {
                s.OctantToX(2);
                return;
            }
            result = Math.Atan(result);
            s.RadianToX(result);
        }
    }

    public class Func_PI : RPN_Function
    {
        public Func_PI()
        {
            Description = "Puts 3.14159... in stack";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_PI;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "pi";
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
            s.X.fromReal(UniversalValue.__PI);
        }
    }

    public class Func_D2Rad : RPN_Function
    {
        public Func_D2Rad()
        {
            Description = "Converts degrees into radian";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_D2RAD;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "DEG->RAD";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(x * 1.7453292519943295e-2);
        }
    }

    public class Func_Rad2D : RPN_Function
    {
        public Func_Rad2D()
        {
            Description = "Converts radian into degrees";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_RAD2D;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "RAD->DEG";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(x * 57.29577951308232);
        }
    }

    public class Func_DMOD_DEG : RPN_Function
    {
        public Func_DMOD_DEG()
        {
            Description = "Set trig mode to Degrees";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DMOD_DEG;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }
 
        public override string Name()
        {
            return "DEG";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setDMode( RPN_Stack.DMODE_DEGREES);
        }
    }

    public class Func_DMOD_RAD : RPN_Function
    {
        public Func_DMOD_RAD()
        {
            Description = "Set trig mode to Radians";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DMOD_RAD;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "RAD";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setDMode(RPN_Stack.DMODE_RADIANS);
        }
    }

    public class Func_DMOD_GRD : RPN_Function
    {
        public Func_DMOD_GRD()
        {
            Description = "Set trig mode to Grads";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DMOD_GRD;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "GRD";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setDMode(RPN_Stack.DMODE_GRADS);
        }
    }
}
