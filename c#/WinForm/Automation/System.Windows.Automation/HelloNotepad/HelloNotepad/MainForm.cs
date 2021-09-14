namespace HelloNotepad
{
    using System;
    using System.Diagnostics;
    using System.Windows.Automation;
    using System.Windows.Forms;

    using Common;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void button__Click(object sender, EventArgs e)
        {
            var notepadProcess = Process.Start("notepad.exe");
            WaitUntilWindowIsVisible(notepadProcess.MainWindowHandle);

#if false
            var notepadWindow = AutomationElement.FromHandle(notepadProcess.MainWindowHandle);
#else
            var notepadWindow = AutomationElement.RootElement.FindFirstChild("无标题 - 记事本", ControlType.Window);
#endif
            var notepadMenuBar = notepadWindow.FindFirstChild(ControlType.MenuBar);

            var notepadMenuItems = notepadMenuBar.FindAllChildren(ControlType.MenuItem);
            Debug.Assert(notepadMenuItems.Count == 5);
            Console.WriteLine(notepadMenuItems.Count);

            var helpMenu = notepadMenuItems[4];
            helpMenu.Expand();

            var expandedHelpMenu = notepadWindow.FindFirstDescendant(ControlType.Menu);
            var expandedHelpMenuItems = expandedHelpMenu.FindAllChildren(ControlType.MenuItem);
            Debug.Assert(expandedHelpMenuItems.Count == 3);
        }

        private static void WaitUntilWindowIsVisible(IntPtr window)
        {
            while (window == IntPtr.Zero)
            {
            }
        }
    }
}
