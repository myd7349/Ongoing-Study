
namespace GetWeChatGroupMembers
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.chatListBox_ = new System.Windows.Forms.ListBox();
            this.tableLayoutPanel_ = new System.Windows.Forms.TableLayoutPanel();
            this.groupMembersListView_ = new System.Windows.Forms.ListView();
            this.toolStrip_ = new System.Windows.Forms.ToolStrip();
            this.getGroupsToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.getGroupMembersToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.tableLayoutPanel_.SuspendLayout();
            this.toolStrip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // chatListBox_
            // 
            this.chatListBox_.Dock = System.Windows.Forms.DockStyle.Fill;
            this.chatListBox_.FormattingEnabled = true;
            this.chatListBox_.HorizontalScrollbar = true;
            this.chatListBox_.ItemHeight = 17;
            this.chatListBox_.Location = new System.Drawing.Point(3, 3);
            this.chatListBox_.Name = "chatListBox_";
            this.chatListBox_.Size = new System.Drawing.Size(267, 508);
            this.chatListBox_.TabIndex = 0;
            // 
            // tableLayoutPanel_
            // 
            this.tableLayoutPanel_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel_.ColumnCount = 2;
            this.tableLayoutPanel_.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel_.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel_.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel_.Controls.Add(this.chatListBox_, 0, 0);
            this.tableLayoutPanel_.Controls.Add(this.groupMembersListView_, 1, 0);
            this.tableLayoutPanel_.Location = new System.Drawing.Point(12, 40);
            this.tableLayoutPanel_.Name = "tableLayoutPanel_";
            this.tableLayoutPanel_.RowCount = 1;
            this.tableLayoutPanel_.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel_.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 514F));
            this.tableLayoutPanel_.Size = new System.Drawing.Size(546, 514);
            this.tableLayoutPanel_.TabIndex = 1;
            // 
            // groupMembersListView_
            // 
            this.groupMembersListView_.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupMembersListView_.FullRowSelect = true;
            this.groupMembersListView_.GridLines = true;
            this.groupMembersListView_.HideSelection = false;
            this.groupMembersListView_.Location = new System.Drawing.Point(276, 3);
            this.groupMembersListView_.Name = "groupMembersListView_";
            this.groupMembersListView_.Size = new System.Drawing.Size(267, 508);
            this.groupMembersListView_.TabIndex = 1;
            this.groupMembersListView_.UseCompatibleStateImageBehavior = false;
            this.groupMembersListView_.View = System.Windows.Forms.View.Details;
            // 
            // toolStrip_
            // 
            this.toolStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getGroupsToolStripButton_,
            this.getGroupMembersToolStripButton_});
            this.toolStrip_.Location = new System.Drawing.Point(0, 0);
            this.toolStrip_.Name = "toolStrip_";
            this.toolStrip_.Size = new System.Drawing.Size(570, 25);
            this.toolStrip_.TabIndex = 2;
            this.toolStrip_.Text = "toolStrip1";
            // 
            // getGroupsToolStripButton_
            // 
            this.getGroupsToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.getGroupsToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.getGroupsToolStripButton_.Name = "getGroupsToolStripButton_";
            this.getGroupsToolStripButton_.Size = new System.Drawing.Size(121, 22);
            this.getGroupsToolStripButton_.Text = "Get Visible Groups";
            this.getGroupsToolStripButton_.Click += new System.EventHandler(this.getGroupsToolStripButton__Click);
            // 
            // getGroupMembersToolStripButton_
            // 
            this.getGroupMembersToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.getGroupMembersToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.getGroupMembersToolStripButton_.Name = "getGroupMembersToolStripButton_";
            this.getGroupMembersToolStripButton_.Size = new System.Drawing.Size(133, 22);
            this.getGroupMembersToolStripButton_.Text = "Get Group Members";
            this.getGroupMembersToolStripButton_.Click += new System.EventHandler(this.getGroupMembersToolStripButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(570, 566);
            this.Controls.Add(this.toolStrip_);
            this.Controls.Add(this.tableLayoutPanel_);
            this.Name = "MainForm";
            this.Text = "Get WeChat Group Members";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.tableLayoutPanel_.ResumeLayout(false);
            this.toolStrip_.ResumeLayout(false);
            this.toolStrip_.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox chatListBox_;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel_;
        private System.Windows.Forms.ToolStrip toolStrip_;
        private System.Windows.Forms.ToolStripButton getGroupsToolStripButton_;
        private System.Windows.Forms.ToolStripButton getGroupMembersToolStripButton_;
        private System.Windows.Forms.ListView groupMembersListView_;
    }
}

