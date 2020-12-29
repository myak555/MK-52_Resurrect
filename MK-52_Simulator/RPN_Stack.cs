using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Functions;

namespace MK52Simulator
{
    //
    // Implements the RPN stack
    //
    public class RPN_Stack
    {
        public const int StackSize = 4;

        private RPN_Calculator _parent = null;
        private string[] _standardLabels = { "X:", "Y:", "Z:", "T:" };

        // stack data
        public List<RPN_Value> StackValues = new List<RPN_Value>();
        public RPN_Value PreviousValue = new RPN_Value();
        public string X_Label = "";
        public string Y_Label = "";
        public string Z_Label = "";
        public string T_Label = "";

        private RPN_Number_Entry _numberEntry = new RPN_Number_Entry();

        public RPN_Stack(RPN_Calculator parent)
        {
            _parent = parent;
            for (int i = 0; i < StackSize; i++)
                StackValues.Add(new RPN_Value());
            ClearLabels();
        }

        public void ClearStack()
        {
            foreach (RPN_Value v in StackValues) v.Clear();
        }

        public RPN_Value X
        {
            get
            {
                CompleteEntry();
                return StackValues[0];
            }
            set
            {
                StackValues[0].FromRPNValue(value);
            }
        }

        public RPN_Value Y
        {
            get
            {
                return StackValues[1];
            }
            set
            {
                StackValues[1].FromRPNValue(value);
            }
        }

        public RPN_Value Z
        {
            get
            {
                return StackValues[2];
            }
            set
            {
                StackValues[2].FromRPNValue(value);
            }
        }

        public RPN_Value T
        {
            get
            {
                return StackValues[3];
            }
            set
            {
                StackValues[3].FromRPNValue(value);
            }
        }

        public void CompleteEntry()
        {
            if (_numberEntry.isActive)
                _numberEntry.ToValue(StackValues[0]);
        }

        public void StorePreviousValue()
        {
            PreviousValue.FromRPNValue(StackValues[0]);
        }

        public void RecoverPreviousValue()
        {
            RPN_Value tmp = new RPN_Value(X);
            StorePreviousValue();
            Push(1);
            X.FromRPNValue(tmp);
        }

        public void Pop()
        {
            Pop(1);
        }
        
        public void Pop(int start)
        {
            for (int i = start; i < StackSize; i++)
                StackValues[i - 1].FromRPNValue(StackValues[i]);
        }

        public void Push()
        {
            Push(1);
        }

        public void Push( double v)
        {
            CompleteEntry();
            StorePreviousValue();
            Push(1);
            X.asReal = v;
        }

        public void Push(int start)
        {
            for (int i = StackSize - 1; i >= start; i--)
                StackValues[i].FromRPNValue(StackValues[i - 1]);
        }

        public void Replace(double v)
        {
            StorePreviousValue();
            X.asReal = v;
        }

        public void Rotate()
        {
            RPN_Value tmp = new RPN_Value(StackValues[0]);
            StorePreviousValue();
            Pop(1);
            StackValues[StackValues.Count-1].FromRPNValue(tmp);
        }

        public void Swap()
        {
            RPN_Value tmp = new RPN_Value(X);
            StorePreviousValue();
            X.FromRPNValue(Y);
            Y.FromRPNValue(tmp);
        }

        public void Enter()
        {
            StorePreviousValue();
            if (!_numberEntry.isActive)
            {
                Push(1);
                return;
            }
            _numberEntry.ToValue(StackValues[0]);
        }

        public void Plus()
        {
            RPN_Value operand1 = X;
            RPN_Value operand2 = new RPN_Value( Y);
            operand2.Add(operand1);
            if (Double.IsInfinity(operand2.asReal))
            {
                setOverflow();
                return;
            }
            StorePreviousValue();
            Y.FromRPNValue( operand2);
            Pop(1);
        }

        public void Minus()
        {
            RPN_Value operand1 = X;
            RPN_Value operand2 = new RPN_Value(Y);
            operand2.Subtract(operand1);
            if (Double.IsInfinity(operand2.asReal))
            {
                setOverflow();
                return;
            }
            StorePreviousValue();
            Y.FromRPNValue(operand2);
            Pop(1);
        }

        public void Multiply()
        {
            RPN_Value operand1 = X;
            RPN_Value operand2 = new RPN_Value(Y);
            operand2.Multiply(operand1);
            if (Double.IsInfinity(operand2.asReal))
            {
                setOverflow();
                return;
            }
            StorePreviousValue();
            Y.FromRPNValue(operand2);
            Pop(1);
        }

