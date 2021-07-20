namespace GraphicsTransformDemo
{
    public struct Settings
    {
        public Settings(int x = 0, int y = 0, int w = 120, int h = 80, int a = 0)
        {
            X = x;
            Y = y;
            Width = w;
            Height = h;
            Angle = a;
        }

        public int X;
        public int Y;
        public int Width;
        public int Height;
        public int Angle;
    }
}
