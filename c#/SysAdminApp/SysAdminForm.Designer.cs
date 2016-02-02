namespace SysAdminApp
{
    partial class SysAdminForm
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
            this.noDrivesLabel = new System.Windows.Forms.Label();
            this.drivesCheckedListBox = new System.Windows.Forms.CheckedListBox();
            this.noDispCPLCheckBox = new System.Windows.Forms.CheckBox();
            this.noSetFoldersCheckBox = new System.Windows.Forms.CheckBox();
            this.disableRegistryToolsCheckBox = new System.Windows.Forms.CheckBox();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.applyButton = new System.Windows.Forms.Button();
            this.langLabel = new System.Windows.Forms.Label();
            this.langComboBox = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // noDrivesLabel
            // 
            this.noDrivesLabel.AutoEllipsis = true;
            this.noDrivesLabel.AutoSize = true;
            this.noDrivesLabel.Location = new System.Drawing.Point(12, 45);
            this.noDrivesLabel.Name = "noDrivesLabel";
            this.noDrivesLabel.Size = new System.Drawing.Size(209, 12);
            this.noDrivesLabel.TabIndex = 2;
            this.noDrivesLabel.Text = "Check the drives you want to hide:";
            // 
            // drivesCheckedListBox
            // 
            this.drivesCheckedListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.drivesCheckedListBox.FormattingEnabled = true;
            this.drivesCheckedListBox.Location = new System.Drawing.Point(14, 60);
            this.drivesCheckedListBox.Name = "drivesCheckedListBox";
            this.drivesCheckedListBox.Size = new System.Drawing.Size(239, 84);
            this.drivesCheckedListBox.TabIndex = 3;
            this.drivesCheckedListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(drivesCheckedListBox_ItemCheck);
            //
            // noDispCPLCheckBox
            // 
            this.noDispCPLCheckBox.AutoSize = true;
            this.noDispCPLCheckBox.Location = new System.Drawing.Point(14, 162);
            this.noDispCPLCheckBox.Name = "noDispCPLCheckBox";
            this.noDispCPLCheckBox.Size = new System.Drawing.Size(108, 16);
            this.noDispCPLCheckBox.TabIndex = 4;
            this.noDispCPLCheckBox.Text = "No Display CPL";
            this.noDispCPLCheckBox.UseVisualStyleBackColor = true;
            // 
            // noSetFoldersCheckBox
            // 
            this.noSetFoldersCheckBox.AutoSize = true;
            this.noSetFoldersCheckBox.Location = new System.Drawing.Point(14, 184);
            this.noSetFoldersCheckBox.Name = "noSetFoldersCheckBox";
            this.noSetFoldersCheckBox.Size = new System.Drawing.Size(108, 16);
            this.noSetFoldersCheckBox.TabIndex = 5;
            this.noSetFoldersCheckBox.Text = "No Set Folders";
            this.noSetFoldersCheckBox.UseVisualStyleBackColor = true;
            // 
            // disableRegistryToolsCheckBox
            // 
            this.disableRegistryToolsCheckBox.AutoSize = true;
            this.disableRegistryToolsCheckBox.Location = new System.Drawing.Point(14, 206);
            this.disableRegistryToolsCheckBox.Name = "disableRegistryToolsCheckBox";
            this.disableRegistryToolsCheckBox.Size = new System.Drawing.Size(156, 16);
            this.disableRegistryToolsCheckBox.TabIndex = 6;
            this.disableRegistryToolsCheckBox.Text = "Disable Registry Tools";
            this.disableRegistryToolsCheckBox.UseVisualStyleBackColor = true;
            // 
            // okButton
            // 
            this.okButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.okButton.AutoSize = true;
            this.okButton.Location = new System.Drawing.Point(14, 237);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 7;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.cancelButton.AutoSize = true;
            this.cancelButton.Location = new System.Drawing.Point(95, 237);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 8;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // applyButton
            // 
            this.applyButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.applyButton.AutoSize = true;
            this.applyButton.Location = new System.Drawing.Point(176, 237);
            this.applyButton.Name = "applyButton";
            this.applyButton.Size = new System.Drawing.Size(75, 23);
            this.applyButton.TabIndex = 9;
            this.applyButton.Text = "Apply";
            this.applyButton.UseVisualStyleBackColor = true;
            this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
            // 
            // langLabel
            // 
            this.langLabel.AutoSize = true;
            this.langLabel.Location = new System.Drawing.Point(12, 14);
            this.langLabel.Name = "langLabel";
            this.langLabel.Size = new System.Drawing.Size(77, 12);
            this.langLabel.TabIndex = 0;
            this.langLabel.Text = "UI Language:";
            this.langLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // langComboBox
            // 
            this.langComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.langComboBox.FormattingEnabled = true;
            this.langComboBox.Location = new System.Drawing.Point(95, 12);
            this.langComboBox.Name = "langComboBox";
            this.langComboBox.Size = new System.Drawing.Size(158, 20);
            this.langComboBox.TabIndex = 1;
            this.langComboBox.SelectedIndexChanged += new System.EventHandler(this.langComboBox_SelectedIndexChanged);
            // 
            // SysAdminForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.MintCream;
            this.ClientSize = new System.Drawing.Size(265, 272);
            this.Controls.Add(this.applyButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.disableRegistryToolsCheckBox);
            this.Controls.Add(this.noSetFoldersCheckBox);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.noDispCPLCheckBox);
            this.Controls.Add(this.drivesCheckedListBox);
            this.Controls.Add(this.noDrivesLabel);
            this.Controls.Add(this.langLabel);
            this.Controls.Add(this.langComboBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "SysAdminForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "System Administration";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.SysAdminForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label noDrivesLabel;
        private System.Windows.Forms.CheckedListBox drivesCheckedListBox;
        private System.Windows.Forms.CheckBox noDispCPLCheckBox;
        private System.Windows.Forms.CheckBox noSetFoldersCheckBox;
        private System.Windows.Forms.CheckBox disableRegistryToolsCheckBox;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.Label langLabel;
        private System.Windows.Forms.ComboBox langComboBox;
    }
}

