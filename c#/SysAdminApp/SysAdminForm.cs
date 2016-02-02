using System;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
using System.Resources;
using System.Threading;
using System.Windows.Forms;

namespace SysAdminApp
{
    public partial class SysAdminForm : Form
    {
        private Dictionary<string, string> uiLangDict;
        private SortedDictionary<string, bool> driveVisibilityDict;
        private bool isFormLoaded = false;

        public SysAdminForm()
        {
            uiLangDict = new Dictionary<string, string>();
            uiLangDict["zh-CN"] = Properties.Resources.zh_CN;
            uiLangDict["en-US"] = Properties.Resources.en_US;
            uiLangDict[Properties.Resources.zh_CN] = "zh-CN";
            uiLangDict[Properties.Resources.en_US] = "en-US";

            string uiLang = Properties.Settings.Default.UILang;
            if (uiLangDict.ContainsKey(uiLang))
            {
                Thread.CurrentThread.CurrentCulture = new CultureInfo(uiLang);
                Thread.CurrentThread.CurrentUICulture = new CultureInfo(uiLang);
            }

            InitializeComponent();

            driveVisibilityDict = SysAdmin.GetDriveVisibilityDict();
        }

        private void PopulateDrivesListBox()
        {
            foreach (var item in driveVisibilityDict)
            {
                drivesCheckedListBox.Items.Add(item.Key, !item.Value);
            }
        }

        private static CheckState GetCheckState(bool isChecked)
        {
            return isChecked ? CheckState.Checked : CheckState.Unchecked;
        }

        private static bool IsChecked(CheckBox checkBox)
        {
            return checkBox.CheckState == CheckState.Checked;
        }

        private void SysAdminForm_Load(object sender, EventArgs e)
        {
            SuspendLayout();

            Text = Properties.Resources.DialogTitle;
            langLabel.Text = Properties.Resources.UILang;
            noDrivesLabel.Text = Properties.Resources.NoDrives;
            noDispCPLCheckBox.Text = Properties.Resources.NoDispCPL;
            noSetFoldersCheckBox.Text = Properties.Resources.NoSetFolders;
            disableRegistryToolsCheckBox.Text = Properties.Resources.DisableRegistryTools;
            okButton.Text = Properties.Resources.Ok;
            cancelButton.Text = Properties.Resources.Cancel;
            applyButton.Text = Properties.Resources.Apply;

            langComboBox.Items.Add(Properties.Resources.zh_CN);
            langComboBox.Items.Add(Properties.Resources.en_US);

            string uiLang = Properties.Settings.Default.UILang;
            if (uiLangDict.ContainsKey(uiLang))
            {
                langComboBox.SelectedText = uiLangDict[uiLang];
            }
            else
            {
                langComboBox.SelectedText = uiLangDict["en-US"];
            }
             

            PopulateDrivesListBox();

            noDispCPLCheckBox.CheckState = GetCheckState(SysAdmin.GetNoDispCPL());
            noSetFoldersCheckBox.CheckState = GetCheckState(SysAdmin.GetNoSetFolders());
            disableRegistryToolsCheckBox.CheckState = GetCheckState(SysAdmin.GetDisableRegistryTools());

            if (SysAdmin.IsWinVistaOrHigher())
            {
                noSetFoldersCheckBox.Hide();
                disableRegistryToolsCheckBox.Hide();
            }

            ResumeLayout();
            
            isFormLoaded = true;
        }

        private void langComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            string uiLang = langComboBox.Text;

            if (uiLangDict.ContainsKey(uiLang))
            {
                Properties.Settings.Default.UILang = uiLangDict[uiLang];
                Properties.Settings.Default.Save();
            }
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            applyButton_Click(sender, e);
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void applyButton_Click(object sender, EventArgs e)
        {
            SysAdmin.SetDriveVisibility(driveVisibilityDict);
            SysAdmin.SetNoDispCPL(IsChecked(noDispCPLCheckBox));

            if (!SysAdmin.IsWinVistaOrHigher())
            {
                SysAdmin.SetNoSetFolders(IsChecked(noSetFoldersCheckBox));
                SysAdmin.SetDisableRegistryTools(IsChecked(disableRegistryToolsCheckBox));
            }
        }

        private void drivesCheckedListBox_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (!isFormLoaded)
                return;

            string driveName = drivesCheckedListBox.Items[e.Index].ToString();
            driveVisibilityDict[driveName] = (e.NewValue == CheckState.Unchecked);
        }
    }
}

// References:
// [Globalization Step-by-Step](https://msdn.microsoft.com/en-us/goglobal/bb688115.aspx)
// [C# Detect Windows OS Version - Part 1](https://andrewensley.com/2009/06/c-detect-windows-os-part-1/)
// [How to tell if the OS is Windows XP or higher?](http://stackoverflow.com/questions/2732432/how-to-tell-if-the-os-is-windows-xp-or-higher)
// [How to determine the Windows version by using Visual C#](https://support.microsoft.com/en-us/kb/304283)
// [Operating System Version](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724832%28v=vs.85%29.aspx)
// [WinForm二三事（四）界面布局（上）](http://www.cnblogs.com/yuyijq/archive/2010/01/20/1652082.html)
// [C#巧用anchor和dock设计复杂界面（控件随着窗体大小的变化而变化）](http://www.cnblogs.com/finallyliuyu/archive/2009/06/16/1504381.html)
