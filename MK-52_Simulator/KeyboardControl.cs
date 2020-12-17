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
        private List<Button> m_Buttons = new List<Button>();
        private Queue<Button> m_ButtonsPressed = new Queue<Button>();

        public KeyboardControl()
        {
            InitializeComponent();

            // Buttons by columns:

            m_Buttons.Add(new FunctionButton_F(40, 30)); // Special F button
            m_Buttons.Add(new FunctionButton_K(40, 97)); // Special K button
            m_Buttons.Add(new FunctionButton_M(40,160)); // Special "‚‚" button (degs-rads-grads)
            m_Buttons.Add(new FunctionButton_A(40,223)); // Special A button

            m_Buttons.Add(new Button(105, 30, "ÿ√>", "x<0")); // TODO
            m_Buttons.Add(new Button(105, 97, "<ÿ√", "x=0")); // TODO
            m_Buttons.Add(new Button(105, 160, "¬/Œ", "x>=0")); // TODO
            m_Buttons.Add(new Button(105, 223, "—/œ", "x!=0")); // TODO

            m_Buttons.Add(new Button(165, 30, "M->X", "L0", "", "", "L0")); // TODO
            m_Buttons.Add(new Button(165, 97, "X->M", "L1", "", "", "L1")); // TODO
            m_Buttons.Add(new Button(165, 160, "¡œ", "L2", "", "", "L2")); // TODO
            m_Buttons.Add(new Button(165, 223, "œœ", "L3", "", "", "L3")); // TODO

            m_Buttons.Add(new DigitButton_0_to_9(230, 30, "7", "SIN", "[X]"));
            m_Buttons.Add(new DigitButton_0_to_9(230, 97, "4", "arcSIN", "|X|"));
            m_Buttons.Add(new DigitButton_0_to_9(230,160, "1", "EXP", "e"));
            m_Buttons.Add(new DigitButton_0_to_9(230,223, "0", "10^X", "NOP"));

            m_Buttons.Add(new DigitButton_0_to_9(295, 30, "8", "COS", "{X}"));
            m_Buttons.Add(new DigitButton_0_to_9(295, 97, "5", "arcCOS", "SIGN"));
            m_Buttons.Add(new DigitButton_0_to_9(295,160, "2", "LG", "LOG"));
            m_Buttons.Add(new DigitButton_Decimal(295, 223)); // ".", "Rotate", "AND"

            m_Buttons.Add(new DigitButton_0_to_9(360, 30, "9", "TG", "MAX"));
            m_Buttons.Add(new DigitButton_0_to_9(360, 97, "6", "arcTG", "<-DM", "<-RAD"));
            m_Buttons.Add(new DigitButton_0_to_9(360,160, "3", "LN", "<-DMS", "<-IN"));
            m_Buttons.Add(new DigitButton_Negative(360, 223)); // "/-/", "¿¬“", "OR"

            m_Buttons.Add(new Button(420,  30, "-", "SQRT", "", ""));
            m_Buttons.Add(new Button(420, 97, "+", "pi", "DM->", "RAD->"));
            m_Buttons.Add(new Button(420, 160, "Swap", "X^Y", "DMS->", "IN->"));
            m_Buttons.Add(new DigitButton_Exponent(420, 223)); // "¬œ", "œ–√", "XOR"

            m_Buttons.Add(new Button(485, 30, "/", "1/X"));
            m_Buttons.Add(new Button(485,  97, "*", "X^2", "", "", "F"));
            m_Buttons.Add(new Button(485, 160, "Enter", "Bx", "RAND", "SEED", "E"));
            m_Buttons.Add(new FunctionButton_Cx(485, 223)); // "Cx", "Cf", "1/X", "D"
        }

        public bool Available()
        {
            return m_ButtonsPressed.Count > 0;
        }

        public Button GetButton()
        {
            if( m_ButtonsPressed.Count < 1) return null;
            return m_ButtonsPressed.Dequeue();
        }

        private void KeyboardControl_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            foreach (Button sb in m_Buttons)
            {
                if (!sb.isPressed(e.X, e.Y)) continue;
                m_ButtonsPressed.Enqueue(sb);
                return;
            }
        }
    }
}
