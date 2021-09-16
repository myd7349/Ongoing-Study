namespace FastMemberDemo
{
    using System;
    using System.Collections.Generic;
    using System.Data;
    using System.Diagnostics;
    using System.Windows.Forms;

    using FastMember;


    public struct Student
    {
        public string Name;
        public int Age;
        public string Address;
    }

    public partial class FastMemberDemoForm : Form
    {
        public FastMemberDemoForm()
        {
            InitializeComponent();
        }

        private void FastMemberDemoForm_Load(object sender, EventArgs e)
        {
#if false
            var students = new Student[]
            {
                new Student() { Name = "Tom", Age = 12, Address = "NYC" },
                new Student() { Name = "Jerry", Age = 8, Address = "NYC" },
                new Student() { Name = "Lily", Age = 14, Address = "LA" },
                new Student() { Name = "Rick", Age = 66, Address = "LA" },
            };
#else
            var students = new List<Student>();
            for (int i = 0; i < 100; ++i)
            {
                var student = new Student();
                student.Name = Faker.Name.First();
                student.Address = Faker.Address.City();
                student.Age = Faker.RandomNumber.Next(10, 100);

                students.Add(student);
            }
#endif

            var dataTable = new DataTable();
            using (var reader = ObjectReader.Create(students, "Name", "Age", "Address"))
            {
                dataTable.Load(reader);
            }

            dataGridView.DataSource = dataTable;
        }

        private void dataGridView_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                var arguments = new List<string>
                {
                    Process.GetCurrentProcess().Id.ToString(),
                    MousePosition.X.ToString(),
                    MousePosition.Y.ToString(),
                };

                if (e.RowIndex % 2 == 0)
                    arguments.Add("true");

                var processStartInfo = new ProcessStartInfo
                {
                    FileName = "UIAutomation.exe",
                    Arguments = string.Join(" ", arguments),
                    CreateNoWindow = false,
                    WindowStyle = ProcessWindowStyle.Hidden
                };
                Process.Start(processStartInfo);
            }
        }
    }
}

// References:
// https://stackoverflow.com/questions/564366/convert-generic-list-enumerable-to-datatable
// [Double-click DataGridView row?](https://stackoverflow.com/questions/3920339/double-click-datagridview-row/3920860)
// [c# datagridview doubleclick on row with FullRowSelect](https://stackoverflow.com/questions/13706150/c-sharp-datagridview-doubleclick-on-row-with-fullrowselect)
// [How to get the Windows Desktop Application elements by Mouse Point?](https://github.com/FlaUI/FlaUI/issues/192)
