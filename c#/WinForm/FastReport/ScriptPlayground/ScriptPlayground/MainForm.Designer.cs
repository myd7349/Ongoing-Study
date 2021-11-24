namespace ScriptPlayground
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
            this.previewButton_ = new System.Windows.Forms.Button();
            this.nameCheckBox_ = new System.Windows.Forms.CheckBox();
            this.nameTextBox_ = new System.Windows.Forms.TextBox();
            this.ageTextBox_ = new System.Windows.Forms.TextBox();
            this.ageCheckBox_ = new System.Windows.Forms.CheckBox();
            this.genderCheckBox_ = new System.Windows.Forms.CheckBox();
            this.genderComboBox_ = new System.Windows.Forms.ComboBox();
            this.idTextBox_ = new System.Windows.Forms.TextBox();
            this.idCheckBox_ = new System.Windows.Forms.CheckBox();
            this.addressTextBox_ = new System.Windows.Forms.TextBox();
            this.addressCheckBox_ = new System.Windows.Forms.CheckBox();
            this.phoneTextBox_ = new System.Windows.Forms.TextBox();
            this.phoneCheckBox_ = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // previewButton_
            // 
            this.previewButton_.Location = new System.Drawing.Point(110, 186);
            this.previewButton_.Name = "previewButton_";
            this.previewButton_.Size = new System.Drawing.Size(75, 23);
            this.previewButton_.TabIndex = 0;
            this.previewButton_.Text = "Preview...";
            this.previewButton_.UseVisualStyleBackColor = true;
            this.previewButton_.Click += new System.EventHandler(this.previewButton__Click);
            // 
            // nameCheckBox_
            // 
            this.nameCheckBox_.AutoSize = true;
            this.nameCheckBox_.Location = new System.Drawing.Point(12, 12);
            this.nameCheckBox_.Name = "nameCheckBox_";
            this.nameCheckBox_.Size = new System.Drawing.Size(54, 16);
            this.nameCheckBox_.TabIndex = 1;
            this.nameCheckBox_.Text = "Name:";
            this.nameCheckBox_.UseVisualStyleBackColor = true;
            this.nameCheckBox_.CheckedChanged += new System.EventHandler(this.nameCheckBox__CheckedChanged);
            // 
            // nameTextBox_
            // 
            this.nameTextBox_.Enabled = false;
            this.nameTextBox_.Location = new System.Drawing.Point(95, 10);
            this.nameTextBox_.Name = "nameTextBox_";
            this.nameTextBox_.Size = new System.Drawing.Size(150, 21);
            this.nameTextBox_.TabIndex = 2;
            // 
            // ageTextBox_
            // 
            this.ageTextBox_.Enabled = false;
            this.ageTextBox_.Location = new System.Drawing.Point(95, 37);
            this.ageTextBox_.Name = "ageTextBox_";
            this.ageTextBox_.Size = new System.Drawing.Size(150, 21);
            this.ageTextBox_.TabIndex = 4;
            // 
            // ageCheckBox_
            // 
            this.ageCheckBox_.AutoSize = true;
            this.ageCheckBox_.Location = new System.Drawing.Point(12, 39);
            this.ageCheckBox_.Name = "ageCheckBox_";
            this.ageCheckBox_.Size = new System.Drawing.Size(48, 16);
            this.ageCheckBox_.TabIndex = 3;
            this.ageCheckBox_.Text = "Age:";
            this.ageCheckBox_.UseVisualStyleBackColor = true;
            this.ageCheckBox_.CheckedChanged += new System.EventHandler(this.ageCheckBox__CheckedChanged);
            // 
            // genderCheckBox_
            // 
            this.genderCheckBox_.AutoSize = true;
            this.genderCheckBox_.Location = new System.Drawing.Point(12, 66);
            this.genderCheckBox_.Name = "genderCheckBox_";
            this.genderCheckBox_.Size = new System.Drawing.Size(66, 16);
            this.genderCheckBox_.TabIndex = 5;
            this.genderCheckBox_.Text = "Gender:";
            this.genderCheckBox_.UseVisualStyleBackColor = true;
            this.genderCheckBox_.CheckedChanged += new System.EventHandler(this.genderCheckBox__CheckedChanged);
            // 
            // genderComboBox_
            // 
            this.genderComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.genderComboBox_.Enabled = false;
            this.genderComboBox_.FormattingEnabled = true;
            this.genderComboBox_.Items.AddRange(new object[] {
            "",
            "Female",
            "Male"});
            this.genderComboBox_.Location = new System.Drawing.Point(95, 64);
            this.genderComboBox_.Name = "genderComboBox_";
            this.genderComboBox_.Size = new System.Drawing.Size(150, 20);
            this.genderComboBox_.TabIndex = 6;
            // 
            // idTextBox_
            // 
            this.idTextBox_.Enabled = false;
            this.idTextBox_.Location = new System.Drawing.Point(95, 90);
            this.idTextBox_.Name = "idTextBox_";
            this.idTextBox_.Size = new System.Drawing.Size(150, 21);
            this.idTextBox_.TabIndex = 8;
            // 
            // idCheckBox_
            // 
            this.idCheckBox_.AutoSize = true;
            this.idCheckBox_.Location = new System.Drawing.Point(12, 92);
            this.idCheckBox_.Name = "idCheckBox_";
            this.idCheckBox_.Size = new System.Drawing.Size(42, 16);
            this.idCheckBox_.TabIndex = 7;
            this.idCheckBox_.Text = "ID:";
            this.idCheckBox_.UseVisualStyleBackColor = true;
            this.idCheckBox_.CheckedChanged += new System.EventHandler(this.idCheckBox__CheckedChanged);
            // 
            // addressTextBox_
            // 
            this.addressTextBox_.Enabled = false;
            this.addressTextBox_.Location = new System.Drawing.Point(95, 117);
            this.addressTextBox_.Name = "addressTextBox_";
            this.addressTextBox_.Size = new System.Drawing.Size(150, 21);
            this.addressTextBox_.TabIndex = 10;
            // 
            // addressCheckBox_
            // 
            this.addressCheckBox_.AutoSize = true;
            this.addressCheckBox_.Location = new System.Drawing.Point(12, 119);
            this.addressCheckBox_.Name = "addressCheckBox_";
            this.addressCheckBox_.Size = new System.Drawing.Size(72, 16);
            this.addressCheckBox_.TabIndex = 9;
            this.addressCheckBox_.Text = "Address:";
            this.addressCheckBox_.UseVisualStyleBackColor = true;
            this.addressCheckBox_.CheckedChanged += new System.EventHandler(this.addressCheckBox__CheckedChanged);
            // 
            // phoneTextBox_
            // 
            this.phoneTextBox_.Enabled = false;
            this.phoneTextBox_.Location = new System.Drawing.Point(95, 144);
            this.phoneTextBox_.Name = "phoneTextBox_";
            this.phoneTextBox_.Size = new System.Drawing.Size(150, 21);
            this.phoneTextBox_.TabIndex = 12;
            // 
            // phoneCheckBox_
            // 
            this.phoneCheckBox_.AutoSize = true;
            this.phoneCheckBox_.Location = new System.Drawing.Point(12, 146);
            this.phoneCheckBox_.Name = "phoneCheckBox_";
            this.phoneCheckBox_.Size = new System.Drawing.Size(60, 16);
            this.phoneCheckBox_.TabIndex = 11;
            this.phoneCheckBox_.Text = "Phone:";
            this.phoneCheckBox_.UseVisualStyleBackColor = true;
            this.phoneCheckBox_.CheckedChanged += new System.EventHandler(this.phoneCheckBox__CheckedChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 221);
            this.Controls.Add(this.phoneTextBox_);
            this.Controls.Add(this.phoneCheckBox_);
            this.Controls.Add(this.addressTextBox_);
            this.Controls.Add(this.addressCheckBox_);
            this.Controls.Add(this.idTextBox_);
            this.Controls.Add(this.idCheckBox_);
            this.Controls.Add(this.genderComboBox_);
            this.Controls.Add(this.genderCheckBox_);
            this.Controls.Add(this.ageTextBox_);
            this.Controls.Add(this.ageCheckBox_);
            this.Controls.Add(this.nameTextBox_);
            this.Controls.Add(this.nameCheckBox_);
            this.Controls.Add(this.previewButton_);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Script Playground";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button previewButton_;
        private System.Windows.Forms.CheckBox nameCheckBox_;
        private System.Windows.Forms.TextBox nameTextBox_;
        private System.Windows.Forms.TextBox ageTextBox_;
        private System.Windows.Forms.CheckBox ageCheckBox_;
        private System.Windows.Forms.CheckBox genderCheckBox_;
        private System.Windows.Forms.ComboBox genderComboBox_;
        private System.Windows.Forms.TextBox idTextBox_;
        private System.Windows.Forms.CheckBox idCheckBox_;
        private System.Windows.Forms.TextBox addressTextBox_;
        private System.Windows.Forms.CheckBox addressCheckBox_;
        private System.Windows.Forms.TextBox phoneTextBox_;
        private System.Windows.Forms.CheckBox phoneCheckBox_;
    }
}

