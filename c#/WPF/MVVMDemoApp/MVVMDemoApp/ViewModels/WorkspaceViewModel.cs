namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Windows.Input;

    abstract class WorkspaceViewModel : ViewModelBase
    {
        public WorkspaceViewModel()
        {
        }

        public ICommand CloseCommand
        {
            get;
            set;
        }

        public event EventHandler RequestClose;

        public void OnRequestClose()
        {
        }
    }
}
