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
    public class Func_IfNotLT0 : RPN_Function
    {
        public Func_IfNotLT0()
        {
            Description = "Jumps to program line if X>=0";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTLT0;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X<0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() < 0.0) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotEQ0 : RPN_Function
    {
        public Func_IfNotEQ0()
        {
            Description = "Jumps to program line if X!=0";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTEQ0;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X=0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() == 0.0) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotGE0 : RPN_Function
    {
        public Func_IfNotGE0()
        {
            Description = "Jumps to program line if X<0";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTGE0;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X>=0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() >= 0.0) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotNE0 : RPN_Function
    {
        public Func_IfNotNE0()
        {
            Description = "Jumps to program line if X==0";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTNE0;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X!=0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() != 0.0) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotLTY : RPN_Function
    {
        public Func_IfNotLTY()
        {
            Description = "Jumps to program line if X>=Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTLTY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X<Y GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() < st.Y.toReal()) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotEQY : RPN_Function
    {
        public Func_IfNotEQY()
        {
            Description = "Jumps to program line if X==Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTEQY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X=Y GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() == st.Y.toReal()) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotGEY : RPN_Function
    {
        public Func_IfNotGEY()
        {
            Description = "Jumps to program line if X<Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTGEY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X>=Y GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() >= st.Y.toReal()) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }

    public class Func_IfNotNEY : RPN_Function
    {
        public Func_IfNotNEY()
        {
            Description = "Jumps to program line if X==Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_IFNOTNEY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "IFNOT X!=Y GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack st = _Stack(components);
            Program_Memory pm = _ProgMem(components);
            if (st.X.toReal() != st.Y.toReal()) pm.incrementCounter();
            else pm.setCounter(command);
        }
    }
}
