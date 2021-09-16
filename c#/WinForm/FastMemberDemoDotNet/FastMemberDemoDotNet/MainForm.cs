namespace FastMemberDemoDotNet
{
    using System.Collections.Generic;
    using System.Data;
    using System.Diagnostics;
    using System.Windows.Forms;

    using FastMember;

    using UIA.Extensions;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            dataGridView_.AsTable();
        }

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            var students = new List<Student>();
            for (int i = 0; i < 500; ++i)
            {
                var student = new Student();
                student.Name = Faker.Name.First();
                student.Address = Faker.Address.City();
                student.Age = Faker.RandomNumber.Next(10, 100);

                students.Add(student);
            }

            var dataTable = new DataTable();
            using (var reader = ObjectReader.Create(students, "Name", "Age", "Address"))
            {
                dataTable.Load(reader);
            }

            dataGridView_.DataSource = dataTable;
        }

        private void dataGridView__CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                var arguments = new List<string>
                {
                    Process.GetCurrentProcess().Id.ToString(),
                };

                if (e.RowIndex % 2 == 0)
                    arguments.Add("true");

                // Note:
                // Please copy these files to the target directory:
                //     UIAutomation.DotNet.runtimeconfig.json
                //     UIAutomation.DotNet.deps.json
                // otherwise, UIAutomation.DotNet.exe will not run
                // as expected.
                var processStartInfo = new ProcessStartInfo
                {
                    FileName = "UIAutomation.DotNet.exe",
                    Arguments = string.Join(" ", arguments),
                    //UseShellExecute = false,
                    //RedirectStandardOutput = true,
                    WindowStyle = ProcessWindowStyle.Hidden
                };
                var process = Process.Start(processStartInfo);
                //var output = process.StandardOutput.ReadToEnd();
                //if (!string.IsNullOrEmpty(output))
                //    MessageBox.Show(output);
            }
        }
    }
}


// References:
// [trying to Find First Child element that start with some letters or contains some letters](https://github.com/FlaUI/FlaUI/issues/409)
// https://gitter.im/FlaUI/Lobby?at=5943c09b6549436c7d52c510
// > if microsoft didn't implement the grid pattern in their winforms datagridview, there is not much flaui can do
// > but working with the headers and the rows is also possible without the grid patter
// > you can also check for modified datagridview controls
// > like above or here: https://github.com/northwoodspd/UIA.Extensions#datagridview
// > they expose some things to uia
// > but I havent tried that
// [.deps.json could not be found](https://stackoverflow.com/questions/37485968/deps-json-could-not-be-found)
