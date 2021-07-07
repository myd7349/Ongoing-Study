namespace MetafileTool
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.IO;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("MetafileTool - Convert Windows metafile into image file and vice verca.");
                Console.WriteLine("Usage:\n\tMetafileTool <input file> <output file>");
                return;
            }

            switch (Path.GetExtension(args[0]).ToLower())
            {
                case ".emf":
                case ".wmf":
                    using (var metafile = new Metafile(args[0]))
                    using (var bitmap = MetafileUtility.MetafileToBitmap(metafile))
                        bitmap.Save(args[1]);
                    break;
                default:
                    using (var bitmap = new Bitmap(args[0]))
                    using (var metafileStream = MetafileUtility.BitmapToMetafileMemoryStream(bitmap))
                    using (var targetStream = File.Create(args[1]))
                        metafileStream.WriteTo(targetStream);
                    break;
            }
        }
    }
}
