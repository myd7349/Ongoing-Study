// 2018-01-25T13:16+08:00

namespace FastMemberDemo
{
    using System;
    using System.Data;
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
            var students = new Student[]
            {
                new Student() { Name = "Tom", Age = 12, Address = "NYC" },
                new Student() { Name = "Jerry", Age = 8, Address = "NYC" },
            };

            var dataTable = new DataTable();
            using (var reader = ObjectReader.Create(students, "Name", "Age", "Address"))
            {
                dataTable.Load(reader);
            }

            dataGridView1.DataSource = dataTable;
        }
    }
}

// https://stackoverflow.com/questions/564366/convert-generic-list-enumerable-to-datatable