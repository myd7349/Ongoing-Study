namespace BaiduBOSDemo
{
    partial class ObjectMetaDataForm
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
            this.objectPropertyGrid_ = new System.Windows.Forms.PropertyGrid();
            this.SuspendLayout();
            // 
            // objectPropertyGrid_
            // 
            this.objectPropertyGrid_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.objectPropertyGrid_.HelpVisible = false;
            this.objectPropertyGrid_.Location = new System.Drawing.Point(24, 64);
            this.objectPropertyGrid_.Name = "objectPropertyGrid_";
            this.objectPropertyGrid_.Size = new System.Drawing.Size(475, 403);
            this.objectPropertyGrid_.TabIndex = 0;
            // 
            // ObjectMetaDataForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 490);
            this.Controls.Add(this.objectPropertyGrid_);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ObjectMetaDataForm";
            this.Text = "Object MetaData";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PropertyGrid objectPropertyGrid_;
    }
}