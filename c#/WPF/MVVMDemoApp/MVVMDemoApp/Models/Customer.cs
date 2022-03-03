namespace MVVMDemoApp.Models
{
    using System;
    using System.ComponentModel;

    class Customer : IDataErrorInfo
    {
        public Customer()
        {
        }

        public CustomerType Type { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public string Email { get; set; }

        public bool IsCompany { get; set; }

        public bool IsValid { get; set; }

        public int TotalSales { get; set; }

        public string this[string columnName] => throw new NotImplementedException();

        public string Error => throw new NotImplementedException();

        public static Customer CreateCustomer()
        {
            return null;
        }

        public static Customer CreateNewCustomer()
        {
            return null;
        }
    }
}
