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
    public class Func_Increment_PC : RPN_Function
    {
        public Func_Increment_PC()
        {
            Description = "Increments program counter (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_INCREMENT_PC;
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            _ProgMem(components).incrementCounter();
        }
    }

    public class Func_Decrement_PC : RPN_Function
    {
        public Func_Decrement_PC()
        {
            Description = "Decrements program counter (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DECREMENT_PC;
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            _ProgMem(components).decrementCounter();
        }
    }

    public class Func_Reset_PC : RPN_Function
    {
        public Func_Reset_PC()
        {
            Description = "Resets program counter and stack (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_RESET_PC;
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            _ProgMem(components).resetCounter();
        }
    }

    public class Func_GOTO : RPN_Function
    {
        public Func_GOTO()
        {
            Description = "Jumps to program line unconditonally";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_GOTO;
        }
        
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _ProgMem(components).setCounter(command);
        }
    }

    public class Func_GOSUB : RPN_Function
    {
        public Func_GOSUB()
        {
            Description = "Calls a subroutine at given address";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_GOSUB;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "GOSUB ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            Program_Memory pm = _ProgMem( components);
            if( !pm.goSub(command)) return;
            _Stack( components).setStackLabel_P(0, "Error: call stack full");
        }
    }

    public class Func_Return : RPN_Function
    {
        public Func_Return()
        {
            Description = "Returns from a subroutine";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_RETURN;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "RETURN";
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            Program_Memory pm = _ProgMem( components);
            if( !pm.returnFromSub()) return;
            _Stack( components).setStackLabel_P(0, "Error: stack busted!");
        }
    }

    public class Func_Stop : RPN_Function
    {
        public Func_Stop()
        {
            Description = "Stops a program";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_STOP;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "STOP";
        }

        public override void advancePC(MK52_Host components) { }

        public override void execute(MK52_Host components, string command)
        {
            components._m_RPN_Functions._atStop = true;
        }
    }

    public class Func_L0 : RPN_Function
    {
        public Func_L0()
        {
            Description = "Register L0 loop";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_L0;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "WHILE L0>0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _executeLoop(components, command, Register_Memory.RPN_REGISTER_L0);
        }
    }

    public class Func_L1 : RPN_Function
    {
        public Func_L1()
        {
            Description = "Register L1 loop";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_L1;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "WHILE L1>0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _executeLoop(components, command, Register_Memory.RPN_REGISTER_L1);
        }
    }

    public class Func_L2 : RPN_Function
    {
        public Func_L2()
        {
            Description = "Register L2 loop";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_L2;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "WHILE L2>0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC() 
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _executeLoop(components, command, Register_Memory.RPN_REGISTER_L2);
        }
    }

    public class Func_L3 : RPN_Function
    {
        public Func_L3()
        {
            Description = "Register L3 loop";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_L3;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "WHILE L3>0 GOTO ";
        }

        public override void advancePC(MK52_Host components) { }

        public override bool containsPC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _executeLoop(components, command, Register_Memory.RPN_REGISTER_L3);
        }
    }
}

