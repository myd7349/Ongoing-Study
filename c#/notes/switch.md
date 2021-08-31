1. [H5Dataset](https://github.com/Apollo3zehn/HDF5.NET/blob/412caaf6e2e794a4a058b9dc1f65ace8e061fabf/src/HDF5.NET/Core/H5Dataset.cs#L142-L179)

   > ```c#
   > using H5D_Base bufferProvider = this.InternalDataLayout.LayoutClass switch
   > {
   >     LayoutClass.Compact => new H5D_Compact(this, datasetAccess),
   >     LayoutClass.Contiguous => new H5D_Contiguous(this, datasetAccess),
   >     LayoutClass.Chunked => H5D_Chunk.Create(this, datasetAccess),
   >     LayoutClass.VirtualStorage => throw new NotImplementedException(),
   >     _ => throw new Exception($"The data layout class '{this.InternalDataLayout.LayoutClass}' is not supported.")
   > };
   > ```

   [GoodEnough.Biology](https://github.com/GoodEnoughIndustries/Biology) also uses this C# 8.0 new feature: [SixLabors.ImageSharp is awesome btw, especially with C# 6](https://twitter.com/ChadJessup/status/1411240851385188358).
   
   [switch expression (C# reference)](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/switch-expression)
   
   ```csharp
   public static class SwitchExample
   {
       public enum Direction
       {
           Up,
           Down,
           Right,
           Left
       }
   
       public enum Orientation
       {
           North,
           South,
           East,
           West
       }
   
       public static Orientation ToOrientation(Direction direction) => direction switch
       {
           Direction.Up    => Orientation.North,
           Direction.Right => Orientation.East,
           Direction.Down  => Orientation.South,
           Direction.Left  => Orientation.West,
           _ => throw new ArgumentOutOfRangeException(nameof(direction), $"Not expected direction value: {direction}"),
       };
   
       public static void Main()
       {
           var direction = Direction.Right;
           Console.WriteLine($"Map view direction is {direction}");
           Console.WriteLine($"Cardinal orientation is {ToOrientation(direction)}");
           // Output:
           // Map view direction is Right
           // Cardinal orientation is East
       }
   }
   ```
   
2. https://github.com/EasyNetQ/EasyNetQ/blob/develop/Source/EasyNetQ/Internals/ReadOnlyMemoryStream.cs

   > ```csharp
   > public override long Seek(long offset, SeekOrigin origin)
   > {
   >     var newPosition = origin switch
   >     {
   >         SeekOrigin.Begin => offset,
   >         SeekOrigin.Current => position + offset,
   >         SeekOrigin.End => content.Length + offset,
   >         _ => throw new ArgumentOutOfRangeException(nameof(origin))
   >     };
   > 
   >     if (newPosition > int.MaxValue || newPosition < 0)
   >         throw new ArgumentOutOfRangeException(nameof(offset));
   > 
   >     position = (int)newPosition;
   >     return position;
   > }
   > ```

   

