// 2016-09-29T16:07+08:00
using System;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Xml.Linq;
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

        private IDbContext Context
        {
            get { return new DbContext().ConnectionString(GetConnectionString(), new SqliteProvider()); }
        }

#if false
        private bool CreateDatabase()
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
#else
        private bool CreateDatabase()
        {
            Debug.Assert(Context != null);
            if (Context != null)
            {
                var appPath = Application.StartupPath;
                var scriptPath = Path.Combine(appPath, "schema.sql");

                try
                {
                    Context.Sql(File.ReadAllText(scriptPath)).Execute();
                    return true;
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString(), "Failed to create database file:",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }

            return false;
        }
#endif

        private string GetConnectionString()
        {
            var document = XDocument.Load(AppDomain.CurrentDomain.SetupInformation.ConfigurationFile);
            var addElements = document.Element("configuration").Element("connectionStrings").Elements("add");
            var addElement = addElements.Single(x => x.Attribute("name").Value == "FluentDataDemo001");
            return addElement.Attribute("connectionString").Value;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            var dbFile = GetConnectionString().Split(';').Single(x => x.StartsWith("Data Source")).Split('=').Last();
            Debug.Assert(dbFile != null);

            if (!File.Exists(dbFile) && !CreateDatabase())
                Close();

            var dataTable = Context.Sql("select * from Students").QuerySingle<DataTable>();

            dataGridView.AutoGenerateColumns = true;
            dataGridView.DataSource = dataTable;
        }
    }
}
