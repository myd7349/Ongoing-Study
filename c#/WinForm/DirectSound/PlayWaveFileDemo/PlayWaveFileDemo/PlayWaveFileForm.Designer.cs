namespace PlayWaveFileDemo
{
    partial class PlayWaveFileForm
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
            this.deviceLabel_ = new System.Windows.Forms.Label();
            this.deviceComboBox_ = new System.Windows.Forms.ComboBox();
            this.refreshButton_ = new System.Windows.Forms.Button();
            this.fileLabel_ = new System.Windows.Forms.Label();
            this.filePathTextBox_ = new System.Windows.Forms.TextBox();
            this.selectFileButton_ = new System.Windows.Forms.Button();
            this.playOrStopButton_ = new System.Windows.Forms.Button();
            this.stopButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // deviceLabel_
            // 
            this.deviceLabel_.AutoSize = true;
            this.deviceLabel_.Location = new System.Drawing.Point(13, 13);
            this.deviceLabel_.Name = "deviceLabel_";
            this.deviceLabel_.Size = new System.Drawing.Size(47, 12);
            this.deviceLabel_.TabIndex = 0;
            this.deviceLabel_.Text = "Device:";
            // 
            // deviceComboBox_
            // 
            this.deviceComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox_.FormattingEnabled = true;
            this.deviceComboBox_.Location = new System.Drawing.Point(67, 11);
            this.deviceComboBox_.Name = "deviceComboBox_";
            this.deviceComboBox_.Size = new System.Drawing.Size(275, 20);
            this.deviceComboBox_.TabIndex = 1;
            this.deviceComboBox_.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox__SelectedIndexChanged);
            // 
            // refreshButton_
            // 
            this.refreshButton_.Location = new System.Drawing.Point(349, 10);
            this.refreshButton_.Name = "refreshButton_";
            this.refreshButton_.Size = new System.Drawing.Size(75, 23);
            this.refreshButton_.TabIndex = 2;
            this.refreshButton_.Text = "Refresh";
            this.refreshButton_.UseVisualStyleBackColor = true;
            this.refreshButton_.Click += new System.EventHandler(this.refreshButton__Click);
            // 
            // fileLabel_
            // 
            this.fileLabel_.AutoSize = true;
            this.fileLabel_.Location = new System.Drawing.Point(13, 46);
            this.fileLabel_.Name = "fileLabel_";
            this.fileLabel_.Size = new System.Drawing.Size(35, 12);
            this.fileLabel_.TabIndex = 3;
            this.fileLabel_.Text = "File:";
            // 
            // filePathTextBox_
            // 
            this.filePathTextBox_.Location = new System.Drawing.Point(67, 43);
            this.filePathTextBox_.Name = "filePathTextBox_";
            this.filePathTextBox_.ReadOnly = true;
            this.filePathTextBox_.Size = new System.Drawing.Size(275, 21);
            this.filePathTextBox_.TabIndex = 4;
            // 
            // selectFileButton_
            // 
            this.selectFileButton_.Location = new System.Drawing.Point(349, 42);
            this.selectFileButton_.Name = "selectFileButton_";
            this.selectFileButton_.Size = new System.Drawing.Size(75, 23);
            this.selectFileButton_.TabIndex = 5;
            this.selectFileButton_.Text = "...";
            this.selectFileButton_.UseVisualStyleBackColor = true;
            this.selectFileButton_.Click += new System.EventHandler(this.selectFileButton__Click);
            // 
            // playOrPauseButton_
            // 
            this.playOrStopButton_.Enabled = false;
            this.playOrStopButton_.Location = new System.Drawing.Point(67, 73);
            this.playOrStopButton_.Name = "playOrPauseButton_";
            this.playOrStopButton_.Size = new System.Drawing.Size(75, 23);
            this.playOrStopButton_.TabIndex = 6;
            this.playOrStopButton_.Text = "Play";
            this.playOrStopButton_.UseVisualStyleBackColor = true;
            this.playOrStopButton_.Click += new System.EventHandler(this.playOrStopButton__Click);
            // 
            // stopButton_
            // 
            this.stopButton_.Enabled = false;
            this.stopButton_.Location = new System.Drawing.Point(159, 73);
            this.stopButton_.Name = "stopButton_";
            this.stopButton_.Size = new System.Drawing.Size(75, 23);
            this.stopButton_.TabIndex = 7;
            this.stopButton_.Text = "Stop";
            this.stopButton_.UseVisualStyleBackColor = true;
            this.stopButton_.Click += new System.EventHandler(this.stopButton__Click);
            // 
            // PlayWaveFileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(436, 114);
            this.Controls.Add(this.stopButton_);
            this.Controls.Add(this.playOrStopButton_);
            this.Controls.Add(this.selectFileButton_);
            this.Controls.Add(this.filePathTextBox_);
            this.Controls.Add(this.fileLabel_);
            this.Controls.Add(this.refreshButton_);
            this.Controls.Add(this.deviceComboBox_);
            this.Controls.Add(this.deviceLabel_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PlayWaveFileForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Play Wave File";
            this.Load += new System.EventHandler(this.PlayWaveFileForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label deviceLabel_;
        private System.Windows.Forms.ComboBox deviceComboBox_;
        private System.Windows.Forms.Button refreshButton_;
        private System.Windows.Forms.Label fileLabel_;
        private System.Windows.Forms.TextBox filePathTextBox_;
        private System.Windows.Forms.Button selectFileButton_;
        private System.Windows.Forms.Button playOrStopButton_;
        private System.Windows.Forms.Button stopButton_;
    }
}
