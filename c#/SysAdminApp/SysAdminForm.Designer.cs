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
            this.noDrivesGroupBox = new System.Windows.Forms.GroupBox();
            this.horzLayoutPanel.SuspendLayout();
            this.noDrivesGroupBox.SuspendLayout();
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
            this.horzLayoutPanel.Controls.Add(this.okButton);
            this.horzLayoutPanel.Controls.Add(this.cancelButton);
            this.horzLayoutPanel.Controls.Add(this.applyButton);
            this.horzLayoutPanel.Location = new System.Drawing.Point(13, 179);
            this.horzLayoutPanel.Name = "horzLayoutPanel";
            this.horzLayoutPanel.Size = new System.Drawing.Size(256, 37);
            this.horzLayoutPanel.TabIndex = 4;
            // 
            // drivesCheckedListBox
            // 
            this.drivesCheckedListBox.FormattingEnabled = true;
            this.drivesCheckedListBox.Location = new System.Drawing.Point(15, 20);
            this.drivesCheckedListBox.Name = "drivesCheckedListBox";
            this.drivesCheckedListBox.Size = new System.Drawing.Size(93, 116);
            this.drivesCheckedListBox.TabIndex = 5;
            this.drivesCheckedListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.drivesCheckedListBox_ItemCheck);
            // 
            // noDrivesGroupBox
            // 
            this.noDrivesGroupBox.Controls.Add(this.drivesCheckedListBox);
            this.noDrivesGroupBox.Location = new System.Drawing.Point(13, 13);
            this.noDrivesGroupBox.Name = "noDrivesGroupBox";
            this.noDrivesGroupBox.Size = new System.Drawing.Size(122, 147);
            this.noDrivesGroupBox.TabIndex = 6;
            this.noDrivesGroupBox.TabStop = false;
            this.noDrivesGroupBox.Text = "No Drives";
            // 
            // SysAdminForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(277, 210);
            this.Controls.Add(this.noDrivesGroupBox);
            this.Controls.Add(this.horzLayoutPanel);
            this.Name = "SysAdminForm";
            this.Text = "System Administration";
            this.horzLayoutPanel.ResumeLayout(false);
            this.noDrivesGroupBox.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.FlowLayoutPanel horzLayoutPanel;
        private System.Windows.Forms.CheckedListBox drivesCheckedListBox;
        private System.Windows.Forms.GroupBox noDrivesGroupBox;

    }
}

