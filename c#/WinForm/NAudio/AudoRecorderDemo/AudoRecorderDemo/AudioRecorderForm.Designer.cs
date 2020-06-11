namespace AudoRecorderDemo
{
    partial class AudioRecorderForm
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
            this.recordOrStopButton_ = new System.Windows.Forms.Button();
            this.deviceLabel_ = new System.Windows.Forms.Label();
            this.deviceComboBox_ = new System.Windows.Forms.ComboBox();
            this.refreshButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // recordOrStopButton_
            // 
            this.recordOrStopButton_.Enabled = false;
            this.recordOrStopButton_.Location = new System.Drawing.Point(162, 51);
            this.recordOrStopButton_.Name = "recordOrStopButton_";
            this.recordOrStopButton_.Size = new System.Drawing.Size(89, 25);
            this.recordOrStopButton_.TabIndex = 0;
            this.recordOrStopButton_.Text = "Record";
            this.recordOrStopButton_.UseVisualStyleBackColor = true;
            this.recordOrStopButton_.Click += new System.EventHandler(this.recordOrStopButton__Click);
            // 
            // deviceLabel_
            // 
            this.deviceLabel_.AutoSize = true;
            this.deviceLabel_.Location = new System.Drawing.Point(13, 13);
            this.deviceLabel_.Name = "deviceLabel_";
            this.deviceLabel_.Size = new System.Drawing.Size(47, 12);
            this.deviceLabel_.TabIndex = 1;
            this.deviceLabel_.Text = "Device:";
            // 
            // deviceComboBox_
            // 
            this.deviceComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox_.FormattingEnabled = true;
            this.deviceComboBox_.Location = new System.Drawing.Point(67, 12);
            this.deviceComboBox_.Name = "deviceComboBox_";
            this.deviceComboBox_.Size = new System.Drawing.Size(309, 20);
            this.deviceComboBox_.TabIndex = 2;
            this.deviceComboBox_.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox__SelectedIndexChanged);
            // 
            // refreshButton_
            // 
            this.refreshButton_.Location = new System.Drawing.Point(67, 51);
            this.refreshButton_.Name = "refreshButton_";
            this.refreshButton_.Size = new System.Drawing.Size(89, 25);
            this.refreshButton_.TabIndex = 3;
            this.refreshButton_.Text = "Refresh";
            this.refreshButton_.UseVisualStyleBackColor = true;
            this.refreshButton_.Click += new System.EventHandler(this.refreshButton__Click);
            // 
            // AudioRecorderForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(388, 93);
            this.Controls.Add(this.refreshButton_);
            this.Controls.Add(this.deviceComboBox_);
            this.Controls.Add(this.deviceLabel_);
            this.Controls.Add(this.recordOrStopButton_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AudioRecorderForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Audio Recorder";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button recordOrStopButton_;
        private System.Windows.Forms.Label deviceLabel_;
        private System.Windows.Forms.ComboBox deviceComboBox_;
        private System.Windows.Forms.Button refreshButton_;
    }
}

