namespace GetWeChatGroupMembers
{
    using System;
    using System.Linq;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            groupMembersListView_.Columns.Add("ID", -2, HorizontalAlignment.Left);
            groupMembersListView_.Columns.Add("Name", -2, HorizontalAlignment.Left);
            groupMembersListView_.Columns.Add("Nickname", -2, HorizontalAlignment.Left);

            try
            {
                using (var wechat = new WeChatAssistant())
                {
                    var visibleChats = wechat.GetChatListElements();
                    var visibleChatNames = visibleChats.Select(chat => chat.Name).ToArray();
                    chatListBox_.Items.AddRange(visibleChatNames);

                    if (visibleChats.Length == 0)
                        return;

                    var firstVisibleGroup = visibleChats[0];
                    var groupMembers = wechat.GetGroupMemberElements(firstVisibleGroup);
                    int i = 1;
                    foreach (var member in groupMembers)
                    {
                        var memberItem = new ListViewItem(
                            new[]
                            {
                                i++.ToString(),
                                member.Item1.Name,
                                member.Item2.Name,
                            });
                        memberItem.Tag = member;
                        groupMembersListView_.Items.Add(memberItem);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Error:",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void getGroupsToolStripButton__Click(object sender, EventArgs e)
        {

        }

        private void getGroupMembersToolStripButton__Click(object sender, EventArgs e)
        {

        }
    }
}


// References:
// [Creating columns in listView and add items](https://stackoverflow.com/questions/11311153/creating-columns-in-listview-and-add-items)
