namespace DragAndDropDemo
{
    using System.IO;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            AllowDrop = true;
            DragEnter += MainForm_DragEnter;
            DragDrop += MainForm_DragDrop;
        }

        private void MainForm_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Copy;
        }

        private void MainForm_DragDrop(object sender, DragEventArgs e)
        {
            var files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files.Length == 0)
                return;

            var path = files[0];
            if (File.Exists(path))
            {
                var fileInfo = new FileInfo(path);
                propertyGrid_.SelectedObject = fileInfo;
            }
            else if (Directory.Exists(path))
            {
                var directoryInfo = new DirectoryInfo(path);
                propertyGrid_.SelectedObject = directoryInfo;
            }
        }
    }
}


// References:
// [How do I drag and drop files into an application?](https://stackoverflow.com/questions/68598/how-do-i-drag-and-drop-files-into-an-application/89470)
// [Walkthrough: Performing a Drag-and-Drop Operation in Windows Forms](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/walkthrough-performing-a-drag-and-drop-operation-in-windows-forms?view=netframeworkdesktop-4.8)
// [How to drag & drop only one file on form window](https://stackoverflow.com/questions/26752826/how-to-drag-drop-only-one-file-on-form-window)
// [C# WinForms: Identify type of drag-drop action event](https://stackoverflow.com/questions/17453347/c-sharp-winforms-identify-type-of-drag-drop-action-event)
// [Control.DoDragDrop(Object, DragDropEffects) Method](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.control.dodragdrop?view=windowsdesktop-6.0)
