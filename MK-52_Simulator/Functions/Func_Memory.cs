using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class Func_GOMEM : RPN_Function
    {
        public Func_GOMEM()
        {
            Description = "Sets memory counter to specified address";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_GOMEM;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "GOMEM ";
        }

        public override bool containsMC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _ExtMem(components).setCounter( command);
        }
    }

    public class Func_M2X : RPN_Function
    {
        public Func_M2X()
        {
            Description = "Value from memory register into X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_M2X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "M->X ";
        }

        public override string IOName()
        {
            return "M->X ";
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).MtoX(command);
        }
    }

    public class Func_X2M : RPN_Function
    {
        public Func_X2M()
        {
            Description = "Value from X-register into memory";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_X2M;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "X->M ";
        }

        public override string IOName()
        {
            return "X->M ";
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).XtoM(command);
        }
    }

    public class Func_K_M2X : RPN_Function
    {
        public Func_K_M2X()
        {
            Description = "Indirect value from memory via a register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_K_M2X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "K M->X ";
        }

        public override string IOName()
        {
            return "K M->X ";
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).K_MtoX(command);
        }
    }

    public class Func_K_X2M : RPN_Function
    {
        public Func_K_X2M()
        {
            Description = "Puts value into memory by an address in register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_K_X2M;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "K X->M ";
        }

        public override string IOName()
        {
            return "K X->M ";
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).K_XtoM(command);
        }
    }

    public class Func_A_M2X : RPN_Function
    {
        public Func_A_M2X()
        {
            Description = "Puts value from extended memory into register X";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_A_M2X;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "A M->X ";
        }

        public override string IOName()
        {
            return "A M->X ";
        }

        public override bool containsMC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).A_MtoX(command);
        }
    }

    public class Func_A_X2M : RPN_Function
    {
        public Func_A_X2M()
        {
            Description = "Put value from register X into extended memory";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_A_X2M;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "A X->M ";
        }

        public override string IOName()
        {
            return "A X->M ";
        }

        public override bool containsMC()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            _RegMem(components).A_XtoM(command);
        }
    }

    public class Func_MemSet : RPN_Function
    {
        public Func_MemSet()
        {
            Description = "Sets current memory location from text";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MEMSET;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "MEMSET ";
        }

        public override void execute(MK52_Host components, string command)
        {
            _ExtMem(components).fromString(command);
        }
    }

    public class Func_MemSwp : RPN_Function
    {
        public Func_MemSwp()
        {
            Description = "Swaps data between X-register and memory";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MEMSWP;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "MEMSWP ";
        }

        public override void execute(MK52_Host components, string command)
        {
            UniversalValue X = _Stack( components).X;
            _ExtMem(components).swapWithUV( X);
            if( X.isEmpty()) X.fromInt(0);
        }
    }

    public class Func_MexToX : RPN_Function
    {
        public Func_MexToX()
        {
            Description = "Puts data from extended memory to X-register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MEXTOX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "ExToX ";
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
            UniversalValue X = s.X;
            _ExtMem(components).toUV(X);
            if (X.isEmpty()) X.fromInt(0);
        }
    }

    public class Func_XToMex : RPN_Function
    {
        public Func_XToMex()
        {
            Description = "Puts data from X-register to the extended memory";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_XTOMEX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "XToEx ";
        }

        public override string IOName()
        {
            return Name();
        }

        public override void execute(MK52_Host components, string command)
        {
            _ExtMem(components).fromUV(_Stack( components).X);
        }
    }

    public class Func_MexToR : RPN_Function
    {
        public Func_MexToR()
        {
            Description = "Puts data from the extended memory into a register";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MEXTOR;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "ExToR ";
        }

        public override string IOName()
        {
            return Name();
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            Register_Memory rm = _RegMem(components);
            UniversalValue ptrE = _ExtMem(components).getCurrentLine();
            UniversalValue ptrR = rm._registerAddress(rm.registerByName(command));
            if (ptrE.isEmpty())
            {
                ptrR.fromInt( 0);
                return;
            }
            ptrR.fromLocation(ptrE);
        }
    }

    public class Func_RToMex : RPN_Function
    {
        public Func_RToMex()
        {
            Description = "Puts data from a register into the extended memory";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_RTOMEX;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "RToEx ";
        }

        public override bool containsRegister()
        {
            return true;
        }

        public override void execute(MK52_Host components, string command)
        {
            Register_Memory rm = _RegMem(components);
            UniversalValue ptrR = rm._registerAddress(rm.registerByName(command));
            _ExtMem(components).fromUV(ptrR);
        }
    }
}
