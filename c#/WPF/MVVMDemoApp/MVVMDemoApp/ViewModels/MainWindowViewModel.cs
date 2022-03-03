namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Collections.ObjectModel;
    using System.Collections.Specialized;

    class MainWindowViewModel : WorkspaceViewModel
    {
        public ObservableCollection<WorkspaceViewModel> Workspaces
        {
            get
            {
                if (workspaces_ == null)
                {
                    workspaces_ = new ObservableCollection<WorkspaceViewModel>();
                    workspaces_.CollectionChanged += OnWorkspacesChanged;
                }

                return workspaces_;
            }
        }

        private void OnWorkspacesChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems?.Count != 0)
            {
                foreach (WorkspaceViewModel workspace in e.NewItems)
                    workspace.RequestClose += OnWorkspaceRequestClose;
            }

            if (e.OldItems?.Count != 0)
            {
                foreach (WorkspaceViewModel workspace in e.OldItems)
                    workspace.RequestClose -= OnWorkspaceRequestClose;
            }
        }

        private void OnWorkspaceRequestClose(object sender, EventArgs e)
        {
            Workspaces.Remove(sender as WorkspaceViewModel);
        }

        private ObservableCollection<WorkspaceViewModel> workspaces_;
    }
}
