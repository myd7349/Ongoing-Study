
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
            this.propertiesComboBox_ = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // propertyGrid_
            // 
            this.propertyGrid_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.propertyGrid_.Location = new System.Drawing.Point(12, 38);
            this.propertyGrid_.Name = "propertyGrid_";
            this.propertyGrid_.Size = new System.Drawing.Size(305, 387);
            this.propertyGrid_.TabIndex = 1;
            // 
            // propertiesComboBox_
            // 
            this.propertiesComboBox_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.propertiesComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.propertiesComboBox_.FormattingEnabled = true;
            this.propertiesComboBox_.Items.AddRange(new object[] {
            "Metafile",
            "MetafileHeader",
            "ENHMETAHEADER"});
            this.propertiesComboBox_.Location = new System.Drawing.Point(12, 12);
            this.propertiesComboBox_.Name = "propertiesComboBox_";
            this.propertiesComboBox_.Size = new System.Drawing.Size(305, 20);
            this.propertiesComboBox_.TabIndex = 0;
            this.propertiesComboBox_.SelectedIndexChanged += new System.EventHandler(this.propertiesComboBox__SelectedIndexChanged);
            // 
            // MetafilePropertiesForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(329, 463);
            this.Controls.Add(this.propertiesComboBox_);
            this.Controls.Add(this.propertyGrid_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Name = "MetafilePropertiesForm";
            this.Text = "Properties";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PropertyGrid propertyGrid_;
        private System.Windows.Forms.ComboBox propertiesComboBox_;
    }
}
