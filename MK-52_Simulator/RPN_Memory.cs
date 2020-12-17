using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the state engine
    //
    public class RPN_Memory
    {
        public const int StackSize = 4;
        public const int MemorySize = 16;
        public const int ExtendedMemorySize = 1000;
        public const int LoopSize = 4;
        private const string BaseRegisterNames = "0123456789ABCDEF";
        private const string LoopRegisterNames = "0123";

        public List<RPN_Value> StackValues = new List<RPN_Value>();
        public RPN_Value PreviousValue = new RPN_Value();

        public List<RPN_Value> MemoryRegisters = new List<RPN_Value>();
        public int[] LoopRegisters = new int[LoopSize];
        public string RegisterName = "";

        private RPN_Calculator _parent = null;

        public RPN_Memory( RPN_Calculator parent)
        {
            _parent = parent;
            for (int i = 0; i < StackSize; i++)
                StackValues.Add(new RPN_Value());
            for (int i = 0; i < MemorySize; i++)
                MemoryRegisters.Add(new RPN_Value());
            for (int i = 0; i < LoopSize; i++)
                LoopRegisters[i] = 0;
        }

        public void ClearStack()
        {
            foreach (RPN_Value v in StackValues) v.Clear();
        }

        public void ClearName()
        {
            RegisterName = "";
        }

        public void AddEntry(string key)
        {
            RegisterName += key.Trim();
            switch (_parent.fMode)
            {
                case RPN_Calculator.fMode_MX:
                    if (BaseMtoX()) return;
                    if (LoopMtoX()) return;
                    ClearName();
                    return;
                case RPN_Calculator.fMode_XM:
                    if (BaseXtoM()) return;
                    if (LoopXtoM()) return;
                    ClearName();
                    return;
                default:
                    return;
            }
        }

        public bool ValidateMemoryName()
        {
            if (BaseRegisterNames.IndexOf(RegisterName) >= 0) return true;
            if (!RegisterName.StartsWith("L")) return false;
            int i = BaseRegisterNames.IndexOf(RegisterName[1]);
            return 0 <= i && i <= 3;
        }

        public bool BaseMtoX()
        {
            int i = BaseRegisterNames.IndexOf(RegisterName);
            if (i < 0) return false;
            if (_parent.XEntry.pushOnEntryRequired) _parent.Memory.PushStack(1);
            _parent.XEntry.pushOnEntryRequired = true;
            _parent.Memory.StackValues[0].FromRPNValue( this.MemoryRegisters[i]);
            _parent.fMode = RPN_Calculator.fMode_Normal;
            return true;
        }

        public bool LoopMtoX()
        {
            if (!RegisterName.StartsWith("L")) return false;
            int i = LoopRegisterNames.IndexOf(RegisterName[1]);
            if (i < 0) return false;
            if (_parent.XEntry.pushOnEntryRequired) _parent.Memory.PushStack(1);
            _parent.XEntry.pushOnEntryRequired = true;
            _parent.Memory.StackValues[0].asInt = this.LoopRegisters[i];
            _parent.fMode = RPN_Calculator.fMode_Normal;
             return true;
         }

         public bool BaseXtoM()
         {
             int i = BaseRegisterNames.IndexOf(RegisterName);
             if (i < 0) return false;
             this.MemoryRegisters[i].FromRPNValue(_parent.Memory.StackValues[0]);
             _parent.fMode = RPN_Calculator.fMode_Normal;
             return true;
         }

         public bool LoopXtoM()
         {
             if (!RegisterName.StartsWith("L")) return false;
             int i = LoopRegisterNames.IndexOf(RegisterName[1]);
             if (i < 0) return false;
             this.LoopRegisters[i] = (int)(_parent.Memory.StackValues[0].asInt & 0xFFFFFFFF);
             _parent.fMode = RPN_Calculator.fMode_Normal;
             return true;
         }

        public void StorePreviousValue()
        {
            PreviousValue.FromRPNValue(StackValues[0]);
        }

        public void PopStack(int start)
        {
            for (int i = start; i < StackSize; i++)
                StackValues[i - 1].FromRPNValue(StackValues[i]);
        }

        public void PushStack(int start)
        {
            for (int i = StackSize - 1; i >= start; i--)
                StackValues[i].FromRPNValue(StackValues[i - 1]);
        }
    }
}
