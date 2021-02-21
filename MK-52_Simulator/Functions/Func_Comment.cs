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
    public class Func_Comment : RPN_Function
    {
        public Func_Comment()
        {
            Description = "Ignores the program line";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_COMMENT;
        }

        public override bool checkName(string name)
        {
            return name[0] == '#';
        }

        public override string Name()
        {
            return "#";
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_Empty : RPN_Function
    {
        public Func_Empty()
        {
            Description = "Empty program line does nothing";
        }

        public override bool checkID(uint id)
        {
            return id == 0;
        }

        public override bool checkName(string name)
        {
            return name.Length == 0;
        }

        public override string Name()
        {
            return "";
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_NOP : RPN_Function
    {
        public Func_NOP()
        {
            Description = "Converts a program line into a comment and back (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_NOP;
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_Toggle_EMOD : RPN_Function
    {
        public Func_Toggle_EMOD()
        {
            Description = "Toggles program editing mode";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_TOGGLE_EMOD;
        }

        public override bool checkName(string name)
        {
            return false;
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            _ProgMem(components).toggleEditMode();
        }
    }

    public class Func_Number : RPN_Function
    {
        public Func_Number()
        {
            Description = "Sends a number from the program line to the X register";
        }

        public override bool checkName(string name)
        {
            return UniversalValue._looksLikeANumber(name);
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Stack s = _Stack(components);
            //s.storeBx(); // in MK-52 the Bx is not updated here
            s.push();
            s.X.fromString( command);
        }
    }
}
