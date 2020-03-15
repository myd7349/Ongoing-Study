namespace BaiduBOSDemo
{
    partial class BaiduBOSForm
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
            this.filePathTextBox_ = new System.Windows.Forms.TextBox();
            this.uploadButton_ = new System.Windows.Forms.Button();
            this.transmissionProgressBar_ = new System.Windows.Forms.ProgressBar();
            this.settingsButton_ = new System.Windows.Forms.Button();
            this.bucketLabel_ = new System.Windows.Forms.Label();
            this.bucketComboBox_ = new System.Windows.Forms.ComboBox();
            this.selectFileButton_ = new System.Windows.Forms.Button();
            this.objectDataGridView_ = new DataGridViewEx();
            ((System.ComponentModel.ISupportInitialize)(this.objectDataGridView_)).BeginInit();
            this.SuspendLayout();
            // 
            // filePathTextBox_
            // 
            this.filePathTextBox_.Location = new System.Drawing.Point(14, 443);
            this.filePathTextBox_.Name = "filePathTextBox_";
            this.filePathTextBox_.Size = new System.Drawing.Size(531, 21);
            this.filePathTextBox_.TabIndex = 2;
            // 
            // uploadButton_
            // 
            this.uploadButton_.Location = new System.Drawing.Point(551, 471);
            this.uploadButton_.Name = "uploadButton_";
            this.uploadButton_.Size = new System.Drawing.Size(226, 23);
            this.uploadButton_.TabIndex = 3;
            this.uploadButton_.Text = "Upload";
            this.uploadButton_.UseVisualStyleBackColor = true;
            this.uploadButton_.Click += new System.EventHandler(this.uploadButton_Click);
            // 
            // transmissionProgressBar_
            // 
            this.transmissionProgressBar_.Location = new System.Drawing.Point(14, 471);
            this.transmissionProgressBar_.Name = "transmissionProgressBar_";
            this.transmissionProgressBar_.Size = new System.Drawing.Size(531, 23);
            this.transmissionProgressBar_.TabIndex = 4;
            // 
            // settingsButton_
            // 
            this.settingsButton_.Location = new System.Drawing.Point(230, 8);
            this.settingsButton_.Name = "settingsButton_";
            this.settingsButton_.Size = new System.Drawing.Size(115, 23);
            this.settingsButton_.TabIndex = 5;
            this.settingsButton_.Text = "Settings";
            this.settingsButton_.UseVisualStyleBackColor = true;
            this.settingsButton_.Click += new System.EventHandler(this.settingsButton_Click);
            // 
            // bucketLabel_
            // 
            this.bucketLabel_.AutoSize = true;
            this.bucketLabel_.Location = new System.Drawing.Point(12, 11);
            this.bucketLabel_.Name = "bucketLabel_";
            this.bucketLabel_.Size = new System.Drawing.Size(47, 12);
            this.bucketLabel_.TabIndex = 6;
            this.bucketLabel_.Text = "Bucket:";
            // 
            // bucketComboBox_
            // 
            this.bucketComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.bucketComboBox_.FormattingEnabled = true;
            this.bucketComboBox_.Location = new System.Drawing.Point(66, 9);
            this.bucketComboBox_.Name = "bucketComboBox_";
            this.bucketComboBox_.Size = new System.Drawing.Size(148, 20);
            this.bucketComboBox_.TabIndex = 7;
            this.bucketComboBox_.SelectedIndexChanged += new System.EventHandler(this.bucketComboBox_SelectedIndexChanged);
            // 
            // selectFileButton_
            // 
            this.selectFileButton_.Location = new System.Drawing.Point(551, 442);
            this.selectFileButton_.Name = "selectFileButton_";
            this.selectFileButton_.Size = new System.Drawing.Size(226, 23);
            this.selectFileButton_.TabIndex = 8;
            this.selectFileButton_.Text = "Select a File";
            this.selectFileButton_.UseVisualStyleBackColor = true;
            this.selectFileButton_.Click += new System.EventHandler(this.selectFileButton_Click);
            // 
            // objectDataGridView_
            // 
            this.objectDataGridView_.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.objectDataGridView_.Location = new System.Drawing.Point(14, 42);
            this.objectDataGridView_.Name = "objectDataGridView_";
            this.objectDataGridView_.ReadOnly = true;
            this.objectDataGridView_.RowTemplate.Height = 23;
            this.objectDataGridView_.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.objectDataGridView_.Size = new System.Drawing.Size(763, 385);
            this.objectDataGridView_.TabIndex = 9;
            // 
            // BaiduBOSForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 535);
            this.Controls.Add(this.objectDataGridView_);
            this.Controls.Add(this.selectFileButton_);
            this.Controls.Add(this.bucketComboBox_);
            this.Controls.Add(this.bucketLabel_);
            this.Controls.Add(this.settingsButton_);
            this.Controls.Add(this.transmissionProgressBar_);
            this.Controls.Add(this.uploadButton_);
            this.Controls.Add(this.filePathTextBox_);
            this.Name = "BaiduBOSForm";
            this.Text = "Baidu BOS";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.BaiduBOSForm_FormClosed);
            this.Load += new System.EventHandler(this.BaiduBOSForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.objectDataGridView_)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox filePathTextBox_;
        private System.Windows.Forms.Button uploadButton_;
        private System.Windows.Forms.ProgressBar transmissionProgressBar_;
        private System.Windows.Forms.Button settingsButton_;
        private System.Windows.Forms.Label bucketLabel_;
        private System.Windows.Forms.ComboBox bucketComboBox_;
        private System.Windows.Forms.Button selectFileButton_;
        private DataGridViewEx objectDataGridView_;
    }
}

