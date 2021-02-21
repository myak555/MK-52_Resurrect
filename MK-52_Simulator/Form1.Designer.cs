namespace MK52Simulator
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.programToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadProgramToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveProgramToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveProgramAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buttonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recordButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.executeButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.loadButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveButtonsStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveButtonsAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.functionsListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.saveFileDialog2 = new System.Windows.Forms.SaveFileDialog();
            this.saveFileDialog3 = new System.Windows.Forms.SaveFileDialog();
            this.fontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.LCD_Manager1 = new MK52Simulator.LCD_Manager();
            this.KBD_Manager1 = new MK52Simulator.KBD_Manager();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 30;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.programToolStripMenuItem,
            this.buttonsToolStripMenuItem,
            this.listToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(914, 31);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // programToolStripMenuItem
            // 
            this.programToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadProgramToolStripMenuItem,
            this.saveProgramToolStripMenuItem,
            this.saveProgramAsToolStripMenuItem,
            this.menuSeparator1,
            this.exitToolStripMenuItem});
            this.programToolStripMenuItem.Name = "programToolStripMenuItem";
            this.programToolStripMenuItem.Size = new System.Drawing.Size(88, 27);
            this.programToolStripMenuItem.Text = "&Program";
            // 
            // loadProgramToolStripMenuItem
            // 
            this.loadProgramToolStripMenuItem.Name = "loadProgramToolStripMenuItem";
            this.loadProgramToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.loadProgramToolStripMenuItem.Text = "&Load";
            this.loadProgramToolStripMenuItem.Click += new System.EventHandler(this.loadProgramToolStripMenuItem_Click);
            // 
            // saveProgramToolStripMenuItem
            // 
            this.saveProgramToolStripMenuItem.Name = "saveProgramToolStripMenuItem";
            this.saveProgramToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveProgramToolStripMenuItem.Text = "&Save";
            this.saveProgramToolStripMenuItem.Click += new System.EventHandler(this.saveProgramToolStripMenuItem_Click);
            // 
            // saveProgramAsToolStripMenuItem
            // 
            this.saveProgramAsToolStripMenuItem.Name = "saveProgramAsToolStripMenuItem";
            this.saveProgramAsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveProgramAsToolStripMenuItem.Text = "Save &As...";
            this.saveProgramAsToolStripMenuItem.Click += new System.EventHandler(this.saveProgramAsToolStripMenuItem_Click);
            // 
            // menuSeparator1
            // 
            this.menuSeparator1.Name = "menuSeparator1";
            this.menuSeparator1.Size = new System.Drawing.Size(147, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // buttonsToolStripMenuItem
            // 
            this.buttonsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.recordButtonsToolStripMenuItem,
            this.stopToolStripMenuItem,
            this.executeButtonsToolStripMenuItem,
            this.menuSeparator2,
            this.loadButtonsToolStripMenuItem,
            this.saveButtonsStripMenuItem,
            this.saveButtonsAsToolStripMenuItem});
            this.buttonsToolStripMenuItem.Name = "buttonsToolStripMenuItem";
            this.buttonsToolStripMenuItem.Size = new System.Drawing.Size(81, 27);
            this.buttonsToolStripMenuItem.Text = "&Buttons";
            // 
            // recordButtonsToolStripMenuItem
            // 
            this.recordButtonsToolStripMenuItem.Name = "recordButtonsToolStripMenuItem";
            this.recordButtonsToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.recordButtonsToolStripMenuItem.Text = "&Record";
            this.recordButtonsToolStripMenuItem.Click += new System.EventHandler(this.recordButtonsToolStripMenuItem_Click);
            // 
            // executeButtonsToolStripMenuItem
            // 
            this.executeButtonsToolStripMenuItem.Name = "executeButtonsToolStripMenuItem";
            this.executeButtonsToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.executeButtonsToolStripMenuItem.Text = "&Execute";
            // 
            // menuSeparator2
            // 
            this.menuSeparator2.Name = "menuSeparator2";
            this.menuSeparator2.Size = new System.Drawing.Size(149, 6);
            // 
            // loadButtonsToolStripMenuItem
            // 
            this.loadButtonsToolStripMenuItem.Name = "loadButtonsToolStripMenuItem";
            this.loadButtonsToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.loadButtonsToolStripMenuItem.Text = "&Load";
            // 
            // saveButtonsStripMenuItem
            // 
            this.saveButtonsStripMenuItem.Name = "saveButtonsStripMenuItem";
            this.saveButtonsStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.saveButtonsStripMenuItem.Text = "&Save";
            // 
            // saveButtonsAsToolStripMenuItem
            // 
            this.saveButtonsAsToolStripMenuItem.Name = "saveButtonsAsToolStripMenuItem";
            this.saveButtonsAsToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.saveButtonsAsToolStripMenuItem.Text = "Save &As...";
            // 
            // listToolStripMenuItem
            // 
            this.listToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.functionsListToolStripMenuItem,
            this.fontToolStripMenuItem});
            this.listToolStripMenuItem.Name = "listToolStripMenuItem";
            this.listToolStripMenuItem.Size = new System.Drawing.Size(47, 27);
            this.listToolStripMenuItem.Text = "&List";
            // 
            // functionsListToolStripMenuItem
            // 
            this.functionsListToolStripMenuItem.Name = "functionsListToolStripMenuItem";
            this.functionsListToolStripMenuItem.Size = new System.Drawing.Size(153, 28);
            this.functionsListToolStripMenuItem.Text = "&Functions";
            this.functionsListToolStripMenuItem.Click += new System.EventHandler(this.functionsListToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "MK52";
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "MK52 Programs|*.mk52|All files|*.*";
            this.openFileDialog1.RestoreDirectory = true;
            this.openFileDialog1.Title = "Load program";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "MK52";
            this.saveFileDialog1.Filter = "MK52 Programs|*.mk52|All files|*.*";
            this.saveFileDialog1.RestoreDirectory = true;
            this.saveFileDialog1.Title = "Save program";
            // 
            // saveFileDialog2
            // 
            this.saveFileDialog2.DefaultExt = "MK52";
            this.saveFileDialog2.Filter = "MK52 Programs|*.mk52|All files|*.*";
            this.saveFileDialog2.RestoreDirectory = true;
            this.saveFileDialog2.Title = "Save program";
            // 
            // saveFileDialog3
            // 
            this.saveFileDialog3.DefaultExt = "txt";
            this.saveFileDialog3.Filter = "Text files|*.txt|All files|*.*";
            this.saveFileDialog3.RestoreDirectory = true;
            this.saveFileDialog3.Title = "Save implemented  functions list";
            // 
            // fontToolStripMenuItem
            // 
            this.fontToolStripMenuItem.Name = "fontToolStripMenuItem";
            this.fontToolStripMenuItem.Size = new System.Drawing.Size(153, 28);
            this.fontToolStripMenuItem.Text = "F&ont";
            this.fontToolStripMenuItem.Click += new System.EventHandler(this.fontToolStripMenuItem_Click);
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            this.stopToolStripMenuItem.Text = "Sto&p";
            // 
            // LCD_Manager1
            // 
            this.LCD_Manager1.BackColor = System.Drawing.Color.DimGray;
            this.LCD_Manager1.ForeColor = System.Drawing.SystemColors.ControlLight;
            this.LCD_Manager1.Location = new System.Drawing.Point(5, 35);
            this.LCD_Manager1.Name = "LCD_Manager1";
            this.LCD_Manager1.Size = new System.Drawing.Size(340, 275);
            this.LCD_Manager1.TabIndex = 3;
            // 
            // KBD_Manager1
            // 
            this.KBD_Manager1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("KBD_Manager1.BackgroundImage")));
            this.KBD_Manager1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.KBD_Manager1.Location = new System.Drawing.Point(350, 35);
            this.KBD_Manager1.Name = "KBD_Manager1";
            this.KBD_Manager1.Size = new System.Drawing.Size(560, 275);
            this.KBD_Manager1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(914, 315);
            this.Controls.Add(this.LCD_Manager1);
            this.Controls.Add(this.KBD_Manager1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "MK-52";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private KBD_Manager KBD_Manager1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem programToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadProgramToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveProgramToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveProgramAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator menuSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buttonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem recordButtonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadButtonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveButtonsAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem executeButtonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator menuSeparator2;
        private System.Windows.Forms.ToolStripMenuItem saveButtonsStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem listToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem functionsListToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog2;
        private System.Windows.Forms.SaveFileDialog saveFileDialog3;
        private LCD_Manager LCD_Manager1;
        private System.Windows.Forms.ToolStripMenuItem fontToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem;
    }
}

