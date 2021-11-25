
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
            this.exportAsButton_ = new System.Windows.Forms.Button();
            this.orientationGroupBox_ = new System.Windows.Forms.GroupBox();
            this.twoHundredSeventyDegreeRadioButton_ = new System.Windows.Forms.RadioButton();
            this.oneHundredEightyDegreeRadioButton_ = new System.Windows.Forms.RadioButton();
            this.ninetyDegreeRadioButton_ = new System.Windows.Forms.RadioButton();
            this.zeroDegreeRadioButton_ = new System.Windows.Forms.RadioButton();
            this.doubleBufferedCheckBox_ = new System.Windows.Forms.CheckBox();
            this.backgroundGroupBox_.SuspendLayout();
            this.orientationGroupBox_.SuspendLayout();
            this.SuspendLayout();
            // 
            // openButton_
            // 
            this.openButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.openButton_.Location = new System.Drawing.Point(706, 12);
            this.openButton_.Name = "openButton_";
            this.openButton_.Size = new System.Drawing.Size(126, 31);
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
            this.sizeModeComboBox_.Location = new System.Drawing.Point(706, 123);
            this.sizeModeComboBox_.Name = "sizeModeComboBox_";
            this.sizeModeComboBox_.Size = new System.Drawing.Size(126, 20);
            this.sizeModeComboBox_.TabIndex = 1;
            this.sizeModeComboBox_.SelectedIndexChanged += new System.EventHandler(this.sizeModeComboBox__SelectedIndexChanged);
            // 
            // backgroundGroupBox_
            // 
            this.backgroundGroupBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.backgroundGroupBox_.Controls.Add(this.colorRadioButton_);
            this.backgroundGroupBox_.Controls.Add(this.transparentRadioButton_);
            this.backgroundGroupBox_.Location = new System.Drawing.Point(706, 149);
            this.backgroundGroupBox_.Name = "backgroundGroupBox_";
            this.backgroundGroupBox_.Size = new System.Drawing.Size(126, 67);
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
            this.colorRadioButton_.CheckedChanged += new System.EventHandler(this.backgroundRadioButton__CheckedChanged);
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
            this.transparentRadioButton_.CheckedChanged += new System.EventHandler(this.backgroundRadioButton__CheckedChanged);
            // 
            // metafileCanvas_
            // 
            this.metafileCanvas_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.metafileCanvas_.IsDoubleBuffered = false;
            this.metafileCanvas_.Location = new System.Drawing.Point(12, 12);
            this.metafileCanvas_.Metafile = null;
            this.metafileCanvas_.Name = "metafileCanvas_";
            this.metafileCanvas_.Orientation = 0;
            this.metafileCanvas_.OriginalMetafile = null;
            this.metafileCanvas_.Size = new System.Drawing.Size(676, 426);
            this.metafileCanvas_.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.metafileCanvas_.TabIndex = 2;
            // 
            // propertiesButton_
            // 
            this.propertiesButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.propertiesButton_.Location = new System.Drawing.Point(706, 86);
            this.propertiesButton_.Name = "propertiesButton_";
            this.propertiesButton_.Size = new System.Drawing.Size(126, 31);
            this.propertiesButton_.TabIndex = 4;
            this.propertiesButton_.Text = "Properties...";
            this.propertiesButton_.UseVisualStyleBackColor = true;
            this.propertiesButton_.Click += new System.EventHandler(this.propertiesButton__Click);
            // 
            // exportAsButton_
            // 
            this.exportAsButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.exportAsButton_.Location = new System.Drawing.Point(706, 49);
            this.exportAsButton_.Name = "exportAsButton_";
            this.exportAsButton_.Size = new System.Drawing.Size(126, 31);
            this.exportAsButton_.TabIndex = 5;
            this.exportAsButton_.Text = "Export As...";
            this.exportAsButton_.UseVisualStyleBackColor = true;
            this.exportAsButton_.Click += new System.EventHandler(this.exportAsButton__Click);
            // 
            // orientationGroupBox_
            // 
            this.orientationGroupBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.orientationGroupBox_.Controls.Add(this.twoHundredSeventyDegreeRadioButton_);
            this.orientationGroupBox_.Controls.Add(this.oneHundredEightyDegreeRadioButton_);
            this.orientationGroupBox_.Controls.Add(this.ninetyDegreeRadioButton_);
            this.orientationGroupBox_.Controls.Add(this.zeroDegreeRadioButton_);
            this.orientationGroupBox_.Location = new System.Drawing.Point(706, 222);
            this.orientationGroupBox_.Name = "orientationGroupBox_";
            this.orientationGroupBox_.Size = new System.Drawing.Size(126, 112);
            this.orientationGroupBox_.TabIndex = 6;
            this.orientationGroupBox_.TabStop = false;
            this.orientationGroupBox_.Text = "Orientation";
            // 
            // twoHundredSeventyDegreeRadioButton_
            // 
            this.twoHundredSeventyDegreeRadioButton_.AutoSize = true;
            this.twoHundredSeventyDegreeRadioButton_.Location = new System.Drawing.Point(12, 86);
            this.twoHundredSeventyDegreeRadioButton_.Name = "twoHundredSeventyDegreeRadioButton_";
            this.twoHundredSeventyDegreeRadioButton_.Size = new System.Drawing.Size(53, 16);
            this.twoHundredSeventyDegreeRadioButton_.TabIndex = 3;
            this.twoHundredSeventyDegreeRadioButton_.TabStop = true;
            this.twoHundredSeventyDegreeRadioButton_.Text = "270°";
            this.twoHundredSeventyDegreeRadioButton_.UseVisualStyleBackColor = true;
            this.twoHundredSeventyDegreeRadioButton_.CheckedChanged += new System.EventHandler(this.orientationRadioButton__CheckedChanged);
            // 
            // oneHundredEightyDegreeRadioButton_
            // 
            this.oneHundredEightyDegreeRadioButton_.AutoSize = true;
            this.oneHundredEightyDegreeRadioButton_.Location = new System.Drawing.Point(12, 64);
            this.oneHundredEightyDegreeRadioButton_.Name = "oneHundredEightyDegreeRadioButton_";
            this.oneHundredEightyDegreeRadioButton_.Size = new System.Drawing.Size(53, 16);
            this.oneHundredEightyDegreeRadioButton_.TabIndex = 2;
            this.oneHundredEightyDegreeRadioButton_.TabStop = true;
            this.oneHundredEightyDegreeRadioButton_.Text = "180°";
            this.oneHundredEightyDegreeRadioButton_.UseVisualStyleBackColor = true;
            this.oneHundredEightyDegreeRadioButton_.CheckedChanged += new System.EventHandler(this.orientationRadioButton__CheckedChanged);
            // 
            // ninetyDegreeRadioButton_
            // 
            this.ninetyDegreeRadioButton_.AutoSize = true;
            this.ninetyDegreeRadioButton_.Location = new System.Drawing.Point(12, 42);
            this.ninetyDegreeRadioButton_.Name = "ninetyDegreeRadioButton_";
            this.ninetyDegreeRadioButton_.Size = new System.Drawing.Size(47, 16);
            this.ninetyDegreeRadioButton_.TabIndex = 1;
            this.ninetyDegreeRadioButton_.TabStop = true;
            this.ninetyDegreeRadioButton_.Text = "90°";
            this.ninetyDegreeRadioButton_.UseVisualStyleBackColor = true;
            this.ninetyDegreeRadioButton_.CheckedChanged += new System.EventHandler(this.orientationRadioButton__CheckedChanged);
            // 
            // zeroDegreeRadioButton_
            // 
            this.zeroDegreeRadioButton_.AutoSize = true;
            this.zeroDegreeRadioButton_.Location = new System.Drawing.Point(12, 20);
            this.zeroDegreeRadioButton_.Name = "zeroDegreeRadioButton_";
            this.zeroDegreeRadioButton_.Size = new System.Drawing.Size(41, 16);
            this.zeroDegreeRadioButton_.TabIndex = 0;
            this.zeroDegreeRadioButton_.TabStop = true;
            this.zeroDegreeRadioButton_.Text = "0°";
            this.zeroDegreeRadioButton_.UseVisualStyleBackColor = true;
            this.zeroDegreeRadioButton_.CheckedChanged += new System.EventHandler(this.orientationRadioButton__CheckedChanged);
            // 
            // doubleBufferedCheckBox_
            // 
            this.doubleBufferedCheckBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.doubleBufferedCheckBox_.AutoSize = true;
            this.doubleBufferedCheckBox_.Location = new System.Drawing.Point(718, 340);
            this.doubleBufferedCheckBox_.Name = "doubleBufferedCheckBox_";
            this.doubleBufferedCheckBox_.Size = new System.Drawing.Size(114, 16);
            this.doubleBufferedCheckBox_.TabIndex = 7;
            this.doubleBufferedCheckBox_.Text = "Double buffered";
            this.doubleBufferedCheckBox_.UseVisualStyleBackColor = true;
            this.doubleBufferedCheckBox_.CheckedChanged += new System.EventHandler(this.doubleBufferedCheckBox__CheckedChanged);
            // 
            // MetafileViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(853, 450);
            this.Controls.Add(this.doubleBufferedCheckBox_);
            this.Controls.Add(this.orientationGroupBox_);
            this.Controls.Add(this.exportAsButton_);
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
            this.orientationGroupBox_.ResumeLayout(false);
            this.orientationGroupBox_.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button openButton_;
        private System.Windows.Forms.ComboBox sizeModeComboBox_;
        private MetafileCanvas metafileCanvas_;
        private System.Windows.Forms.GroupBox backgroundGroupBox_;
        private System.Windows.Forms.RadioButton colorRadioButton_;
        private System.Windows.Forms.RadioButton transparentRadioButton_;
        private System.Windows.Forms.Button propertiesButton_;
        private System.Windows.Forms.Button exportAsButton_;
        private System.Windows.Forms.GroupBox orientationGroupBox_;
        private System.Windows.Forms.RadioButton ninetyDegreeRadioButton_;
        private System.Windows.Forms.RadioButton zeroDegreeRadioButton_;
        private System.Windows.Forms.RadioButton twoHundredSeventyDegreeRadioButton_;
        private System.Windows.Forms.RadioButton oneHundredEightyDegreeRadioButton_;
        private System.Windows.Forms.CheckBox doubleBufferedCheckBox_;
    }
}

