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
            this.dataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buttonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recordButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pauseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.executeButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.loadButtonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveButtonsStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveButtonsAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.functionsListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.saveFileDialog2 = new System.Windows.Forms.SaveFileDialog();
            this.saveFileDialog3 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog2 = new System.Windows.Forms.OpenFileDialog();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.button_Record = new System.Windows.Forms.Button();
            this.button_Pause = new System.Windows.Forms.Button();
            this.button_Stop = new System.Windows.Forms.Button();
            this.button_Execute = new System.Windows.Forms.Button();
            this.button_CopyX = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.openFileDialog3 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog4 = new System.Windows.Forms.SaveFileDialog();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
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
            this.dataToolStripMenuItem,
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
            this.loadProgramToolStripMenuItem.Click += new System.EventHandler(this.programLoad_Click);
            // 
            // saveProgramToolStripMenuItem
            // 
            this.saveProgramToolStripMenuItem.Name = "saveProgramToolStripMenuItem";
            this.saveProgramToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveProgramToolStripMenuItem.Text = "&Save";
            this.saveProgramToolStripMenuItem.Click += new System.EventHandler(this.programSave_Click);
            // 
            // saveProgramAsToolStripMenuItem
            // 
            this.saveProgramAsToolStripMenuItem.Name = "saveProgramAsToolStripMenuItem";
            this.saveProgramAsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveProgramAsToolStripMenuItem.Text = "Save &As...";
            this.saveProgramAsToolStripMenuItem.Click += new System.EventHandler(this.programSaveAs_Click);
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
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.programExit_Click);
            // 
            // dataToolStripMenuItem
            // 
            this.dataToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadToolStripMenuItem,
            this.saveAsToolStripMenuItem});
            this.dataToolStripMenuItem.Name = "dataToolStripMenuItem";
            this.dataToolStripMenuItem.Size = new System.Drawing.Size(58, 27);
            this.dataToolStripMenuItem.Text = "&Data";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.loadToolStripMenuItem.Text = "&Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.dataLoad_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveAsToolStripMenuItem.Text = "&Save As...";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.dataSaveAs_Click);
            // 
            // buttonsToolStripMenuItem
            // 
            this.buttonsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.recordButtonsToolStripMenuItem,
            this.pauseToolStripMenuItem,
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
            this.recordButtonsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.recordButtonsToolStripMenuItem.Text = "&Record";
            this.recordButtonsToolStripMenuItem.Click += new System.EventHandler(this.recordButtonsToolStripMenuItem_Click);
            // 
            // pauseToolStripMenuItem
            // 
            this.pauseToolStripMenuItem.Name = "pauseToolStripMenuItem";
            this.pauseToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.pauseToolStripMenuItem.Text = "&Pause";
            this.pauseToolStripMenuItem.Click += new System.EventHandler(this.pauseToolStripMenuItem_Click);
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.stopToolStripMenuItem.Text = "&Stop";
            this.stopToolStripMenuItem.Click += new System.EventHandler(this.stopToolStripMenuItem_Click);
            // 
            // executeButtonsToolStripMenuItem
            // 
            this.executeButtonsToolStripMenuItem.Name = "executeButtonsToolStripMenuItem";
            this.executeButtonsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.executeButtonsToolStripMenuItem.Text = "&Execute";
            this.executeButtonsToolStripMenuItem.Click += new System.EventHandler(this.executeButtonsToolStripMenuItem_Click);
            // 
            // menuSeparator2
            // 
            this.menuSeparator2.Name = "menuSeparator2";
            this.menuSeparator2.Size = new System.Drawing.Size(147, 6);
            // 
            // loadButtonsToolStripMenuItem
            // 
            this.loadButtonsToolStripMenuItem.Name = "loadButtonsToolStripMenuItem";
            this.loadButtonsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.loadButtonsToolStripMenuItem.Text = "&Load";
            this.loadButtonsToolStripMenuItem.Click += new System.EventHandler(this.loadButtonsToolStripMenuItem_Click);
            // 
            // saveButtonsStripMenuItem
            // 
            this.saveButtonsStripMenuItem.Name = "saveButtonsStripMenuItem";
            this.saveButtonsStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveButtonsStripMenuItem.Text = "&Save";
            this.saveButtonsStripMenuItem.Click += new System.EventHandler(this.saveButtonsStripMenuItem_Click);
            // 
            // saveButtonsAsToolStripMenuItem
            // 
            this.saveButtonsAsToolStripMenuItem.Name = "saveButtonsAsToolStripMenuItem";
            this.saveButtonsAsToolStripMenuItem.Size = new System.Drawing.Size(150, 28);
            this.saveButtonsAsToolStripMenuItem.Text = "Save &As...";
            this.saveButtonsAsToolStripMenuItem.Click += new System.EventHandler(this.saveButtonsAsToolStripMenuItem_Click);
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
            // fontToolStripMenuItem
            // 
            this.fontToolStripMenuItem.Name = "fontToolStripMenuItem";
            this.fontToolStripMenuItem.Size = new System.Drawing.Size(153, 28);
            this.fontToolStripMenuItem.Text = "F&ont";
            this.fontToolStripMenuItem.Click += new System.EventHandler(this.fontToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "MK52";
            this.openFileDialog1.FileName = "Program";
            this.openFileDialog1.Filter = "MK52 Programs|*.mk52|All files|*.*";
            this.openFileDialog1.RestoreDirectory = true;
            this.openFileDialog1.Title = "Load program";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "MK52";
            this.saveFileDialog1.FileName = "Program_1";
            this.saveFileDialog1.Filter = "MK52 Programs|*.mk52|All files|*.*";
            this.saveFileDialog1.RestoreDirectory = true;
            this.saveFileDialog1.Title = "Save program";
            // 
            // saveFileDialog2
            // 
            this.saveFileDialog2.DefaultExt = "DAT";
            this.saveFileDialog2.FileName = "Data_1";
            this.saveFileDialog2.Filter = "MK52 Data|*.DAT|All files|*.*";
            this.saveFileDialog2.RestoreDirectory = true;
            this.saveFileDialog2.Title = "Save data";
            // 
            // saveFileDialog3
            // 
            this.saveFileDialog3.DefaultExt = "txt";
            this.saveFileDialog3.Filter = "Text files|*.txt|All files|*.*";
            this.saveFileDialog3.RestoreDirectory = true;
            this.saveFileDialog3.Title = "Save implemented  functions list";
            // 
            // openFileDialog2
            // 
            this.openFileDialog2.DefaultExt = "DAT";
            this.openFileDialog2.FileName = "Data";
            this.openFileDialog2.Filter = "Data Files|*.dat|MK52 Programs|*.mk52|All files|*.*";
            this.openFileDialog2.RestoreDirectory = true;
            this.openFileDialog2.Title = "Load data";
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            // 
            // button_Record
            // 
            this.button_Record.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Record.BackColor = System.Drawing.Color.LimeGreen;
            this.button_Record.FlatAppearance.BorderColor = System.Drawing.Color.LimeGreen;
            this.button_Record.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Coral;
            this.button_Record.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Record.Location = new System.Drawing.Point(386, 316);
            this.button_Record.Name = "button_Record";
            this.button_Record.Size = new System.Drawing.Size(75, 25);
            this.button_Record.TabIndex = 4;
            this.button_Record.Text = "Record";
            this.button_Record.UseVisualStyleBackColor = false;
            this.button_Record.Click += new System.EventHandler(this.button_Record_Click);
            // 
            // button_Pause
            // 
            this.button_Pause.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Pause.BackColor = System.Drawing.Color.LimeGreen;
            this.button_Pause.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Coral;
            this.button_Pause.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Pause.Location = new System.Drawing.Point(466, 316);
            this.button_Pause.Name = "button_Pause";
            this.button_Pause.Size = new System.Drawing.Size(75, 25);
            this.button_Pause.TabIndex = 5;
            this.button_Pause.Text = "Pause";
            this.button_Pause.UseVisualStyleBackColor = false;
            this.button_Pause.Click += new System.EventHandler(this.button_Pause_Click);
            // 
            // button_Stop
            // 
            this.button_Stop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Stop.BackColor = System.Drawing.Color.LimeGreen;
            this.button_Stop.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Coral;
            this.button_Stop.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Stop.Location = new System.Drawing.Point(546, 316);
            this.button_Stop.Name = "button_Stop";
            this.button_Stop.Size = new System.Drawing.Size(75, 25);
            this.button_Stop.TabIndex = 6;
            this.button_Stop.Text = "Stop";
            this.button_Stop.UseVisualStyleBackColor = false;
            this.button_Stop.Click += new System.EventHandler(this.button_Stop_Click);
            // 
            // button_Execute
            // 
            this.button_Execute.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Execute.BackColor = System.Drawing.Color.LimeGreen;
            this.button_Execute.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Coral;
            this.button_Execute.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_Execute.Location = new System.Drawing.Point(626, 316);
            this.button_Execute.Name = "button_Execute";
            this.button_Execute.Size = new System.Drawing.Size(75, 25);
            this.button_Execute.TabIndex = 7;
            this.button_Execute.Text = "Execute";
            this.button_Execute.UseVisualStyleBackColor = false;
            this.button_Execute.Click += new System.EventHandler(this.button_Execute_Click);
            // 
            // button_CopyX
            // 
            this.button_CopyX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button_CopyX.BackColor = System.Drawing.Color.LimeGreen;
            this.button_CopyX.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Coral;
            this.button_CopyX.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_CopyX.Location = new System.Drawing.Point(799, 316);
            this.button_CopyX.Name = "button_CopyX";
            this.button_CopyX.Size = new System.Drawing.Size(75, 25);
            this.button_CopyX.TabIndex = 8;
            this.button_CopyX.Text = "Copy X";
            this.button_CopyX.UseVisualStyleBackColor = false;
            this.button_CopyX.Click += new System.EventHandler(this.button_CopyX_Click);
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.Color.LimeGreen;
            this.label1.Location = new System.Drawing.Point(64, 319);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(277, 25);
            this.label1.TabIndex = 9;
            this.label1.Text = "Buttons recorded: 0";
            // 
            // openFileDialog3
            // 
            this.openFileDialog3.DefaultExt = "BTN";
            this.openFileDialog3.FileName = "Macro";
            this.openFileDialog3.Filter = "Macro Files|*.btn|All files|*.*";
            this.openFileDialog3.RestoreDirectory = true;
            this.openFileDialog3.Title = "Load keyboard macro";
            // 
            // saveFileDialog4
            // 
            this.saveFileDialog4.DefaultExt = "BTN";
            this.saveFileDialog4.FileName = "Macro_1";
            this.saveFileDialog4.Filter = "Macro files|*.btn|All files|*.*";
            this.saveFileDialog4.RestoreDirectory = true;
            this.saveFileDialog4.Title = "Save macro file";
            // 
            // radioButton1
            // 
            this.radioButton1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.radioButton1.AutoCheck = false;
            this.radioButton1.AutoSize = true;
            this.radioButton1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.radioButton1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.radioButton1.Location = new System.Drawing.Point(7, 322);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(13, 12);
            this.radioButton1.TabIndex = 10;
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.Click += new System.EventHandler(this.radioButton1_Click);
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
            this.ClientSize = new System.Drawing.Size(914, 345);
            this.Controls.Add(this.radioButton1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_CopyX);
            this.Controls.Add(this.button_Execute);
            this.Controls.Add(this.button_Stop);
            this.Controls.Add(this.button_Pause);
            this.Controls.Add(this.button_Record);
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
        private System.Windows.Forms.ToolStripMenuItem dataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog2;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button button_Record;
        private System.Windows.Forms.Button button_Pause;
        private System.Windows.Forms.Button button_Stop;
        private System.Windows.Forms.Button button_Execute;
        private System.Windows.Forms.Button button_CopyX;
        private System.Windows.Forms.ToolStripMenuItem pauseToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog openFileDialog3;
        private System.Windows.Forms.SaveFileDialog saveFileDialog4;
        private System.Windows.Forms.RadioButton radioButton1;
    }
}

