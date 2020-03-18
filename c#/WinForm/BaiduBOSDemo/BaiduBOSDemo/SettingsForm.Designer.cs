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
            this.tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.endPointTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.endPointLabel_ = new MetroFramework.Controls.MetroLabel();
            this.secretAccessKeyTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.accessKeyTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.secretAccessKeyLabel_ = new MetroFramework.Controls.MetroLabel();
            this.accessKeyLabel_ = new MetroFramework.Controls.MetroLabel();
            this.useFileFullPathAsObjectKeyMetroCheckBox_ = new MetroFramework.Controls.MetroCheckBox();
            this.tableLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel
            // 
            this.tableLayoutPanel.ColumnCount = 2;
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel.Controls.Add(this.endPointTextBox_, 1, 2);
            this.tableLayoutPanel.Controls.Add(this.endPointLabel_, 0, 2);
            this.tableLayoutPanel.Controls.Add(this.secretAccessKeyTextBox_, 1, 1);
            this.tableLayoutPanel.Controls.Add(this.accessKeyTextBox_, 1, 0);
            this.tableLayoutPanel.Controls.Add(this.secretAccessKeyLabel_, 0, 1);
            this.tableLayoutPanel.Controls.Add(this.accessKeyLabel_, 0, 0);
            this.tableLayoutPanel.Controls.Add(this.useFileFullPathAsObjectKeyMetroCheckBox_, 1, 3);
            this.tableLayoutPanel.Location = new System.Drawing.Point(13, 65);
            this.tableLayoutPanel.Name = "tableLayoutPanel";
            this.tableLayoutPanel.RowCount = 5;
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 29F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 22F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 10F));
            this.tableLayoutPanel.Size = new System.Drawing.Size(472, 120);
            this.tableLayoutPanel.TabIndex = 0;
            // 
            // endPointTextBox_
            // 
            this.endPointTextBox_.Location = new System.Drawing.Point(123, 61);
            this.endPointTextBox_.Name = "endPointTextBox_";
            this.endPointTextBox_.Size = new System.Drawing.Size(346, 21);
            this.endPointTextBox_.TabIndex = 4;
            // 
            // endPointLabel_
            // 
            this.endPointLabel_.AutoSize = true;
            this.endPointLabel_.Location = new System.Drawing.Point(3, 58);
            this.endPointLabel_.Name = "endPointLabel_";
            this.endPointLabel_.Size = new System.Drawing.Size(67, 19);
            this.endPointLabel_.TabIndex = 3;
            this.endPointLabel_.Text = "End Point:";
            // 
            // secretAccessKeyTextBox_
            // 
            this.secretAccessKeyTextBox_.Location = new System.Drawing.Point(123, 32);
            this.secretAccessKeyTextBox_.Name = "secretAccessKeyTextBox_";
            this.secretAccessKeyTextBox_.Size = new System.Drawing.Size(346, 21);
            this.secretAccessKeyTextBox_.TabIndex = 3;
            // 
            // accessKeyTextBox_
            // 
            this.accessKeyTextBox_.Location = new System.Drawing.Point(123, 3);
            this.accessKeyTextBox_.Name = "accessKeyTextBox_";
            this.accessKeyTextBox_.Size = new System.Drawing.Size(346, 21);
            this.accessKeyTextBox_.TabIndex = 1;
            // 
            // secretAccessKeyLabel_
            // 
            this.secretAccessKeyLabel_.AutoSize = true;
            this.secretAccessKeyLabel_.Location = new System.Drawing.Point(3, 29);
            this.secretAccessKeyLabel_.Name = "secretAccessKeyLabel_";
            this.secretAccessKeyLabel_.Size = new System.Drawing.Size(114, 19);
            this.secretAccessKeyLabel_.TabIndex = 2;
            this.secretAccessKeyLabel_.Text = "Secret Access Key:";
            // 
            // accessKeyLabel_
            // 
            this.accessKeyLabel_.AutoSize = true;
            this.accessKeyLabel_.Location = new System.Drawing.Point(3, 0);
            this.accessKeyLabel_.Name = "accessKeyLabel_";
            this.accessKeyLabel_.Size = new System.Drawing.Size(74, 19);
            this.accessKeyLabel_.TabIndex = 0;
            this.accessKeyLabel_.Text = "Access Key:";
            // 
            // useFileFullPathAsObjectKeyMetroCheckBox_
            // 
            this.useFileFullPathAsObjectKeyMetroCheckBox_.AutoSize = true;
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Location = new System.Drawing.Point(123, 90);
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Name = "useFileFullPathAsObjectKeyMetroCheckBox_";
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Size = new System.Drawing.Size(278, 15);
            this.useFileFullPathAsObjectKeyMetroCheckBox_.TabIndex = 5;
            this.useFileFullPathAsObjectKeyMetroCheckBox_.Text = "Use File Full Path as Object Key When Uploading";
            this.useFileFullPathAsObjectKeyMetroCheckBox_.UseVisualStyleBackColor = true;
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 226);
            this.Controls.Add(this.tableLayoutPanel);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingsForm";
            this.Resizable = false;
            this.Text = "Settings";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SettingsForm_FormClosed);
            this.Load += new System.EventHandler(this.SettingsForm_Load);
            this.tableLayoutPanel.ResumeLayout(false);
            this.tableLayoutPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel;
        private MetroFramework.Controls.MetroTextBox endPointTextBox_;
        private MetroFramework.Controls.MetroLabel endPointLabel_;
        private MetroFramework.Controls.MetroTextBox secretAccessKeyTextBox_;
        private MetroFramework.Controls.MetroLabel accessKeyLabel_;
        private MetroFramework.Controls.MetroTextBox accessKeyTextBox_;
        private MetroFramework.Controls.MetroLabel secretAccessKeyLabel_;
        private MetroFramework.Controls.MetroCheckBox useFileFullPathAsObjectKeyMetroCheckBox_;
    }
}
