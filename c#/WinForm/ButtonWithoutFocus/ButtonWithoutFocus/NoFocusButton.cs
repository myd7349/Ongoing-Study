namespace ButtonWithoutFocus
{
    using System.Windows.Forms;

    public class NoFocusButton : Button
    {
        public NoFocusButton()
        {
            SetStyle(ControlStyles.Selectable, false);
        }
    }
}


// References:
// [C# Stop Button From Gaining Focus on Click](https://stackoverflow.com/questions/6741544/c-sharp-stop-button-from-gaining-focus-on-click)
// [PerformClick on custom button will not work](https://stackoverflow.com/questions/16951142/performclick-on-custom-button-will-not-work/31467870#31467870)
