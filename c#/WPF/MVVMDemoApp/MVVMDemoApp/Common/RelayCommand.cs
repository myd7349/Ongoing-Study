namespace MVVMDemoApp.Common
{
    using System;
    using System.Windows.Input;

    public class RelayCommand : ICommand
    {
        public RelayCommand(Action<object> execute)
            : this(execute, null)
        {
        }

        public RelayCommand(Action<object> execute, Predicate<object> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException(nameof(execute));

            execute_ = execute;
            canExecute_ = canExecute;
        }

        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return canExecute_ == null || canExecute_(parameter);
        }

        public void Execute(object parameter)
        {
            execute_?.Invoke(parameter);
        }

        private readonly Action<object> execute_;
        private readonly Predicate<object> canExecute_;
    }
}
