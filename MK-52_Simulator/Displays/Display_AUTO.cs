using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in auto mode
    //
    public class Display_AUTO : Display
    {
        public Display_AUTO(MK52_Host parent):
            base( parent)
        {
            Moniker = "AUTO";
        }

        public override string activate()
        {
            if (_parent.current_Display.Moniker == this.Moniker)
                return "Nothing";
            _parent.LCD.clearScreen();
            _outputGenericStatus();
            _parent.LCD.outputCalcLabel(3, _parent.CalcStack.T_Label);
            _parent.LCD.outputCalcLabel(2, _parent.CalcStack.Z_Label);
            _parent.LCD.outputCalcLabel(1, _parent.CalcStack.Y_Label);
            _parent.LCD.outputCalcLabel(0, _parent.CalcStack.X_Label);
            if (_parent.CalcStack.T.isInt)
                _parent.LCD.outputCalcRegister(3, UniversalValue._composeInt64( _parent.CalcStack.T.asInt));
            else
                _parent.LCD.outputCalcRegister(3, UniversalValue._composeDouble(_parent.CalcStack.T.asReal));
            if (_parent.CalcStack.Z.isInt)
                _parent.LCD.outputCalcRegister(2, UniversalValue._composeInt64( _parent.CalcStack.Z.asInt));
            else
                _parent.LCD.outputCalcRegister(2, UniversalValue._composeDouble(_parent.CalcStack.Z.asReal));
            if (_parent.CalcStack.Y.isInt)
                _parent.LCD.outputCalcRegister(1, UniversalValue._composeInt64( _parent.CalcStack.Y.asInt));
            else
                _parent.LCD.outputCalcRegister(1, UniversalValue._composeDouble(_parent.CalcStack.Y.asReal));
            if (_parent.CalcStack.X.isInt)
                _parent.LCD.outputCalcRegister(0, UniversalValue._composeInt64( _parent.CalcStack.X.asInt));
            else
                _parent.LCD.outputCalcRegister(0, UniversalValue._composeDouble(_parent.CalcStack.X.asReal));
            _parent.LCD.Refresh();
            return "AUTO_N";
        }

        public override void tick()
        {
            _updateGenericStatus();
            _parent.LCD.updateCalcLabel(3, _parent.CalcStack.T_Label);
            _parent.LCD.updateCalcLabel(2, _parent.CalcStack.Z_Label);
            _parent.LCD.updateCalcLabel(1, _parent.CalcStack.Y_Label);
            _parent.LCD.updateCalcLabel(0, _parent.CalcStack.X_Label);
            if (_parent.CalcStack.T.isInt)
                _parent.LCD.updateCalcRegister(3, UniversalValue._composeInt64(_parent.CalcStack.T.asInt));
            else
                _parent.LCD.updateCalcRegister(3, UniversalValue._composeDouble(_parent.CalcStack.T.asReal));
            if (_parent.CalcStack.Z.isInt)
                _parent.LCD.updateCalcRegister(2, UniversalValue._composeInt64(_parent.CalcStack.Z.asInt));
            else
                _parent.LCD.updateCalcRegister(2, UniversalValue._composeDouble(_parent.CalcStack.Z.asReal));
            if (_parent.CalcStack.Y.isInt)
                _parent.LCD.updateCalcRegister(1, UniversalValue._composeInt64(_parent.CalcStack.Y.asInt));
            else
                _parent.LCD.updateCalcRegister(1, UniversalValue._composeDouble(_parent.CalcStack.Y.asReal));
            if (_parent.CalcStack.isActive)
            {
                _parent.LCD.updateCalcRegister(0, _parent.CalcStack.activeEntry);
                _parent.LCD.Refresh();
                return;
            }
            if (_parent.CalcStack.X.isInt)
                _parent.LCD.updateCalcRegister(0, UniversalValue._composeInt64(_parent.CalcStack.X.asInt));
            else
                _parent.LCD.updateCalcRegister(0, UniversalValue._composeDouble(_parent.CalcStack.X.asReal));
            _parent.LCD.Refresh();
            return;
        }

        #region Private Functions
        private void makeBody(LCD_Manager target)
        {
            target.outputCalcLabel(3, _parent.CalcStack.T_Label);
            target.outputCalcLabel(2, _parent.CalcStack.Z_Label);
            target.outputCalcLabel(1, _parent.CalcStack.Y_Label);
            target.outputCalcLabel(0, _parent.CalcStack.X_Label);
            if( _parent.CalcStack.T.isInt)
                target.outputCalcRegister(3, UniversalValue._composeInt64(_parent.CalcStack.T.asInt));
            else
                target.outputCalcRegister(3, UniversalValue._composeDouble(_parent.CalcStack.T.asReal));
            if (_parent.CalcStack.Z.isInt)
                target.outputCalcRegister(2, UniversalValue._composeInt64(_parent.CalcStack.Z.asInt));
            else
                target.outputCalcRegister(2, UniversalValue._composeDouble(_parent.CalcStack.Z.asReal));
            if (_parent.CalcStack.Y.isInt)
                target.outputCalcRegister(1, UniversalValue._composeInt64(_parent.CalcStack.Y.asInt));
            else
                target.outputCalcRegister(1, UniversalValue._composeDouble(_parent.CalcStack.Y.asReal));
            //if( _parent.CalcStack
            //target.outputCalcRegister(0, _parent.CalcStack.XasInt);
            //else
            //    target.outputCalcRegister(0, _parent.CalcStack.X.asReal);
        }
        #endregion
    }
}
