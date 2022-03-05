namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Collections.ObjectModel;
    using System.Windows.Input;

    using MVVMDemoApp.Common;
    using MVVMDemoApp.Models;

    class AllCustomersViewModel : WorkspaceViewModel
    {
        public AllCustomersViewModel()
        {
            SelectCustomerCommand = new RelayCommand(OnCustomerSelected);
        }

        public override string DisplayName
        {
            get => "All Customers";
        }

        public ObservableCollection<CustomerViewModel> Customers => customers_;

        public ICommand SelectCustomerCommand
        {
            get;
            set;
        }

        public event EventHandler<EventArgs<Customer>> CustomerSelected;

        private void OnCustomerSelected(object selected)
        {
            var viewModel = selected as CustomerViewModel;
            var handler = CustomerSelected;
            if (handler != null)
                handler(this, new EventArgs<Customer>(viewModel.Customer));
        }

        private ObservableCollection<CustomerViewModel> customers_;
    }
}
