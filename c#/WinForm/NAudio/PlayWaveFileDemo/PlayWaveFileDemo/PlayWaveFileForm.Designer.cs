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
            this.playOrPauseButton_ = new System.Windows.Forms.Button();
            this.stopButton_ = new System.Windows.Forms.Button();
            this.propertiesButton_ = new System.Windows.Forms.Button();
            this.drcCheckBox_ = new System.Windows.Forms.CheckBox();
            this.volumeLabel_ = new System.Windows.Forms.Label();
            this.volumeTrackBar_ = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.volumeTrackBar_)).BeginInit();
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
            this.playOrPauseButton_.Enabled = false;
            this.playOrPauseButton_.Location = new System.Drawing.Point(67, 158);
            this.playOrPauseButton_.Name = "playOrPauseButton_";
            this.playOrPauseButton_.Size = new System.Drawing.Size(75, 23);
            this.playOrPauseButton_.TabIndex = 6;
            this.playOrPauseButton_.Text = "Play";
            this.playOrPauseButton_.UseVisualStyleBackColor = true;
            this.playOrPauseButton_.Click += new System.EventHandler(this.playOrPauseButton__Click);
            // 
            // stopButton_
            // 
            this.stopButton_.Enabled = false;
            this.stopButton_.Location = new System.Drawing.Point(158, 158);
            this.stopButton_.Name = "stopButton_";
            this.stopButton_.Size = new System.Drawing.Size(75, 23);
            this.stopButton_.TabIndex = 7;
            this.stopButton_.Text = "Stop";
            this.stopButton_.UseVisualStyleBackColor = true;
            this.stopButton_.Click += new System.EventHandler(this.stopButton__Click);
            // 
            // propertiesButton_
            // 
            this.propertiesButton_.Enabled = false;
            this.propertiesButton_.Location = new System.Drawing.Point(248, 158);
            this.propertiesButton_.Name = "propertiesButton_";
            this.propertiesButton_.Size = new System.Drawing.Size(94, 23);
            this.propertiesButton_.TabIndex = 8;
            this.propertiesButton_.Text = "Properties...";
            this.propertiesButton_.UseVisualStyleBackColor = true;
            this.propertiesButton_.Click += new System.EventHandler(this.propertiesButton__Click);
            // 
            // drcCheckBox_
            // 
            this.drcCheckBox_.AutoSize = true;
            this.drcCheckBox_.Location = new System.Drawing.Point(67, 127);
            this.drcCheckBox_.Name = "drcCheckBox_";
            this.drcCheckBox_.Size = new System.Drawing.Size(216, 16);
            this.drcCheckBox_.TabIndex = 9;
            this.drcCheckBox_.Text = "Enable Dynamic Range Compression";
            this.drcCheckBox_.UseVisualStyleBackColor = true;
            // 
            // volumeLabel_
            // 
            this.volumeLabel_.AutoSize = true;
            this.volumeLabel_.Location = new System.Drawing.Point(12, 76);
            this.volumeLabel_.Name = "volumeLabel_";
            this.volumeLabel_.Size = new System.Drawing.Size(47, 12);
            this.volumeLabel_.TabIndex = 10;
            this.volumeLabel_.Text = "Volume:";
            // 
            // volumeTrackBar_
            // 
            this.volumeTrackBar_.Location = new System.Drawing.Point(62, 76);
            this.volumeTrackBar_.Maximum = 32;
            this.volumeTrackBar_.Minimum = 1;
            this.volumeTrackBar_.Name = "volumeTrackBar_";
            this.volumeTrackBar_.Size = new System.Drawing.Size(280, 45);
            this.volumeTrackBar_.TabIndex = 11;
            this.volumeTrackBar_.Value = 1;
            this.volumeTrackBar_.Scroll += new System.EventHandler(this.volumeTrackBar__Scroll);
            // 
            // PlayWaveFileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(436, 245);
            this.Controls.Add(this.volumeTrackBar_);
            this.Controls.Add(this.volumeLabel_);
            this.Controls.Add(this.drcCheckBox_);
            this.Controls.Add(this.propertiesButton_);
            this.Controls.Add(this.stopButton_);
            this.Controls.Add(this.playOrPauseButton_);
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
            ((System.ComponentModel.ISupportInitialize)(this.volumeTrackBar_)).EndInit();
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
        private System.Windows.Forms.Button playOrPauseButton_;
        private System.Windows.Forms.Button stopButton_;
        private System.Windows.Forms.Button propertiesButton_;
        private System.Windows.Forms.CheckBox drcCheckBox_;
        private System.Windows.Forms.Label volumeLabel_;
        private System.Windows.Forms.TrackBar volumeTrackBar_;
    }
}
