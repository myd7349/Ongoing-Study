##### partial class

[Access class fields from partial class](https://stackoverflow.com/questions/4132984/access-class-fields-from-partial-class)

[Partial classes in separate dlls](https://stackoverflow.com/questions/3858649/partial-classes-in-separate-dlls)

```csharp
// partial class defined in dll A
public static partial class MyMath
{
    public const int PI = 3.14;
}

// partial class defined in dll B
public static partial class MyMath
{
    public static double Sin()
    {
        // Can not access PI here
    }
}
```

##### class with same name in different namespace

```csharp
// ImageProcessing.dll
namespace ImageProcessing
{
    public static class ImageHelper
    {
        public static void Blur(this Image image, double factor)
        {
        }
    }
}

// ImageUtilities.dll
namespace ImageUtilities
{
    public static class ImageHelper
    {
        public static void GetWidth(this Image image)
        {
        }
    }
}

// App
using ImageProcessing;
using ImageUtilities;

var image = new Image(...);
image.Blur(0.5);
image.GetWidth();
```

##### [Multiple Inheritance in C#](https://stackoverflow.com/questions/178333/multiple-inheritance-in-c-sharp)

Consider just using *[composition](http://en.wikipedia.org/wiki/Object_composition)* instead of trying to simulate Multiple Inheritance. You can use Interfaces to define what classes make up the composition.
