namespace BaiduBOSDemo
{
    using System;
    using System.Threading;
    using System.Windows.Forms;

    class ProgressBarReporter : IProgress<int>
    {
        public ProgressBarReporter(ProgressBar progressBar, SynchronizationContext synchronizationContext)
        {
            progressBar_ = progressBar;
            synchronizationContext_ = synchronizationContext;
        }

        public void Report(int value)
        {
            synchronizationContext_.Post(_ => progressBar_.Value = value, null);
        }

        private ProgressBar progressBar_;
        private SynchronizationContext synchronizationContext_;
    }
}
