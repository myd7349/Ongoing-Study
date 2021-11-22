
namespace MetafileViewer
{
    partial class MetafileViewerForm
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
            this.openButton_ = new System.Windows.Forms.Button();
            this.sizeModeComboBox_ = new System.Windows.Forms.ComboBox();
            this.backgroundGroupBox_ = new System.Windows.Forms.GroupBox();
            this.colorRadioButton_ = new System.Windows.Forms.RadioButton();
            this.transparentRadioButton_ = new System.Windows.Forms.RadioButton();
            this.metafileCanvas_ = new MetafileViewer.MetafileCanvas();
            this.propertiesButton_ = new System.Windows.Forms.Button();
            this.backgroundGroupBox_.SuspendLayout();
            this.SuspendLayout();
            // 
            // openButton_
            // 
            this.openButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.openButton_.Location = new System.Drawing.Point(691, 12);
            this.openButton_.Name = "openButton_";
            this.openButton_.Size = new System.Drawing.Size(107, 31);
            this.openButton_.TabIndex = 0;
            this.openButton_.Text = "Open...";
            this.openButton_.UseVisualStyleBackColor = true;
            this.openButton_.Click += new System.EventHandler(this.openButton__Click);
            // 
            // sizeModeComboBox_
            // 
            this.sizeModeComboBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.sizeModeComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.sizeModeComboBox_.FormattingEnabled = true;
            this.sizeModeComboBox_.Location = new System.Drawing.Point(691, 91);
            this.sizeModeComboBox_.Name = "sizeModeComboBox_";
            this.sizeModeComboBox_.Size = new System.Drawing.Size(107, 20);
            this.sizeModeComboBox_.TabIndex = 1;
            this.sizeModeComboBox_.SelectedIndexChanged += new System.EventHandler(this.sizeModeComboBox__SelectedIndexChanged);
            // 
            // backgroundGroupBox_
            // 
            this.backgroundGroupBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.backgroundGroupBox_.Controls.Add(this.colorRadioButton_);
            this.backgroundGroupBox_.Controls.Add(this.transparentRadioButton_);
            this.backgroundGroupBox_.Location = new System.Drawing.Point(691, 129);
            this.backgroundGroupBox_.Name = "backgroundGroupBox_";
            this.backgroundGroupBox_.Size = new System.Drawing.Size(107, 67);
            this.backgroundGroupBox_.TabIndex = 3;
            this.backgroundGroupBox_.TabStop = false;
            this.backgroundGroupBox_.Text = "Background";
            // 
            // colorRadioButton_
            // 
            this.colorRadioButton_.AutoSize = true;
            this.colorRadioButton_.Location = new System.Drawing.Point(12, 42);
            this.colorRadioButton_.Name = "colorRadioButton_";
            this.colorRadioButton_.Size = new System.Drawing.Size(53, 16);
            this.colorRadioButton_.TabIndex = 1;
            this.colorRadioButton_.TabStop = true;
            this.colorRadioButton_.Text = "Color";
            this.colorRadioButton_.UseVisualStyleBackColor = true;
            this.colorRadioButton_.CheckedChanged += new System.EventHandler(this.transparentRadioButton__CheckedChanged);
            // 
            // transparentRadioButton_
            // 
            this.transparentRadioButton_.AutoSize = true;
            this.transparentRadioButton_.Location = new System.Drawing.Point(12, 20);
            this.transparentRadioButton_.Name = "transparentRadioButton_";
            this.transparentRadioButton_.Size = new System.Drawing.Size(89, 16);
            this.transparentRadioButton_.TabIndex = 0;
            this.transparentRadioButton_.TabStop = true;
            this.transparentRadioButton_.Text = "Transparent";
            this.transparentRadioButton_.UseVisualStyleBackColor = true;
            this.transparentRadioButton_.CheckedChanged += new System.EventHandler(this.transparentRadioButton__CheckedChanged);
            // 
            // metafileCanvas_
            // 
            this.metafileCanvas_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.metafileCanvas_.Location = new System.Drawing.Point(12, 12);
            this.metafileCanvas_.Metafile = null;
            this.metafileCanvas_.Name = "metafileCanvas_";
            this.metafileCanvas_.Size = new System.Drawing.Size(657, 426);
            this.metafileCanvas_.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.metafileCanvas_.TabIndex = 2;
            // 
            // propertiesButton_
            // 
            this.propertiesButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.propertiesButton_.Location = new System.Drawing.Point(691, 49);
            this.propertiesButton_.Name = "propertiesButton_";
            this.propertiesButton_.Size = new System.Drawing.Size(107, 31);
            this.propertiesButton_.TabIndex = 4;
            this.propertiesButton_.Text = "Properties...";
            this.propertiesButton_.UseVisualStyleBackColor = true;
            this.propertiesButton_.Click += new System.EventHandler(this.propertiesButton__Click);
            // 
            // MetafileViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(824, 450);
            this.Controls.Add(this.propertiesButton_);
            this.Controls.Add(this.backgroundGroupBox_);
            this.Controls.Add(this.metafileCanvas_);
            this.Controls.Add(this.sizeModeComboBox_);
            this.Controls.Add(this.openButton_);
            this.Name = "MetafileViewerForm";
            this.Text = "Metafile Viewer";
            this.Load += new System.EventHandler(this.MetafileViewerForm_Load);
            this.backgroundGroupBox_.ResumeLayout(false);
            this.backgroundGroupBox_.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button openButton_;
        private System.Windows.Forms.ComboBox sizeModeComboBox_;
        private MetafileCanvas metafileCanvas_;
        private System.Windows.Forms.GroupBox backgroundGroupBox_;
        private System.Windows.Forms.RadioButton colorRadioButton_;
        private System.Windows.Forms.RadioButton transparentRadioButton_;
        private System.Windows.Forms.Button propertiesButton_;
    }
}

