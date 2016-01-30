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
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.applyButton = new System.Windows.Forms.Button();
            this.horzLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.drivesCheckedListBox = new System.Windows.Forms.CheckedListBox();
            this.vertFlowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.noDrivesLabel = new System.Windows.Forms.Label();
            this.noDispCPLCheckBox = new System.Windows.Forms.CheckBox();
            this.noSetFoldersCheckBox = new System.Windows.Forms.CheckBox();
            this.disableRegistryToolsCheckBox = new System.Windows.Forms.CheckBox();
            this.horzLayoutPanel.SuspendLayout();
            this.vertFlowLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(3, 3);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 1;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(84, 3);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // applyButton
            // 
            this.applyButton.Location = new System.Drawing.Point(165, 3);
            this.applyButton.Name = "applyButton";
            this.applyButton.Size = new System.Drawing.Size(75, 23);
            this.applyButton.TabIndex = 3;
            this.applyButton.Text = "Apply";
            this.applyButton.UseVisualStyleBackColor = true;
            this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
            // 
            // horzLayoutPanel
            // 
            this.horzLayoutPanel.AutoSize = true;
            this.horzLayoutPanel.Controls.Add(this.okButton);
            this.horzLayoutPanel.Controls.Add(this.cancelButton);
            this.horzLayoutPanel.Controls.Add(this.applyButton);
            this.horzLayoutPanel.Location = new System.Drawing.Point(3, 203);
            this.horzLayoutPanel.Name = "horzLayoutPanel";
            this.horzLayoutPanel.Size = new System.Drawing.Size(243, 29);
            this.horzLayoutPanel.TabIndex = 4;
            // 
            // drivesCheckedListBox
            // 
            this.drivesCheckedListBox.FormattingEnabled = true;
            this.drivesCheckedListBox.Location = new System.Drawing.Point(3, 15);
            this.drivesCheckedListBox.Name = "drivesCheckedListBox";
            this.drivesCheckedListBox.Size = new System.Drawing.Size(243, 116);
            this.drivesCheckedListBox.TabIndex = 5;
            this.drivesCheckedListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.drivesCheckedListBox_ItemCheck);
            // 
            // vertFlowLayoutPanel
            // 
            this.vertFlowLayoutPanel.AutoSize = true;
            this.vertFlowLayoutPanel.Controls.Add(this.noDrivesLabel);
            this.vertFlowLayoutPanel.Controls.Add(this.drivesCheckedListBox);
            this.vertFlowLayoutPanel.Controls.Add(this.noDispCPLCheckBox);
            this.vertFlowLayoutPanel.Controls.Add(this.noSetFoldersCheckBox);
            this.vertFlowLayoutPanel.Controls.Add(this.disableRegistryToolsCheckBox);
            this.vertFlowLayoutPanel.Controls.Add(this.horzLayoutPanel);
            this.vertFlowLayoutPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.vertFlowLayoutPanel.Location = new System.Drawing.Point(12, 12);
            this.vertFlowLayoutPanel.Name = "vertFlowLayoutPanel";
            this.vertFlowLayoutPanel.Size = new System.Drawing.Size(404, 308);
            this.vertFlowLayoutPanel.TabIndex = 7;
            // 
            // noDrivesLabel
            // 
            this.noDrivesLabel.AutoSize = true;
            this.noDrivesLabel.Location = new System.Drawing.Point(3, 0);
            this.noDrivesLabel.Name = "noDrivesLabel";
            this.noDrivesLabel.Size = new System.Drawing.Size(209, 12);
            this.noDrivesLabel.TabIndex = 6;
            this.noDrivesLabel.Text = "Check the drives you want to hide:";
            // 
            // noDispCPLCheckBox
            // 
            this.noDispCPLCheckBox.AutoSize = true;
            this.noDispCPLCheckBox.Location = new System.Drawing.Point(3, 137);
            this.noDispCPLCheckBox.Name = "noDispCPLCheckBox";
            this.noDispCPLCheckBox.Size = new System.Drawing.Size(108, 16);
            this.noDispCPLCheckBox.TabIndex = 7;
            this.noDispCPLCheckBox.Text = "No Display CPL";
            this.noDispCPLCheckBox.UseVisualStyleBackColor = true;
            // 
            // noSetFoldersCheckBox
            // 
            this.noSetFoldersCheckBox.AutoSize = true;
            this.noSetFoldersCheckBox.Location = new System.Drawing.Point(3, 159);
            this.noSetFoldersCheckBox.Name = "noSetFoldersCheckBox";
            this.noSetFoldersCheckBox.Size = new System.Drawing.Size(108, 16);
            this.noSetFoldersCheckBox.TabIndex = 8;
            this.noSetFoldersCheckBox.Text = "No Set Folders";
            this.noSetFoldersCheckBox.UseVisualStyleBackColor = true;
            // 
            // disableRegistryToolsCheckBox
            // 
            this.disableRegistryToolsCheckBox.AutoSize = true;
            this.disableRegistryToolsCheckBox.Location = new System.Drawing.Point(3, 181);
            this.disableRegistryToolsCheckBox.Name = "disableRegistryToolsCheckBox";
            this.disableRegistryToolsCheckBox.Size = new System.Drawing.Size(156, 16);
            this.disableRegistryToolsCheckBox.TabIndex = 9;
            this.disableRegistryToolsCheckBox.Text = "Disable Registry Tools";
            this.disableRegistryToolsCheckBox.UseVisualStyleBackColor = true;
            // 
            // SysAdminForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(428, 332);
            this.Controls.Add(this.vertFlowLayoutPanel);
            this.Name = "SysAdminForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "System Administration";
            this.horzLayoutPanel.ResumeLayout(false);
            this.vertFlowLayoutPanel.ResumeLayout(false);
            this.vertFlowLayoutPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.FlowLayoutPanel horzLayoutPanel;
        private System.Windows.Forms.CheckedListBox drivesCheckedListBox;
        private System.Windows.Forms.FlowLayoutPanel vertFlowLayoutPanel;
        private System.Windows.Forms.Label noDrivesLabel;
        private System.Windows.Forms.CheckBox noDispCPLCheckBox;
        private System.Windows.Forms.CheckBox noSetFoldersCheckBox;
        private System.Windows.Forms.CheckBox disableRegistryToolsCheckBox;

    }
}

