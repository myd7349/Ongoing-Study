// 2016-09-29T16:07+08:00
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

using FluentData;

namespace FluentDataDemo001
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private bool createDatabase()
        {
            var appPath = Application.StartupPath;
            var createCmd = Path.Combine(appPath, "CreateSQLiteDB.exe");
            var scriptPath = Path.Combine(appPath, "schema.sql");
            var targetDBPath = Path.Combine(appPath, "Students.db");

            try
            {
                var processStartInfo = new ProcessStartInfo(createCmd);
                processStartInfo.Arguments = $"\"{scriptPath}\" \"{targetDBPath}\"";
                processStartInfo.WindowStyle = ProcessWindowStyle.Hidden;

                Process.Start(processStartInfo);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Failed to create database file:",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }

            return true;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            if (!createDatabase())
                Close();
        }
    }
}
