using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator.Functions;

namespace MK52Simulator
{
    //
    // Implements the state engine
    //
    public class RPN_Calculator
    {
        public const int ScreenWidth = 25;
        public const int StatusWidth = 32;

        // modifier mode
        public string[] fModeLabels = { "      ", "[   ] ", "[ F ] ", "[ K ] ", "[ A ] ", "[MOD] ", "[M<-] ", "[M->] " };
        public const int fMode_Off = 0;
        public const int fMode_Normal = 1;
        public const int fMode_F = 2;
        public const int fMode_K = 3;
        public const int fMode_A = 4;
        public const int fMode_M = 5;
        public const int fMode_XM = 6;
        public const int fMode_MX = 7;
        public int fMode = fMode_Normal;

        // degrees/radian/gradian mode
        public string[] dModeLabels = { "[DEG] ", "[RAD] ", "[GRD] " };
        public const int dMode_Degrees = 0;
        public const int dMode_Radian = 1;
        public const int dMode_Gradian = 2;
        public int dMode = dMode_Degrees;
        
        // screen labels
        public string X_Label = " X:";
        public string Y_Label = " Y:";
        public string Z_Label = " Z:";
        public string T_Label = " T:";

        // calculator memory
        public RPN_Memory Memory = null;        
        public RPN_XEntry XEntry = null;
        public string[] screenValues = new string[9];

        // random number remembered
        public Random myRNG = new Random();

        // functions
        public Dictionary<string, RPN_Function> Functions = new Dictionary<string, RPN_Function>();

        #region General Functions
        public RPN_Calculator()
        {
            Memory = new RPN_Memory(this);
            XEntry = new RPN_XEntry(this);
            addFunctions();
            ClearLabels();
        }

        public void setScreenValues()
        {
            if (fMode == RPN_XEntry.Mode_Off)
            {
                for (int i = 0; i < screenValues.Length; i++) screenValues[i] = "";
                return;
            }
            screenValues[0] = dModeLabels[dMode];
            screenValues[0] += fModeLabels[fMode];
            screenValues[0] = screenValues[0].PadLeft(StatusWidth);
            screenValues[1] = T_Label;
            screenValues[2] = presentValue(Memory.StackValues[3]);
            screenValues[3] = Z_Label;
            screenValues[4] = presentValue(Memory.StackValues[2]);
            screenValues[5] = Y_Label;
            screenValues[6] = presentValue(Memory.StackValues[1]);
            screenValues[7] = X_Label;
            screenValues[8] = (XEntry.Mode == RPN_XEntry.Mode_Off) ?
                presentValue(Memory.StackValues[0]) : XEntry.ToString();
        }
        #endregion

        public void ClearLabels()
        {
            X_Label = " X:";
            Y_Label = " Y:";
            Z_Label = " Z:";
            T_Label = " T:";
        }

        public void setTrigWarning(double v)
        {
            if (Math.Abs(v) < 1.0e12) return; 
            X_Label = "Warn: Trig Accuracy";
        }

        public double setImaginaryWarning(double v)
        {
            if (v > 0.0) return v;
            X_Label = "Warn: Imaginary";
            return -v;
        }

        public bool setInvTrigError(double v)
        {
            if (Math.Abs(v) <= 1.0) return false;
            X_Label = "Err: Inverse Trig";
            return true;
        }

        public void setArgumentError()
        {
            X_Label = "Err: Argument";
        }

        public void setInfinityError()
        {
            X_Label = "Err: Infinity";
        }

        public void setDegError()
        {
            X_Label = "Err: Deg Format";
        }

        public void executeFunction(string name)
        {
            if (!Functions.ContainsKey(name)) return;
            RPN_Function f = Functions[name];
            f.execute();
            if (f.Keyword != "Enter") 
                XEntry.pushOnEntryRequired = true; // reset new edit behavoir
        }

        #region Implemented Math Functions
        //
        // Function adding helper
        // 
        private void addFunction(RPN_Function f)
        {
            Functions.Add(f.Keyword, f);
        }
        private void addFunctions()
        {
            addFunction(new RPN_Function_10x(this));
            addFunction(new RPN_Function_1x(this));
            addFunction(new RPN_Function_ABS(this));
            addFunction(new RPN_Function_AND(this));
            addFunction(new RPN_Function_arcCOS(this));
            addFunction(new RPN_Function_arcSIN(this));
            addFunction(new RPN_Function_arcTG(this));
            addFunction(new RPN_Function_COS(this));
            addFunction(new RPN_Function_Divide(this));
            addFunction(new RPN_Function_e(this));
            addFunction(new RPN_Function_Enter(this));
            addFunction(new RPN_Function_EXP(this));
            addFunction(new RPN_Function_FRAC(this));
            addFunction(new RPN_Function_FromDM(this));
            addFunction(new RPN_Function_FromDMS(this));
            addFunction(new RPN_Function_FromIN(this));
            addFunction(new RPN_Function_FromRAD(this));
            addFunction(new RPN_Function_INT(this));
            addFunction(new RPN_Function_LG(this));
            addFunction(new RPN_Function_LN(this));
            addFunction(new RPN_Function_LOG(this));
            addFunction(new RPN_Function_MAX(this));
            addFunction(new RPN_Function_Minus(this));
            addFunction(new RPN_Function_MtoX(this));
            addFunction(new RPN_Function_Mult(this));
            addFunction(new RPN_Function_Neg(this));
            addFunction(new RPN_Function_NOP(this));
            addFunction(new RPN_Function_NOT(this));
            addFunction(new RPN_Function_OR(this));
            addFunction(new RPN_Function_pi(this));
            addFunction(new RPN_Function_Plus(this));
            addFunction(new RPN_Function_Prev(this));
            addFunction(new RPN_Function_RAND(this));
            addFunction(new RPN_Function_Rotate(this));
            addFunction(new RPN_Function_SEED(this));
            addFunction(new RPN_Function_SIGN(this));
            addFunction(new RPN_Function_SIN(this));
            addFunction(new RPN_Function_SQRT(this));
            addFunction(new RPN_Function_Swap(this));
            addFunction(new RPN_Function_TG(this));
            addFunction(new RPN_Function_ToDM(this));
            addFunction(new RPN_Function_ToDMS(this));
            addFunction(new RPN_Function_ToIN(this));
            addFunction(new RPN_Function_ToRAD(this));
            addFunction(new RPN_Function_x2(this));
            addFunction(new RPN_Function_XOR(this));
            addFunction(new RPN_Function_XpY(this));
            addFunction(new RPN_Function_XtoM(this));
        }
        #endregion

        #region Private Functions
        //
        // Padding value - will be moved to display function
        //
        private string presentValue(RPN_Value v)
        {
            return v.ToString().PadLeft(ScreenWidth);
        }

        #endregion
    }
}
