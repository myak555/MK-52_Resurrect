using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class RPN_Button
    {
        public int X = 0;
        public int Y = 0;
        public int sX = 40;
        public int sY = 30;
        public string Moniker = "Dummy";
        public string Letter = "";
        public string Register = "";

        /// <summary>
        /// Constructor
        /// </summary>
        public RPN_Button()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="X">Form location X</param>
        /// <param name="Y">Form Y</param>
        public RPN_Button(int X, int Y)
        {
            this.X = X;
            this.Y = Y;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="X">Form location X</param>
        /// <param name="Y">Form location Y</param>
        /// <param name="moniker">Moniker</param>
        public RPN_Button(int X, int Y, string moniker)
        {
            this.X = X;
            this.Y = Y;
            Moniker = moniker;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="X">Form location X</param>
        /// <param name="Y">Form location Y</param>
        /// <param name="moniker">Moniker</param>
        /// <param name="letter">Associated letter</param>
        public RPN_Button(int X, int Y, string moniker, string letter)
        {
            this.X = X;
            this.Y = Y;
            Moniker = moniker;
            Letter = letter;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="X">Form location X</param>
        /// <param name="Y">Form location Y</param>
        /// <param name="moniker">Moniker</param>
        /// <param name="letter">Associated letter</param>
        /// <param name="register">Associated register</param>
        public RPN_Button(int X, int Y, string moniker, string letter, string register)
        {
            this.X = X;
            this.Y = Y;
            Moniker = moniker;
            Letter = letter;
            Register = register;
        }

        /// <summary>
        /// Only for debug
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            if( Letter.Length <= 0) return Moniker;
            return Moniker + " [" + Letter + "]";
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
