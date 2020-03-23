namespace BaiduBOSDemo
{
    partial class SettingsForm
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
            this.endPointTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.endPointLabel_ = new MetroFramework.Controls.MetroLabel();
            this.secretAccessKeyTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.accessKeyTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.secretAccessKeyLabel_ = new MetroFramework.Controls.MetroLabel();
            this.accessKeyLabel_ = new MetroFramework.Controls.MetroLabel();
            this.useFileFullPathAsObjectKeyMetroCheckBox_ = new MetroFramework.Controls.MetroCheckBox();
            this.metroTabControl_ = new MetroFramework.Controls.MetroTabControl();
            this.accountMetroTabPage_ = new MetroFramework.Controls.MetroTabPage();
            this.uploadMetroTabPage_ = new MetroFramework.Controls.MetroTabPage();
            this.uploadPartSizeUnitMetroComboBox_ = new MetroFramework.Controls.MetroComboBox();
            this.uploadPartSizeMetroTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.uploadPartSizeMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.downloadMetroTabPage_ = new MetroFramework.Controls.MetroTabPage();
            this.downloadSizeMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.downloadSizeMetroTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.downloadSizeUnitMetroComboBox_ = new MetroFramework.Controls.MetroComboBox();
            this.metroTabControl_.SuspendLayout();
            this.accountMetroTabPage_.SuspendLayout();
            this.uploadMetroTabPage_.SuspendLayout();
            this.downloadMetroTabPage_.SuspendLayout();
            this.SuspendLayout();
            // 
            // endPointTextBox_
            // 
            this.endPointTextBox_.Location = new System.Drawing.Point(123, 64);
            this.endPointTextBox_.Name = "endPointTextBox_";
            this.endPointTextBox_.Size = new System.Drawing.Size(287, 21);
            this.endPointTextBox_.TabIndex = 4;
            // 
            // endPointLabel_
            // 
            this.endPointLabel_.AutoSize = true;
            this.endPointLabel_.Location = new System.Drawing.Point(0, 64);
            this.endPointLabel_.Name = "endPointLabel_";
            this.endPointLabel_.Size = new System.Drawing.Size(67, 19);
            this.endPointLabel_.TabIndex = 3;
            this.endPointLabel_.Text = "End Point:";
            // 
            // secretAccessKeyTextBox_
            // 
            this.secretAccessKeyTextBox_.Location = new System.Drawing.Point(123, 37);
            this.secretAccessKeyTextBox_.Name = "secretAccessKeyTextBox_";
            this.secretAccessKeyTextBox_.Size = new System.Drawing.Size(287, 21);
            this.secretAccessKeyTextBox_.TabIndex = 3;
            // 
            // accessKeyTextBox_
            // 
            this.accessKeyTextBox_.Location = new System.Drawing.Point(123, 10);
            this.accessKeyTextBox_.Name = "accessKeyTextBox_";
            this.accessKeyTextBox_.Size = new System.Drawing.Size(287, 21);
            this.accessKeyTextBox_.TabIndex = 1;
            // 
            // secretAccessKeyLabel_
            // 
            this.secretAccessKeyLabel_.AutoSize = true;
            this.secretAccessKeyLabel_.Location = new System.Drawing.Point(0, 37);
            this.secretAccessKeyLabel_.Name = "secretAccessKeyLabel_";
            this.secretAccessKeyLabel_.Size = new System.Drawing.Size(114, 19);
            this.secretAccessKeyLabel_.TabIndex = 2;
            this.secretAccessKeyLabel_.Text = "Secret Access Key:";
            // 
            // accessKeyLabel_
            // 
            this.accessKeyLabel_.AutoSize = true;
            this.accessKeyLabel_.Location = new System.Drawing.Point(0, 10);
            this.accessKeyLabel_.Name = "accessKeyLabel_";
            this.accessKeyLabel_.Size = new System.Drawing.Size(74, 19);
            this.accessKeyLabel_.TabIndex = 0;
            this.accessKeyLabel_.Text = "Access Key:";
            // 
            // useFileFullPathAsObjectKeyMetroCheckBox_
            // 
            this.useFileFullPathAsObjectKeyMetroCheckBox_.AutoSize = true;
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Location = new System.Drawing.Point(8, 44);
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Name = "useFileFullPathAsObjectKeyMetroCheckBox_";
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Size = new System.Drawing.Size(186, 15);
            this.useFileFullPathAsObjectKeyMetroCheckBox_.TabIndex = 5;
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Text = "Use File Full Path as Object Key";
            this.useFileFullPathAsObjectKeyMetroCheckBox_.UseVisualStyleBackColor = true;
            // 
            // metroTabControl_
            // 
            this.metroTabControl_.Controls.Add(this.accountMetroTabPage_);
            this.metroTabControl_.Controls.Add(this.uploadMetroTabPage_);
            this.metroTabControl_.Controls.Add(this.downloadMetroTabPage_);
            this.metroTabControl_.Location = new System.Drawing.Point(23, 63);
            this.metroTabControl_.Name = "metroTabControl_";
            this.metroTabControl_.SelectedIndex = 2;
            this.metroTabControl_.Size = new System.Drawing.Size(421, 154);
            this.metroTabControl_.TabIndex = 1;
            // 
            // accountMetroTabPage_
            // 
            this.accountMetroTabPage_.Controls.Add(this.endPointTextBox_);
            this.accountMetroTabPage_.Controls.Add(this.endPointLabel_);
            this.accountMetroTabPage_.Controls.Add(this.accessKeyLabel_);
            this.accountMetroTabPage_.Controls.Add(this.secretAccessKeyTextBox_);
            this.accountMetroTabPage_.Controls.Add(this.accessKeyTextBox_);
            this.accountMetroTabPage_.Controls.Add(this.secretAccessKeyLabel_);
            this.accountMetroTabPage_.HorizontalScrollbarBarColor = true;
            this.accountMetroTabPage_.Location = new System.Drawing.Point(4, 36);
            this.accountMetroTabPage_.Name = "accountMetroTabPage_";
            this.accountMetroTabPage_.Size = new System.Drawing.Size(413, 114);
            this.accountMetroTabPage_.TabIndex = 0;
            this.accountMetroTabPage_.Text = "Account";
            this.accountMetroTabPage_.VerticalScrollbarBarColor = true;
            // 
            // uploadMetroTabPage_
            // 
            this.uploadMetroTabPage_.Controls.Add(this.uploadPartSizeUnitMetroComboBox_);
            this.uploadMetroTabPage_.Controls.Add(this.uploadPartSizeMetroTextBox_);
            this.uploadMetroTabPage_.Controls.Add(this.uploadPartSizeMetroLabel_);
            this.uploadMetroTabPage_.Controls.Add(this.useFileFullPathAsObjectKeyMetroCheckBox_);
            this.uploadMetroTabPage_.HorizontalScrollbarBarColor = true;
            this.uploadMetroTabPage_.Location = new System.Drawing.Point(4, 36);
            this.uploadMetroTabPage_.Name = "uploadMetroTabPage_";
            this.uploadMetroTabPage_.Size = new System.Drawing.Size(413, 114);
            this.uploadMetroTabPage_.TabIndex = 1;
            this.uploadMetroTabPage_.Text = "Upload";
            this.uploadMetroTabPage_.VerticalScrollbarBarColor = true;
            // 
            // uploadPartSizeUnitMetroComboBox_
            // 
            this.uploadPartSizeUnitMetroComboBox_.FormattingEnabled = true;
            this.uploadPartSizeUnitMetroComboBox_.ItemHeight = 23;
            this.uploadPartSizeUnitMetroComboBox_.Items.AddRange(new object[] {
            "KB",
            "MB"});
            this.uploadPartSizeUnitMetroComboBox_.Location = new System.Drawing.Point(169, 9);
            this.uploadPartSizeUnitMetroComboBox_.Name = "uploadPartSizeUnitMetroComboBox_";
            this.uploadPartSizeUnitMetroComboBox_.Size = new System.Drawing.Size(56, 29);
            this.uploadPartSizeUnitMetroComboBox_.TabIndex = 8;
            // 
            // uploadPartSizeMetroTextBox_
            // 
            this.uploadPartSizeMetroTextBox_.Location = new System.Drawing.Point(70, 11);
            this.uploadPartSizeMetroTextBox_.Name = "uploadPartSizeMetroTextBox_";
            this.uploadPartSizeMetroTextBox_.Size = new System.Drawing.Size(95, 23);
            this.uploadPartSizeMetroTextBox_.TabIndex = 7;
            // 
            // uploadPartSizeMetroLabel_
            // 
            this.uploadPartSizeMetroLabel_.AutoSize = true;
            this.uploadPartSizeMetroLabel_.Location = new System.Drawing.Point(4, 12);
            this.uploadPartSizeMetroLabel_.Name = "uploadPartSizeMetroLabel_";
            this.uploadPartSizeMetroLabel_.Size = new System.Drawing.Size(63, 19);
            this.uploadPartSizeMetroLabel_.TabIndex = 6;
            this.uploadPartSizeMetroLabel_.Text = "Part Size:";
            // 
            // downloadMetroTabPage_
            // 
            this.downloadMetroTabPage_.Controls.Add(this.downloadSizeUnitMetroComboBox_);
            this.downloadMetroTabPage_.Controls.Add(this.downloadSizeMetroTextBox_);
            this.downloadMetroTabPage_.Controls.Add(this.downloadSizeMetroLabel_);
            this.downloadMetroTabPage_.HorizontalScrollbarBarColor = true;
            this.downloadMetroTabPage_.Location = new System.Drawing.Point(4, 36);
            this.downloadMetroTabPage_.Name = "downloadMetroTabPage_";
            this.downloadMetroTabPage_.Size = new System.Drawing.Size(413, 114);
            this.downloadMetroTabPage_.TabIndex = 2;
            this.downloadMetroTabPage_.Text = "Download";
            this.downloadMetroTabPage_.VerticalScrollbarBarColor = true;
            // 
            // downloadSizeMetroLabel_
            // 
            this.downloadSizeMetroLabel_.AutoSize = true;
            this.downloadSizeMetroLabel_.Location = new System.Drawing.Point(4, 11);
            this.downloadSizeMetroLabel_.Name = "downloadSizeMetroLabel_";
            this.downloadSizeMetroLabel_.Size = new System.Drawing.Size(98, 19);
            this.downloadSizeMetroLabel_.TabIndex = 2;
            this.downloadSizeMetroLabel_.Text = "Download Size:";
            // 
            // downloadSizeMetroTextBox_
            // 
            this.downloadSizeMetroTextBox_.Location = new System.Drawing.Point(105, 11);
            this.downloadSizeMetroTextBox_.Name = "downloadSizeMetroTextBox_";
            this.downloadSizeMetroTextBox_.Size = new System.Drawing.Size(95, 23);
            this.downloadSizeMetroTextBox_.TabIndex = 8;
            // 
            // downloadSizeUnitMetroComboBox_
            // 
            this.downloadSizeUnitMetroComboBox_.FormattingEnabled = true;
            this.downloadSizeUnitMetroComboBox_.ItemHeight = 23;
            this.downloadSizeUnitMetroComboBox_.Items.AddRange(new object[] {
            "B",
            "KB",
            "MB"});
            this.downloadSizeUnitMetroComboBox_.Location = new System.Drawing.Point(204, 9);
            this.downloadSizeUnitMetroComboBox_.Name = "downloadSizeUnitMetroComboBox_";
            this.downloadSizeUnitMetroComboBox_.Size = new System.Drawing.Size(56, 29);
            this.downloadSizeUnitMetroComboBox_.TabIndex = 9;
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(463, 235);
            this.Controls.Add(this.metroTabControl_);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingsForm";
            this.Resizable = false;
            this.Text = "Settings";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SettingsForm_FormClosed);
            this.Load += new System.EventHandler(this.SettingsForm_Load);
            this.metroTabControl_.ResumeLayout(false);
            this.accountMetroTabPage_.ResumeLayout(false);
            this.accountMetroTabPage_.PerformLayout();
            this.uploadMetroTabPage_.ResumeLayout(false);
            this.uploadMetroTabPage_.PerformLayout();
            this.downloadMetroTabPage_.ResumeLayout(false);
            this.downloadMetroTabPage_.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private MetroFramework.Controls.MetroTextBox endPointTextBox_;
        private MetroFramework.Controls.MetroLabel endPointLabel_;
        private MetroFramework.Controls.MetroTextBox secretAccessKeyTextBox_;
        private MetroFramework.Controls.MetroLabel accessKeyLabel_;
        private MetroFramework.Controls.MetroTextBox accessKeyTextBox_;
        private MetroFramework.Controls.MetroLabel secretAccessKeyLabel_;
        private MetroFramework.Controls.MetroCheckBox useFileFullPathAsObjectKeyMetroCheckBox_;
        private MetroFramework.Controls.MetroTabControl metroTabControl_;
        private MetroFramework.Controls.MetroTabPage accountMetroTabPage_;
        private MetroFramework.Controls.MetroTabPage uploadMetroTabPage_;
        private MetroFramework.Controls.MetroLabel uploadPartSizeMetroLabel_;
        private MetroFramework.Controls.MetroTextBox uploadPartSizeMetroTextBox_;
        private MetroFramework.Controls.MetroComboBox uploadPartSizeUnitMetroComboBox_;
        private MetroFramework.Controls.MetroTabPage downloadMetroTabPage_;
        private MetroFramework.Controls.MetroComboBox downloadSizeUnitMetroComboBox_;
        private MetroFramework.Controls.MetroTextBox downloadSizeMetroTextBox_;
        private MetroFramework.Controls.MetroLabel downloadSizeMetroLabel_;
    }
}
