using System.Collections.Generic;
using System.Windows.Media;
using System.Windows.Shapes;

using MvvmHelpers;
using MvvmHelpers.Commands;
using SciColorMap = SciColorMaps.Portable.ColorMap;

using ColorMap.WPF;

namespace ColorMap.Demo
{
    
    class MainWindowViewModel : ObservableObject
    {
        public MainWindowViewModel()
        {
            ColorPalettes = SciColorMap.Palettes;

            //SelectedColorPalette = "viridis";
            
            CreateColorMapBrush();
        }

        public IEnumerable<string> ColorPalettes { get; }

        public string? SelectedColorPalette
        {
            get => selectedColorPalette_;

            set
            {
                if (SetProperty(ref selectedColorPalette_, value))
                {
                    CreateColorMapBrush();
                    CreateColorMapBrush2();
                    CreateDrawingImage();
                }
            }
        }

        public int ColorCount
        {
            get => colorCount_;

            set
            {
                if (SetProperty(ref colorCount_, value))
                {
                    CreateColorMapBrush();
                    CreateColorMapBrush2();
                    CreateDrawingImage();
                }
            }
        }
        
        public Brush? ColorMapBrush
        {
            get => colorMapBrush_;
            set => SetProperty(ref colorMapBrush_, value);
        }

        public Brush? ColorMapBrush2
        {
            get => colorMapBrush2_;
            set => SetProperty(ref colorMapBrush2_, value);
        }

        public Command UpdateSizeCommand =>
            updateSizeCommand_ ??
            (updateSizeCommand_ = new Command<Rectangle>(UpdateSize));

        public double Width
        {
            get => width_;
            
            set
            {
                if (SetProperty(ref width_, value))
                    CreateColorMapBrush2();
            }
        }

        public double Height
        {
            get => height_;
            
            set
            {
                if (SetProperty(ref height_, value))
                    CreateColorMapBrush2();
            }
        }

        public DrawingImage DrawingImage
        {
            get => drawingImage_;
            set => SetProperty(ref drawingImage_, value);
        }

        private void UpdateSize(Rectangle rectangle)
        {
            Width = rectangle.ActualWidth;
            Height = rectangle.ActualHeight;
        }
        
        private void CreateColorMapBrush()
        {            
            ColorMapBrush = SciColorMapHelper.CreatePaletteBrush(
                SelectedColorPalette, ColorCount);
        }

        private void CreateColorMapBrush2()
        {
            ColorMapBrush2 = SciColorMapHelper.CreatePaletteBrush(
                selectedColorPalette_, colorCount_, width_, height_);
        }

        private void CreateDrawingImage()
        {
            DrawingImage = SciColorMapHelper.CreateDrawingImage(
                selectedColorPalette_, colorCount_);
        }

        private string? selectedColorPalette_;
        private int colorCount_ = 256;
        private Brush? colorMapBrush_;
        private Brush? colorMapBrush2_;
        private Command? updateSizeCommand_;
        private double width_;
        private double height_;
        private DrawingImage drawingImage_;
    }
}
