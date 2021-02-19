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
using System.IO;

namespace MK52Simulator
{
    //
    // Implements the RPN stack
    //
    public class RPN_Stack
    {
        private const string _RPN_Stack_TrigAccuracy = "Warn: Trig Accuracy";
        private const string _RPN_Stack_ComplexRoot = "Warn: Complex";
        public const int RPN_STACK_SIZE = 4;
        public const int DMODE_DEGREES = 0;
        public const int DMODE_RADIANS = 1;
        public const int DMODE_GRADS = 2;

        private static double[] _DMODE_ConversionsToRadian = {1.7453292519943295e-2, 1.0, 1.5707963267948967e-2};
        private static double[] _DMODE_ConversionsFromRadian = {57.29577951308232, 1.0, 63.66197723675813};

        private string[] _standardLabels = { "X:", "Y:", "Z:", "T:" };
        private string[] _dmodeLabels = { "DEG", "RAD", "GRD" };
        private int _dMode = DMODE_DEGREES;
        private string[] _stackLabels = new string[RPN_STACK_SIZE];
        private List<UniversalValue> _stackValues = new List<UniversalValue>();

        public void init( MK52_Host parent)
        {
            for (int i = 0; i <= RPN_STACK_SIZE; i++)
                _stackValues.Add(new UniversalValue());
            clearStack();
            resetStackLabels();
            setDMode( DMODE_DEGREES);
        }

        #region Fake Variables
        public UniversalValue Bx
        {
            get{ return _stackValues[0];}
        }

        public UniversalValue X
        {
            get{ return _stackValues[1];}
        }

        public UniversalValue Y
        {
            get{ return _stackValues[2];}
        }

        public UniversalValue Z
        {
            get{ return _stackValues[3];}
        }

        public UniversalValue T
        {
            get{ return _stackValues[4];}
        }

        public string X_Label
        {
            get{ return _stackLabels[0];}
        }

        public string Y_Label
        {
            get{ return _stackLabels[1];}
        }

        public string Z_Label
        {
            get{ return _stackLabels[2];}
        }

        public string T_Label
        {
            get{ return _stackLabels[3];}
        }
        #endregion

        public void clearStack()
        {
            Bx.fromInt(0L);
            X.fromInt(0L);
            Y.fromInt(0L);
            Z.fromInt(0L);
            T.fromInt(0L);
        }

        public void resetStackLabels()
        {
            for( int i=0; i<4; i++)
                _stackLabels[i] = _standardLabels[i];
        }

        public bool customStackLabels()
        {
            for( int i=0; i<4; i++)
            {
                if( _stackLabels[i] != _standardLabels[i]) return true;
            }
            return false;
        }

        public void setStackLabel(int n, string text)
        {
            setStackLabel_P(n, text);
        }

        public void setStackLabel_P(int n, string text)
        {
            if( n < 0 || 3 < n) return;
            if (text.Length < LCD_Manager.SCREEN_COLS - 1)
                _stackLabels[n] = text;
            else
                _stackLabels[n] = text.Substring(0, LCD_Manager.SCREEN_COLS-1);
        }

        public int getDMode()
        {
            return _dMode;
        }

        public string getDModeName()
        {
            return _dmodeLabels[_dMode];
        } 

        public void setDMode(int m)
        {
            if( m > DMODE_GRADS) m = DMODE_DEGREES;
            _dMode = m;
        } 

        public int toggleAngleMode()
        {
            setDMode( _dMode+1);
            return _dMode;
        } 

        public void push()
        {
            push(1);
        }

        public void push( uint start)
        {
            for( int i=RPN_STACK_SIZE; i>start; i--)
                _stackValues[i].fromLocation( _stackValues[i-1]);
        }

        public void pop()
        {
            pop(1);
        }

        public void pop( uint start)
        {
            for( int i=(int)start; i<RPN_STACK_SIZE; i++)
                _stackValues[i].fromLocation( _stackValues[i+1]);
        }

        public void storeBx()
        {
            Bx.fromLocation( X); 
        }

        public void swap()
        {
            Bx.fromLocation( X);
            X.fromLocation( Y);
            Y.fromLocation( Bx);
        }

        public void rotate()
        {
            pop( 0);
            T.fromLocation( Bx); 
        }

        public double XtoRadian()
        {
            double tmp = X.toReal();
            // prevents precision loss for angles such as 36000000000045
            if (X.isInt())
            {
                if (_dMode == DMODE_DEGREES) tmp = (double)(X.toInt() % 360);
                if (_dMode == DMODE_DEGREES) tmp = (double)(X.toInt() % 400);
            }
            return tmp * _DMODE_ConversionsToRadian[_dMode];
        }

        public int XtoOctant()
        {
            if( _dMode == DMODE_RADIANS) return -1;
            if( X.isEmpty()) return -1;
            if( X.isReal()) return -1;
            Int64 octant = (_dMode==DMODE_GRADS)? 50L: 45L;
            Int64 result = X.toInt();
            if( result % octant != 0) return -1;
            result /= octant;
            result %= 8;
            if( result < 0L) result += 8L;
            return (int)result;
        }

        public void RadianToX(double value)
        {
            X.fromReal( value * _DMODE_ConversionsFromRadian[_dMode]);
            // in case of degrees and grads, need to round-up higher, to account for the Radian conversion
            if( _dMode != DMODE_RADIANS) X._checkRounding( UniversalValue.__ROUNDING_ACCURACY * 0.01);
        }

        public void OctantToX(int value)
        {
            switch( _dMode){
                case DMODE_DEGREES:
                    X.fromInt( value * 45);
                    break;
                case DMODE_GRADS:
                    X.fromInt( value * 50);
                    break;
                default:
                    X.fromReal( UniversalValue.__PI4 * value);
                    break;
            }
        }

        //
        // value in radians
        // if outside of -1e12 to 1e12 range, perioodic functions lose precision
        //
        public void setTrigAccuracyWarning(double value)
        {
            if( -1e12 <= value && value <= 1e12) return;
            setStackLabel_P(0, _RPN_Stack_TrigAccuracy);
        }

        public bool setNegativeRootWarning(double value)
        {
            if( value >= 0) return false;
            setStackLabel_P(0, _RPN_Stack_ComplexRoot);
            return true;
        }
    }
}
