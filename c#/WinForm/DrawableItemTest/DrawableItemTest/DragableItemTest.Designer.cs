namespace DrawableItemTest
{
    partial class DragableItemTest
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
            this.SuspendLayout();
            // 
            // DragableItemTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(506, 370);
            this.Name = "DragableItemTest";
            this.Text = "DrawableItemTest";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.DragableItemTest_Paint);
            this.Layout += new System.Windows.Forms.LayoutEventHandler(this.DragableItemTest_Layout);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.DragableItemTest_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.DragableItemTest_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.DragableItemTest_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion
    }
}

