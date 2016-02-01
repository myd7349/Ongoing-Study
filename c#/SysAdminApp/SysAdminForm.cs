using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SysAdminApp
{
    public partial class SysAdminForm : Form
    {
        private SortedDictionary<string, bool> driveVisibilityDict;
        private bool isInitialized = false;

        public SysAdminForm()
        {
            InitializeComponent();

            driveVisibilityDict = SysAdmin.GetDriveVisibilityDict();
            PopulateDrivesListBox();

            noDispCPLCheckBox.CheckState = GetCheckState(SysAdmin.GetNoDispCPL());
            noSetFoldersCheckBox.CheckState = GetCheckState(SysAdmin.GetNoSetFolders());
            disableRegistryToolsCheckBox.CheckState = GetCheckState(SysAdmin.GetDisableRegistryTools());

            if (SysAdmin.IsWinVistaOrHigher())
            {
                noSetFoldersCheckBox.Hide();
                disableRegistryToolsCheckBox.Hide();
            }

            isInitialized = true;
        }

        private void PopulateDrivesListBox()
        {
            foreach (var item in driveVisibilityDict)
            {
                drivesCheckedListBox.Items.Add(item.Key, !item.Value);
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
            SysAdmin.SetNoSetFolders(IsChecked(noSetFoldersCheckBox));
            SysAdmin.SetDisableRegistryTools(IsChecked(disableRegistryToolsCheckBox));
        }

        private void drivesCheckedListBox_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (!isInitialized)
                return;

            string driveName = drivesCheckedListBox.Items[e.Index].ToString();
            driveVisibilityDict[driveName] = (e.NewValue == CheckState.Unchecked);
        }

        private static CheckState GetCheckState(bool isChecked)
        {
            return isChecked ? CheckState.Checked : CheckState.Unchecked;
        }

        private static bool IsChecked(CheckBox checkBox)
        {
            return checkBox.CheckState == CheckState.Checked;
        }
    }
}
