namespace MetafileViewer
{
    using System;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using NLog;

    static class Program
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Logger.Info("==================================== Startup ====================================");

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

#if !DEBUG
            Application.ThreadException += Application_ThreadException;
            TaskScheduler.UnobservedTaskException += TaskScheduler_UnobservedTaskException;
#endif

            Application.Run(args.Length > 0 ? new MetafileViewerForm(args[0]) : new MetafileViewerForm());

            Logger.Info("=================================================================================");
        }

        private static void Application_ThreadException(object sender, System.Threading.ThreadExceptionEventArgs e)
        {
            Logger.Fatal(e.Exception, "Unhandled thread exception:\r\n{0}", e.Exception);
            MessageBox.Show(e.Exception.ToString(), "Unhandled thread exception:", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private static void TaskScheduler_UnobservedTaskException(object sender, UnobservedTaskExceptionEventArgs e)
        {
            Logger.Fatal(e.Exception, "Unobserved task exception:\r\n{0}", e.Exception);
            MessageBox.Show(e.Exception.ToString(), "Unobserved task exception:", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}


// References:
// [Can a WinForms program be run from command line?](https://stackoverflow.com/questions/21678217/can-a-winforms-program-be-run-from-command-line)
