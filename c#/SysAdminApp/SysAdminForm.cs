using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
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

            noDispCPLCheckBox.CheckState = GetCheckedState(SysAdmin.GetNoDispCPL());
            noSetFoldersCheckBox.CheckState = GetCheckedState(SysAdmin.GetNoSetFolders());
            disableRegistryToolsCheckBox.CheckState = GetCheckedState(SysAdmin.GetDisableRegistryTools());

            isInitialized = true;
        }

        private void PopulateDrivesListBox()
        {
            foreach (var item in driveVisibilityDict)
            {
                drivesCheckedListBox.Items.Add(item.Key, !item.Value);
            }
        }

        private CheckState GetCheckedState(bool isChecked)
        {
            return isChecked ? CheckState.Checked : CheckState.Unchecked;
        }

        private bool IsChecked(CheckBox checkBox)
        {
            return checkBox.CheckState == CheckState.Checked;
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
    }
}
