namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;

    abstract class ViewModelBase : IDisposable, INotifyPropertyChanged
    {
        public string DisplayName
        {
            get;
            set;
        }

        public bool ThrowOnInvalidPropertyName
        {
            get;
            set;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            VerifyPropertyName(propertyName);

            var handler = PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                handler(this, e);
            }
        }

        private void OnDispose()
        {

        }

        [Conditional("DEBUG")]
        [DebuggerStepThrough]
        private void VerifyPropertyName(string propertyName)
        {
            // Verify that the property name matches a real,
            // public, instance property on this object.
            if (TypeDescriptor.GetProperties(this)[propertyName] == null)
            {
                var errorMessage = $"Invalid property name: {propertyName}";
                if (ThrowOnInvalidPropertyName)
                    throw new ArgumentException(errorMessage);
                else
                    Debug.Fail(errorMessage);

            }
        }
    }
}
