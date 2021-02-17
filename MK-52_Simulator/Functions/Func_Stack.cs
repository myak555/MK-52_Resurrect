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
    public class Func_Enter : RPN_Function
    {
        public Func_Enter()
        {
            Description = "Enters value into the stack";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ENTER;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }
        public override string Name()
        {
            return "Enter";
        }
        public override string IOName()
        {
            return "Enter";
        }
        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).push();
        }
    }

    public class Func_Swap : RPN_Function
    {
        public Func_Swap()
        {
            Description = "Swaps X and Y";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SWAP;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "X<->Y";
        }

        public override string IOName()
        {
            return "X<->Y";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).swap();
        }
    }

    public class Func_Clear_X : RPN_Function
    {
        public Func_Clear_X()
        {
            Description = "Erases X register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_CLEAR_X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "Cx";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).X.fromInt(0);
        }
    }

    public class Func_Rot : RPN_Function
    {
        public Func_Rot()
        {
            Description = "Rotates stack (X to T)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_ROT;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }
        public override string Name()
        {
            return "Rotate";
        }
        public override string IOName()
        {
            return "Rotate";
        }
        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).rotate();
        }
    }

    public class Func_Bx : RPN_Function
    {
        public Func_Bx()
        {
            Description = "Recovers the previous value";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_BX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "Bx";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).push(0);
        }
    }

    public class Func_LBX: RPN_Function
    {
        public Func_LBX()
        {
            Description = "Puts value into X Label";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LBX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P( name, Name());
        }

        public override string Name()
        { 
            return "LBX> ";
        }

        public override string IOName()
        {
            return "LBX> ";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setStackLabel( 0, command);
        }
    }

    public class Func_LBY : RPN_Function
    {
        public Func_LBY()
        {
            Description = "Puts value into Y Label";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LBY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "LBY> ";
        }

        public override string IOName()
        {
            return "LBY> ";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setStackLabel(1, command);
        }
    }

    public class Func_LBZ : RPN_Function
    {
        public Func_LBZ()
        {
            Description = "Puts value into Z Label";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LBZ;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "LBZ> ";
        }

        public override string IOName()
        {
            return "LBZ> ";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setStackLabel(2, command);
        }
    }

    public class Func_LBT : RPN_Function
    {
        public Func_LBT()
        {
            Description = "Puts value into T Label";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LBT;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "LBT> ";
        }

        public override string IOName()
        {
            return "LBT> ";
        }

        public override void execute(MK52_Host components, string command)
        {
            _Stack(components).setStackLabel(3, command);
        }
    }
}
