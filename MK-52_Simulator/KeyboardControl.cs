using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace MK52Simulator
{
    public partial class KeyboardControl : UserControl
    {
        private List<RPN_Button> m_Buttons = new List<RPN_Button>();
        private Queue<RPN_Button> m_ButtonsPressed = new Queue<RPN_Button>();

        public KeyboardControl()
        {
            InitializeComponent();

            // Buttons by columns:

            m_Buttons.Add(new RPN_Button(40,  30, "Func F")); // Modal F button
            m_Buttons.Add(new RPN_Button(40,  97, "Func K")); // Modal K button
            m_Buttons.Add(new RPN_Button(40, 160, "Mode")); // Modal "ââ" button (degs-rads-grads and code/text/addr)
            m_Buttons.Add(new RPN_Button(40, 223, "Func A")); // Modal A button

            m_Buttons.Add(new RPN_Button(105,  30, "->", "A")); // "->", "IF x<0 GOTO "
            m_Buttons.Add(new RPN_Button(105,  97, "<-", "H")); // "<-", "IF x=0 GOTO "
            m_Buttons.Add(new RPN_Button(105, 160, "B/O", "O")); // "B/O", "IF x>=0 GOTO "
            m_Buttons.Add(new RPN_Button(105, 223, "S/P", "V")); // "S/P", "IF x!=0 GOTO "

            m_Buttons.Add(new RPN_Button(165,  30, "M->X", "B", "L0")); // "M->X", "L0"
            m_Buttons.Add(new RPN_Button(165,  97, "X->M", "I", "L1")); // "X->M", "L1"
            m_Buttons.Add(new RPN_Button(165, 160, "GOTO", "P", "L2")); // "GOTO", "L2"
            m_Buttons.Add(new RPN_Button(165, 223, "GOSUB", "W", "L3")); // "GOSUB", "L3"

            m_Buttons.Add(new RPN_Button(230,  30, "7", "C", "7")); // "7", "SIN", "[X]"
            m_Buttons.Add(new RPN_Button(230,  97, "4", "J", "4")); // "4", "arcSIN", "|X|"
            m_Buttons.Add(new RPN_Button(230, 160, "1", "Q", "1")); // "1", "EXP", "e"
            m_Buttons.Add(new RPN_Button(230, 223, "0", "X", "0")); // "0", "10^X", "NOP"

            m_Buttons.Add(new RPN_Button(295,  30, "8", "D", "8")); // "8", "COS", "{X}"
            m_Buttons.Add(new RPN_Button(295,  97, "5", "K", "5")); // "5", "arcCOS", "SIGN";
            m_Buttons.Add(new RPN_Button(295, 160, "2", "R", "2")); // "2", "LG", "LOG"
            m_Buttons.Add(new RPN_Button(295, 223, ".", "Y", "A")); // ".", "Rotate", "AND"

            m_Buttons.Add(new RPN_Button(360,  30, "9", "E", "9")); // "9", "TG", "MAX"
            m_Buttons.Add(new RPN_Button(360,  97, "6", "L", "6")); // "6", "arcTG", "<-DM", "<-RAD"
            m_Buttons.Add(new RPN_Button(360, 160, "3", "S", "3"));// "3", "LN", "<-DMS", "<-IN"
            m_Buttons.Add(new RPN_Button(360, 223, "/-/", "Z", "B")); // "/-/", "ÀÂÒ", "OR"

            m_Buttons.Add(new RPN_Button(420,  30, "-", "F")); // "SQRT"
            m_Buttons.Add(new RPN_Button(420,  97, "+", "M")); // "pi", "DM->", "RAD->"
            m_Buttons.Add(new RPN_Button(420, 160, "Swap", "T")); // "X^Y", "DMS->", "IN->"
            m_Buttons.Add(new RPN_Button(420, 223, "EE", "#", "C")); // "ÂÏ", "ÏÐÃ", "XOR", "LIST"

            m_Buttons.Add(new RPN_Button(485,  30, "/", "G")); // "/", "1/X"
            m_Buttons.Add(new RPN_Button(485,  97, "*", "F", "F")); // "X^2"
            m_Buttons.Add(new RPN_Button(485, 160, "Enter", "U", "E")); //  "Bx", "RAND", "SEED"
            m_Buttons.Add(new RPN_Button(485, 223, "Cx", "", "D")); // "Cx", "Cf", "NOT"
        }

        public bool Available()
        {
            return m_ButtonsPressed.Count > 0;
        }

        public RPN_Button GetButton()
        {
            if( m_ButtonsPressed.Count < 1) return null;
            return m_ButtonsPressed.Dequeue();
        }

        private void KeyboardControl_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            foreach (RPN_Button rpb in m_Buttons)
            {
                if (!rpb.isPressed(e.X, e.Y)) continue;
                m_ButtonsPressed.Enqueue(rpb);
                return;
            }
        }
    }
}
