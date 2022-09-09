using System.Windows;

using SciColorMap = SciColorMaps.Portable.ColorMap;

namespace ColorMap.WPF
{
    public class ColorMapChangedEventArgs : RoutedEventArgs
    {
        public ColorMapChangedEventArgs(SciColorMap cmap, bool isQualitative, bool isReversed)
        {
            ColorMap = cmap;
            IsQualitative = isQualitative;
            IsReversed = isReversed;
        }

        public ColorMapChangedEventArgs(SciColorMap cmap, bool isQualitative, bool isReversed, RoutedEvent routedEvent)
            : base(routedEvent)
        {
            ColorMap = cmap;
            IsQualitative = isQualitative;
            IsReversed = isReversed;
        }

        public ColorMapChangedEventArgs(SciColorMap cmap, bool isQualitative, bool isReversed, RoutedEvent routedEvent, object source)
            : base(routedEvent, source)
        {
            ColorMap = cmap;
            IsQualitative = isQualitative;
            IsReversed = isReversed;
        }

        public SciColorMap ColorMap { get; }

        public bool IsQualitative { get; }
        
        public bool IsReversed { get; }
    }
}
