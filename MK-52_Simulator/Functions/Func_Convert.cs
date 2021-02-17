using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class Func_in2mm : RPN_Function
    {
        public Func_in2mm()
        {
            Description = "Converts inches into mm";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IN2MM;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            // TODO
            return "->mm";
        }

        public override string IOName()
        {
            return "->MM";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(x * 25.4);
        }
    }

    public class Func_mm2in : RPN_Function
    {
        public Func_mm2in()
        {
            Description = "Converts mm into inches";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MM2IN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            // TODO
            return "->in";
        }

        public override string IOName()
        {
            return "->in";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            s.storeBx();
            double x = s.X.toReal();
            s.X.fromReal(x / 25.4);
        }
    }

    public class Func_DM2D : RPN_Function
    {
        public Func_DM2D()
        {
            Description = "Converts DD.MMmmm into DD.dddd";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DM2D;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            // TODO
            return "<-DM";
        }

        public override string IOName()
        {
            return "<-DM";
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            if (s.X.isInt()) return;
            double x = s.X.toReal();
            bool positive = true;
            if (x < 0.0)
            {
                positive = false;
                x = -x;
            }
            double degr = Math.Floor(x);
            double mins = (x - degr) * 100.0;
            if (mins >= 60.0)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            x = degr + mins / 60.0;
            s.X.fromReal(positive ? x : -x);
        }
    }

    public class Func_D2DM : RPN_Function
    {
        public Func_D2DM()
        {
            Description = "Converts DD.dddd into DD.MMmmm";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_D2DM;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            // TODO
            return "->DM";
        }

        public override string IOName()
        {
            return "->DM";
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            if (s.X.isInt()) return;
            double x = s.X.toReal();
            bool positive = true;
            if (x < 0.0)
            {
                positive = false;
                x = -x;
            }
            double degr = Math.Floor(x);
            double mins = (x - degr) * 0.6;
            x = degr + mins;
            s.X.fromReal(positive ? x : -x);
        }
    }

    public class Func_DMS2D : RPN_Function
    {
        public Func_DMS2D()
        {
            Description = "Converts DD.MMSSss into DD.dddd";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DMS2D;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            // TODO
            return "<-DMS";
        }

        public override string IOName()
        {
            return "<-DMS";
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            if (s.X.isInt()) return;
            double x = s.X.toReal();
            bool positive = true;
            if (x < 0.0)
            {
                positive = false;
                x = -x;
            }
            double degr = Math.Floor(x);
            x = (x - degr) * 100.0;
            double mins = Math.Floor(x);
            if (mins >= 60.0)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            double sec = (x - mins) * 100.0;
            if (sec >= 60.0)
            {
                s.X.fromReal(double.NaN);
                return;
            }
            x = degr + (mins * 60.0 + sec) / 3600.0;
            s.X.fromReal(positive ? x : -x);
        }
    }

    public class Func_D2DMS : RPN_Function
    {
        public Func_D2DMS()
        {
            Description = "Converts DD.dddd into DD.MMSS";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_D2DMS;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P( name, Name());
        }

        public override string Name()
        {
            // TODO
            return "->DMS";
        }

        public override string IOName()
        {
            return "->DMS";
        }

        public override void execute (MK52_Host components, string command)
        {
            RPN_Stack s = _dealWithClergy1(components);
            if (s == null) return;
            s.storeBx();
            if (s.X.isInt()) return;
            double x = s.X.toReal();
            bool positive = true;
            if (x < 0.0)
            {
                positive = false;
                x = -x;
            }
            double degr = Math.Floor(x);
            double sec = (x - degr) * 3600.0;
            double min = Math.Floor(sec / 60.0);
            sec -= min * 60.0;
            x = degr + 0.01 * (min + sec * 0.01);
            s.X.fromReal(positive ? x : -x);
        }
    }
}
