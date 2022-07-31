using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ColorMap.WPF
{
    /// <summary>
    /// Interaction logic for ColorMapControl.xaml
    /// </summary>
    public partial class ColorMapControl : UserControl
    {
        public ColorMapControl()
        {
            InitializeComponent();
        }

        public Orientation Orientation
        {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

        public static readonly DependencyProperty OrientationProperty =
            DependencyProperty.Register(
                nameof(Orientation),
                typeof(Orientation),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    Orientation.Vertical,
                    OnDependencyPropertyChanged));

        public string Palette
        {
            get { return (string)GetValue(PaletteProperty); }
            set { SetValue(PaletteProperty, value); }
        }

        public static readonly DependencyProperty PaletteProperty =
            DependencyProperty.Register(
                nameof(Palette),
                typeof(string),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    "rainbow",
                    OnDependencyPropertyChanged));

        public int Gradation
        {
            get { return (int)GetValue(GradationProperty); }
            set { SetValue(GradationProperty, value); }
        }

        public static readonly DependencyProperty GradationProperty =
            DependencyProperty.Register(
                nameof(Gradation),
                typeof(int),
                typeof(ColorMapControl),
                new UIPropertyMetadata(
                    256,
                    OnDependencyPropertyChanged,
                    CoerceGradationValueCallback));

        public bool ShowTicks
        {
            get { return (bool)GetValue(ShowTicksProperty); }
            set { SetValue(ShowTicksProperty, value); }
        }

        public static readonly DependencyProperty ShowTicksProperty =
            DependencyProperty.Register(
                nameof(ShowTicks),
                typeof(bool),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    false,
                    OnDependencyPropertyChanged));

        public Color TickColor
        {
            get { return (Color)GetValue(TickColorProperty); }
            set { SetValue(TickColorProperty, value); }
        }

        public static readonly DependencyProperty TickColorProperty =
            DependencyProperty.Register(
                nameof(TickColor),
                typeof(Color),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    Colors.Black,
                    OnDependencyPropertyChanged));

        public ImageSource ImageSource
        {
            get => (ImageSource)GetValue(ImageSourcePropertyKey.DependencyProperty);
        }

        internal static readonly DependencyPropertyKey ImageSourcePropertyKey =
            DependencyProperty.RegisterReadOnly(
                nameof(ImageSource),
                typeof(ImageSource),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata());

        private static void OnDependencyPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var colorMapControl = d as ColorMapControl;
            
            switch (e.Property.Name)
            {
                case nameof(Orientation):
                case nameof(Palette):
                case nameof(Gradation):
                case nameof(ShowTicks):
                case nameof(TickColor):
                    colorMapControl.CreateColorMapImage();
                    break;
            }
        }

        private static object CoerceGradationValueCallback(DependencyObject d, object baseValue)
        {
            var value = (int)baseValue;
            if (value < 2)
                return 2;

            if (value > 256)
                return 256;

            return value;
        }

        private void Image_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            CreateColorMapImage();
        }

        private void CreateColorMapImage()
        {
            var colorMapImage = SciColorMapHelper.CreateColorMapImage(
                Palette,
                Gradation,
                grid_.ActualWidth, //image_.ActualWidth,
                grid_.ActualHeight, //image_.ActualHeight,
                Orientation,
                ShowTicks,
                TickColor);
            SetValue(ImageSourcePropertyKey, colorMapImage);
        }
    }
}


// References
// [Setting a range of possible values of a dependency property](https://stackoverflow.com/questions/25643185/setting-a-range-of-possible-values-of-a-dependency-property)
// [Read-only dependency properties (WPF .NET)](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/properties/read-only-dependency-properties?view=netdesktop-6.0)
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationFramework/System/Windows/Controls/ContentControl.cs HasContent