        public void Divide()
        {
            RPN_Value operand1 = X;
            if (operand1.asReal == 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            RPN_Value operand2 = new RPN_Value(Y);
            operand2.Divide(operand1);
            if (Double.IsInfinity(operand2.asReal))
            {
                setOverflow();
                return;
            }
            StorePreviousValue();
            Y.FromRPNValue(operand2);
            Pop(1);
        }

        public void onButton(string key)
        {
            switch (key)
            {
                case "0":
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                case ".":
                    if (!_numberEntry.isActive) Push(1);
                    _numberEntry.AddEntry(key);
                    return;
                case "/-/":
                    if (_numberEntry.isActive) _numberEntry.AddEntry(key);
                    else StackValues[0].Negate();
                    return;
                case "+":
                    Plus();
                    return;
                case "-":
                    Minus();
                    return;
                case "Swap":
                    Swap();
                    return;
                case "/":
                    Divide();
                    return;
                case "*":
                    Multiply();
                    return;
                case "EE":
                    if (!_numberEntry.isActive)
                        _numberEntry.FromValue(StackValues[0]);
                    else
                        _numberEntry.AddEntry(key);
                    return;
                case "Enter":
                    Enter();
                    return;
                case "Cx":
                    if (isCustomLabels())
                    {
                        ClearLabels();
                        return;
                    }
                    if (_numberEntry.isActive) _numberEntry.AddEntry(key);
                    else StackValues[0].Clear();
                    return;
                default:
                    return;
            }
        }

        public void ClearLabels()
        {
            X_Label = _standardLabels[0];
            Y_Label = _standardLabels[1];
            Z_Label = _standardLabels[2];
            T_Label = _standardLabels[3];
        }

        public bool isCustomLabels()
        {
            if (X_Label != _standardLabels[0]) return true;
            if (Y_Label != _standardLabels[1]) return true;
            if (Z_Label != _standardLabels[2]) return true;
            if (T_Label != _standardLabels[3]) return true;
            return false;
        }

        public void ToStrings( string[] inp){
            inp[1] = T_Label;
            inp[2] = StackValues[3].ToString();
            inp[3] = Z_Label;
            inp[4] = StackValues[2].ToString();
            inp[5] = Y_Label;
            inp[6] = StackValues[1].ToString();
            inp[7] = X_Label;
            inp[8] = ( _numberEntry.isActive)?
                "> " + _numberEntry.ToString():
                StackValues[0].ToString();
        }

        public void setOverflow()
        {
            X_Label = "Error: Overflow";
        }
        
        public void setTrigWarning(double v)
        {
            if (Math.Abs(v) < 1.0e12) return;
            X_Label = "Warning: Trig Accuracy";
        }

        public double setImaginaryWarning(double v)
        {
            if (v > 0.0) return v;
            X_Label = "Warning: Imaginary";
            return -v;
        }

        public bool setInvTrigError(double v)
        {
            if (Math.Abs(v) <= 1.0) return false;
            X_Label = "Error: Inverse Trig";
            return true;
        }

        public void setArgumentError()
        {
            X_Label = "Error: Argument";
        }

        public void setInfinityError()
        {
            X_Label = "Error: Infinity";
        }

        public void setDegError()
        {
            X_Label = "Error: Deg Format";
        }

        #region Load / Save
        public bool LoadLine(string s)
        {
            if (StringLoadHelper(s, "XLabel", ref X_Label)) return true;
            if (StringLoadHelper(s, "YLabel", ref Y_Label)) return true;
            if (StringLoadHelper(s, "ZLabel", ref Z_Label)) return true;
            if (StringLoadHelper(s, "TLabel", ref T_Label)) return true;
            if (StackLoadHelper(s, "X", 0)) return true;
            if (StackLoadHelper(s, "Y", 1)) return true;
            if (StackLoadHelper(s, "Z", 2)) return true;
            if (StackLoadHelper(s, "T", 3)) return true;
            if (ValueLoadHelper(s, "Bx", ref PreviousValue)) return true;
            return false;
        }

        public void Save(StreamWriter sw)
        {
            sw.Write("#\n");
            sw.Write("# Stack registers:\n");
            sw.Write("#\n");
            if (T_Label != _standardLabels[3]) sw.Write("TLabel = " + T_Label.Trim() + "\n");
            sw.Write("T = " + StackValues[3].ToString() + "\n");
            if (Z_Label != _standardLabels[2]) sw.Write("ZLabel = " + Z_Label.Trim() + "\n");
            sw.Write("Z = " + StackValues[2].ToString() + "\n");
            if (Y_Label != _standardLabels[1]) sw.Write("YLabel = " + Y_Label.Trim() + "\n");
            sw.Write("Y = " + StackValues[1].ToString() + "\n");
            if (X_Label != _standardLabels[0]) sw.Write("XLabel = " + X_Label.Trim() + "\n");
            sw.Write("X = " + StackValues[0].ToString() + "\n");
            sw.Write("Bx = " + PreviousValue.ToString() + "\n");
        }

        private bool StringLoadHelper(string s, string varName, ref string inp)
        {
            varName += " = ";
            if (!s.StartsWith(varName)) return false;
            inp = s.Substring(varName.Length).Trim();
            return true;
        }

        private bool ValueLoadHelper(string s, string varName, ref RPN_Value inp)
        {
            varName += " = ";
            if (!s.StartsWith(varName)) return false;
            inp.FromString(s.Substring(varName.Length));
            return true;
        }

        private bool StackLoadHelper(string s, string varName, int index)
        {
            varName += " = ";
            if (!s.StartsWith(varName)) return false;
            StackValues[index].FromString(s.Substring(varName.Length));
            return true;
        }
        #endregion
    }
}
