using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator.Displays;

namespace MK52Simulator
{
    //
    // Implements the calculator display in auto mode
    //
    public class RPN_Display
    {
        public const int ScreenWidth = 25;
        public const int StatusWidth = 37;

        private RPN_Calculator _source = null;
        private ScreenControl _screen = null;
        private string[] _screenValues = new string[9];

        public RPN_Display(RPN_Calculator source, ScreenControl screen)
        {
            _source = source;
            _screen = screen;
        }

        public void Redraw()
        {
            _source.CurrentReceiver.Display.setScreenValues(_screenValues); 
            for (int i = 0; i < _screenValues.Length; i++)
                _screen.PlaceText(_screenValues[i], i, 0);
        }
    }
}
