using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

using SciColorMap = SciColorMaps.Portable.ColorMap;

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

            LayoutUpdated += ColorMapControl_LayoutUpdated;
        }

        private void ColorMapControl_LayoutUpdated(object sender, EventArgs e)
        {
            if (ActualWidth > 0 && ActualHeight > 0)
            {
                CreateColorMapImage();

                LayoutUpdated -= ColorMapControl_LayoutUpdated;
            }
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

        public bool DrawEdge
        {
            get { return (bool)GetValue(DrawEdgeProperty); }
            set { SetValue(DrawEdgeProperty, value); }
        }

        public static readonly DependencyProperty DrawEdgeProperty =
            DependencyProperty.Register(
                nameof(DrawEdge),
                typeof(bool),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    false,
                    OnDependencyPropertyChanged));

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

        public int TickLength
        {
            get { return (int)GetValue(TickLengthProperty); }
            set { SetValue(TickLengthProperty, value); }
        }

        public static readonly DependencyProperty TickLengthProperty =
            DependencyProperty.Register(
                nameof(TickLength),
                typeof(int),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    3,
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

        public bool IsQualitative
        {
            get { return (bool)GetValue(IsQualitativeProperty); }
            set { SetValue(IsQualitativeProperty, value); }
        }

        public static readonly DependencyProperty IsQualitativeProperty =
            DependencyProperty.Register(
                nameof(IsQualitative),
                typeof(bool),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    true,
                    OnDependencyPropertyChanged));

        // Reverse/Mirror/Flip
        public bool IsReversed
        {
            get { return (bool)GetValue(IsReversedProperty); }
            set { SetValue(IsReversedProperty, value); }
        }

        public static readonly DependencyProperty IsReversedProperty =
            DependencyProperty.Register(
                nameof(IsReversed),
                typeof(bool),
                typeof(ColorMapControl),
                new FrameworkPropertyMetadata(
                    false,
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

        [Category("Behavior")]
        public event ColorMapChangedEventHandler ColorMapChanged
        {
            add { AddHandler(ColorMapChangedEvent, value); }
            remove { RemoveHandler(ColorMapChangedEvent, value); }
        }

        public static readonly RoutedEvent ColorMapChangedEvent =
            EventManager.RegisterRoutedEvent(
                nameof(ColorMapChanged),
                RoutingStrategy.Bubble,
                typeof(ColorMapChangedEventHandler),
                typeof(ColorMapControl));

        private static void OnDependencyPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var colorMapControl = d as ColorMapControl;
            
            switch (e.Property.Name)
            {
                case nameof(Palette):
                case nameof(Gradation):
                    //colorMapControl.RaiseEvent(
                    //    new RoutedEventArgs(ColorMapChangedEvent, colorMapControl));
                    colorMapControl.CreateColorMap();
                    colorMapControl.CreateColorMapImage();
                    break;
                case nameof(Orientation):
                case nameof(DrawEdge):
                case nameof(ShowTicks):
                case nameof(TickLength):
                case nameof(TickColor):
                case nameof(IsQualitative):
                case nameof(IsReversed):
                    colorMapControl.CreateColorMapImage();
                    break;
            }
        }

#if false
        protected override void OnInitialized(EventArgs e)
        {
            base.OnInitialized(e);

            CreateColorMapImage();
        }
#endif
        
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

            // TODO:
            // First, decrease the height of the window so that grid_.ActualHeight becomes 0.
            // then increase the height of the window again. At this point, you will find
            // that grid_.ActualHeight is still 0.
            // How to fix it? Set MinWidth & MinHeight of grid_:
            //     MinWidth="2" MinHeight="2"
            Trace.WriteLine($"Image size changed: {grid_.ActualWidth}x{grid_.ActualHeight}.");
        }

        private void CreateColorMap()
        {
            if (string.IsNullOrEmpty(Palette))
                cmap_ = null;
            else
                cmap_ = SciColorMapHelper.CreateColorMap(Palette, Gradation);

            RaiseEvent(new ColorMapChangedEventArgs(
                cmap_,
                IsQualitative,
                IsReversed,
                ColorMapChangedEvent,
                this));
        }

        private void CreateColorMapImage()
        {
            if (cmap_ == null)
                CreateColorMap();

            if (cmap_ == null)
            {
                SetValue(ImageSourcePropertyKey, null);
                return;
            }

            var colorMapImage = SciColorMapHelper.CreateColorMapImage(
                Palette,
                Gradation,
                grid_.ActualWidth, //image_.ActualWidth,
                grid_.ActualHeight, //image_.ActualHeight,
                Orientation,
                IsReversed,
                DrawEdge,
                ShowTicks,
                TickLength,
                TickColor);
            SetValue(ImageSourcePropertyKey, colorMapImage);
        }

        private SciColorMap cmap_;
    }
}


// References
// [Setting a range of possible values of a dependency property](https://stackoverflow.com/questions/25643185/setting-a-range-of-possible-values-of-a-dependency-property)
// [Read-only dependency properties (WPF .NET)](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/properties/read-only-dependency-properties?view=netdesktop-6.0)
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationFramework/System/Windows/Controls/ContentControl.cs HasContent
// [Loaded event of a WPF user control fires more than once](https://stackoverflow.com/questions/3421303/loaded-event-of-a-wpf-user-control-fires-more-than-once)
// [What event is fired when a UserControl is displayed?](https://stackoverflow.com/questions/4708039/what-event-is-fired-when-a-usercontrol-is-displayed)
// [SizeChanged Event Isn't Firing](https://stackoverflow.com/questions/50822715/sizechanged-event-isnt-firing)
// https://github.com/ScottPlot/ScottPlot/blob/main/src/ScottPlot4/ScottPlot/Drawing/Colormap.cs
// https://github.com/marcomusy/vedo/blob/master/examples/notebooks/sphere.ipynb
// https://matplotlib.org/stable/gallery/color/colormap_reference.html
// > Qualitative colormaps
// [Matplotlib 系列：colormap 的设置](https://zhajiman.github.io/post/matplotlib_colormap/)
// [Reverse colormap in matplotlib](https://stackoverflow.com/questions/3279560/reverse-colormap-in-matplotlib)
// > The standard colormaps also all have reversed versions. They have the same names with _r tacked on to the end. (Documentation here.)
// https://github.com/helix-toolkit/helix-toolkit/blob/develop/Source/HelixToolkit.Wpf.Shared/Controls/ColorAxis/ColorAxis.cs
