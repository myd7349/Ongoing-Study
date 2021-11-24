1. Catch unhandled exception and do logging

   https://github.com/cyanfish/naps2/blob/master/NAPS2.DI/EntryPoints/WinFormsEntryPoint.cs

   > ```c#
   > namespace NAPS2.DI.EntryPoints
   > {
   >     /// <summary>
   >     /// The entry point logic for NAPS2.exe, the NAPS2 GUI.
   >     /// </summary>
   >     public static class WinFormsEntryPoint
   >     {
   >         public static void Run(string[] args)
   >         {
   >             // Initialize Ninject (the DI framework)
   >             var kernel = new StandardKernel(new CommonModule(), new WinFormsModule());
   > 
   >             Paths.ClearTemp();
   > 
   >             // Parse the command-line arguments and see if we're doing something other than displaying the main form
   >             var lifecycle = kernel.Get<Lifecycle>();
   >             lifecycle.ParseArgs(args);
   >             lifecycle.ExitIfRedundant();
   > 
   >             // Start a pending worker process
   >             WorkerManager.Init();
   > 
   >             // Set up basic application configuration
   >             kernel.Get<CultureInitializer>().InitCulture(Thread.CurrentThread);
   >             Application.EnableVisualStyles();
   >             Application.SetCompatibleTextRenderingDefault(false);
   >             Application.ThreadException += UnhandledException;
   >             TaskScheduler.UnobservedTaskException += UnhandledTaskException;
   > 
   >             // Show the main form
   >             var formFactory = kernel.Get<IFormFactory>();
   >             var desktop = formFactory.Create<FDesktop>();
   >             Invoker.Current = desktop;
   >             Application.Run(desktop);
   >         }
   > 
   >         private static void UnhandledTaskException(object sender, UnobservedTaskExceptionEventArgs e)
   >         {
   >             Log.FatalException("An error occurred that caused the task to terminate.", e.Exception);
   >             e.SetObserved();
   >         }
   > 
   >         private static void UnhandledException(object sender, ThreadExceptionEventArgs e)
   >         {
   >             Log.FatalException("An error occurred that caused the application to close.", e.Exception);
   >         }
   >     }
   > }
   > ```

   https://github.com/3F/DllExport/blob/c1cc52fa13f563f97a2b4fe08bfb541c69195866/Wizard/UI/App.cs#L25-L83

   > ```csharp
   > using System;
   > using System.Threading;
   > using System.Windows.Forms;
   > using net.r_eg.MvsSln.Log;
   > 
   > namespace net.r_eg.DllExport.Wizard.UI
   > {
   >     internal static class App
   >     {
   >         private static object sync = new object();
   > 
   >         /// <summary>
   >         /// Execute form with single-threaded apartment model.
   >         /// </summary>
   >         /// <param name="frm"></param>
   >         public static void RunSTA(Form frm)
   >         {
   >             var thread = new Thread(() => Run(frm));
   >             thread.SetApartmentState(ApartmentState.STA);
   >             thread.Start();
   >             thread.Join();
   > 
   >             if(!frm.IsDisposed) {
   >                 frm.Dispose();
   >             }
   >         }
   > 
   >         private static void Run(Form frm)
   >         {
   >             Application.EnableVisualStyles();
   >             Application.SetUnhandledExceptionMode(UnhandledExceptionMode.Automatic);
   > 
   >             lock(sync) {
   >                 Application.ThreadException -= OnThreadException;
   >                 Application.ThreadException += OnThreadException;
   >             }
   > 
   >             try {
   >                 Application.Run(frm);
   >             }
   >             catch(Exception ex) {
   >                 UnknownFail(ex, false);
   >             }
   >         }
   > 
   >         private static void UnknownFail(Exception ex, bool threadEx)
   >         {
   >             LSender.Send<Executor>(
   >                 $"{ex.Message}{(threadEx ? "[TH]" : "[M]")}\n---\n{ex.ToString()}", 
   >                 MvsSln.Log.Message.Level.Fatal
   >             );
   >         }
   > 
   >         private static void OnThreadException(object sender, ThreadExceptionEventArgs e)
   >         {
   >             UnknownFail(e.Exception, true);
   >         }
   >     }
   > }
   > ```

2. [Do you end your exception messages with a period?](https://stackoverflow.com/questions/1136829/do-you-end-your-exception-messages-with-a-period)

   > Use grammatically correct error messages, **including ending  punctuation**. Each sentence in a description string of an exception  should end in a period. For example, "The log table has overflowed.”  would be an appropriate description string.

