
namespace MetafileViewer
{
    partial class MetafilePropertiesForm
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
            this.propertyGrid_ = new System.Windows.Forms.PropertyGrid();
            this.useGdi32CheckBox_ = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // propertyGrid_
            // 
            this.propertyGrid_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.propertyGrid_.Location = new System.Drawing.Point(12, 12);
            this.propertyGrid_.Name = "propertyGrid_";
            this.propertyGrid_.Size = new System.Drawing.Size(305, 420);
            this.propertyGrid_.TabIndex = 0;
            // 
            // useGdi32CheckBox_
            // 
            this.useGdi32CheckBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.useGdi32CheckBox_.AutoSize = true;
            this.useGdi32CheckBox_.Location = new System.Drawing.Point(12, 438);
            this.useGdi32CheckBox_.Name = "useGdi32CheckBox_";
            this.useGdi32CheckBox_.Size = new System.Drawing.Size(168, 16);
            this.useGdi32CheckBox_.TabIndex = 1;
            this.useGdi32CheckBox_.Text = "Use GetEnhMetaFileHeader";
            this.useGdi32CheckBox_.UseVisualStyleBackColor = true;
            this.useGdi32CheckBox_.CheckedChanged += new System.EventHandler(this.useGdi32CheckBox__CheckedChanged);
            // 
            // MetafilePropertiesForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(329, 463);
            this.Controls.Add(this.useGdi32CheckBox_);
            this.Controls.Add(this.propertyGrid_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Name = "MetafilePropertiesForm";
            this.Text = "Properties";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PropertyGrid propertyGrid_;
        private System.Windows.Forms.CheckBox useGdi32CheckBox_;
    }
}
