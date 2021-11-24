namespace ShowTips
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.textBox_ = new System.Windows.Forms.TextBox();
            this.showToolTipbutton_ = new System.Windows.Forms.Button();
            this.balloonCheckBox_ = new System.Windows.Forms.CheckBox();
            this.toolTip_ = new System.Windows.Forms.ToolTip(this.components);
            this.notifyIcon_ = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip_ = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBox_
            // 
            this.textBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_.Location = new System.Drawing.Point(12, 12);
            this.textBox_.Multiline = true;
            this.textBox_.Name = "textBox_";
            this.textBox_.Size = new System.Drawing.Size(406, 173);
            this.textBox_.TabIndex = 0;
            this.textBox_.Text = "Hello, world!";
            // 
            // showToolTipbutton_
            // 
            this.showToolTipbutton_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.showToolTipbutton_.Location = new System.Drawing.Point(12, 224);
            this.showToolTipbutton_.Name = "showToolTipbutton_";
            this.showToolTipbutton_.Size = new System.Drawing.Size(406, 33);
            this.showToolTipbutton_.TabIndex = 1;
            this.showToolTipbutton_.Text = "Say It";
            this.showToolTipbutton_.UseVisualStyleBackColor = true;
            this.showToolTipbutton_.Click += new System.EventHandler(this.showToolTipbutton__Click);
            // 
            // balloonCheckBox_
            // 
            this.balloonCheckBox_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.balloonCheckBox_.AutoSize = true;
            this.balloonCheckBox_.Location = new System.Drawing.Point(12, 197);
            this.balloonCheckBox_.Name = "balloonCheckBox_";
            this.balloonCheckBox_.Size = new System.Drawing.Size(90, 16);
            this.balloonCheckBox_.TabIndex = 2;
            this.balloonCheckBox_.Text = "Is Balloon?";
            this.balloonCheckBox_.UseVisualStyleBackColor = true;
            this.balloonCheckBox_.CheckedChanged += new System.EventHandler(this.balloonCheckBox__CheckedChanged);
            // 
            // notifyIcon_
            // 
            this.notifyIcon_.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.notifyIcon_.ContextMenuStrip = this.contextMenuStrip_;
            this.notifyIcon_.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon_.Icon")));
            this.notifyIcon_.Visible = true;
            this.notifyIcon_.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon__MouseDoubleClick);
            // 
            // contextMenuStrip_
            // 
            this.contextMenuStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.contextMenuStrip_.Name = "contextMenuStrip_";
            this.contextMenuStrip_.Size = new System.Drawing.Size(97, 26);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(430, 269);
            this.Controls.Add(this.balloonCheckBox_);
            this.Controls.Add(this.showToolTipbutton_);
            this.Controls.Add(this.textBox_);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Main Form";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.contextMenuStrip_.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_;
        private System.Windows.Forms.Button showToolTipbutton_;
        private System.Windows.Forms.CheckBox balloonCheckBox_;
        private System.Windows.Forms.ToolTip toolTip_;
        private System.Windows.Forms.NotifyIcon notifyIcon_;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip_;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    }
}

