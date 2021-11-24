namespace ScriptPlayground
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using Common;

    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

#if !DEBUG
            Application.ThreadException += UnhandledException;
            TaskScheduler.UnobservedTaskException += UnobservedTaskException;
#endif

            Application.Run(new MainForm());
        }

#if !DEBUG
        private static void UnhandledException(object sender, ThreadExceptionEventArgs e)
        {
            MsgBox.ErrorFmt("Unhanled exception:\r\n{0}", e.Exception.ToString());
        }

        private static void UnobservedTaskException(object sender, UnobservedTaskExceptionEventArgs e)
        {
            MsgBox.ErrorFmt("Unobserved task exception:\r\n{0}", e.Exception.ToString());
        }
#endif
    }
}
