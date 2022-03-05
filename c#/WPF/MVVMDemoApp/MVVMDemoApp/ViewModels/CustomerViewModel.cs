namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Windows.Input;

    using MVVMDemoApp.Models;

    class CustomerViewModel : WorkspaceViewModel
    {
        public CustomerViewModel(Customer customer)
        {
            customer_ = customer;
        }

        public Customer Customer => customer_;

        public string FirstName
        {
            get => customer_.FirstName;
            set
            {
                if (customer_.FirstName != value)
                {
                    customer_.FirstName = value;
                    OnPropertyChanged("FirstName");
                }
            }
        }

        public string LastName
        {
            get => customer_.LastName;
            set
            {
                if (customer_.LastName != value)
                {
                    customer_.LastName = value;
                    OnPropertyChanged("LastName");
                }
            }
        }

        public string Email
        {
            get => customer_.Email;
            set
            {
                if (customer_.Email != value)
                {
                    customer_.Email = value;
                    OnPropertyChanged("Email");
                }
            }
        }

        public string[] CustomerTypeOptions => customerTypeOptions_;

        public string Type
        {
            get => customer_.Type.ToString();
            set
            {
                if (string.IsNullOrEmpty(value) || value == customer_.Type.ToString())
                    return;

                switch (value)
                {
                    case "Company":
                        customer_.Type = CustomerType.Company;
                        customer_.IsCompany = true;
                        break;
                    case "Person":
                        customer_.Type = CustomerType.Person;
                        customer_.IsCompany = false;
                        break;
                    default:
                        throw new ArgumentException("Type");
                }

                OnPropertyChanged("Type");
                OnPropertyChanged("LastName");
            }
        }

        public override string DisplayName
        {
            get
            {
                return isNewCustomer_ ? "New Customer" :
                    customer_.Type == CustomerType.Company ? FirstName :
                    FirstName + " " + LastName;
            }
        }

        public decimal TotalSales => customer_.TotalSales;

        public ICommand SaveCommand => saveCommand_;


        private readonly Customer customer_;
        private bool isNewCustomer_;
        private string[] customerTypeOptions_ = new string[] { "(Not Specified)", "Person", "Company" };
        private readonly ICommand saveCommand_;
    }
}
