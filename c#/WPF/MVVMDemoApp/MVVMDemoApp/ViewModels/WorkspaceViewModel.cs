namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Windows.Input;

    using MVVMDemoApp.Common;

    abstract class WorkspaceViewModel : ViewModelBase
    {
        public WorkspaceViewModel()
        {
            CloseCommand = new RelayCommand(p => OnRequestClose());
        }

        public ICommand CloseCommand
        {
            get;
            set;
        }

        public event EventHandler RequestClose;

        public void OnRequestClose()
        {
            var handler = RequestClose;
            if (handler != null)
                handler(this, EventArgs.Empty);
        }
    }
}
