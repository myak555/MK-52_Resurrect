using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class MK52_Button
    {
        public int X = 0;
        public int Y = 0;
        public int sX = 40;
        public int sY = 30;
        public int Scancode;
        public string Moniker;

        /// <summary>
        /// Constructor
        /// </summary>
        public MK52_Button()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="X">Form location X</param>
        /// <param name="Y">Form location Y</param>
        /// <param name="Scancode">Scancode 1-33</param>
        /// <param name="Moniker">Human name</param>
        public MK52_Button(int X, int Y, int Scancode, string Moniker)
        {
            this.X = X;
            this.Y = Y;
            this.Scancode = Scancode;
            this.Moniker = Moniker;
        }

        /// <summary>
        /// Only for debug
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Moniker + " [" + Scancode.ToString("00") + "]";
        }

        /// <summary>
        /// Checks if button is pressed (only for PC mockup)
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool isPressed(int x, int y)
        {
            if (x < this.X) return false;
            if (y < this.Y) return false;
            if (x > this.X + sX) return false;
            if (y > this.Y + sY) return false;
            return true;
        }
    }
}
