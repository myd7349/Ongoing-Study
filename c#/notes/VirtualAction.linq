<Query Kind="Program" />

void Main()
{
    var viewModel = new DerivedViewModel();
    viewModel.ClickCommand.Execute(null);
}

public interface ICommand
{
    void Execute(object parameter);
}

class RelayCommand : ICommand
{
    public RelayCommand(Action action)
    {
        action_ = action;
    }

    public void Execute(object parameter)
    {
        action_?.Invoke();
    }
    
    private Action action_;
}

public class BaseViewModel
{
    public BaseViewModel()
    {
        ClickCommand = new RelayCommand(OnClick);
    }

    public ICommand ClickCommand { get; }

    protected virtual void OnClick()
    {
        Console.WriteLine("BaseViewModel");
    }
}

public class DerivedViewModel : BaseViewModel
{
    protected override void OnClick()
    {
        Console.WriteLine("DerivedViewModel");
    }
}


// References:
// [Action<T> vs virtual methods](https://stackoverflow.com/questions/11122717/actiont-vs-virtual-methods)
