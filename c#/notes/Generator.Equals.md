```csharp
using Generator.Equals;

[Equatable]
public partial class Class1
{
    public string A1;

    public string A2;
}
```

Not work!

So let us declare Class1 in a namespace:

```csharp
using Generator.Equals;

namespace Test;

[Equatable]
public partial class Class1
{
    public string A1;

    public string A2;
}
```

Generated code:

```csharp
// Test.Class1
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using Test;

public class Class1 : IEquatable<Class1>
{
	public string A1;

	public string A2;

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator ==(Class1? left, Class1? right)
	{
		return EqualityComparer<Class1>.Default.Equals(left, right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator !=(Class1? left, Class1? right)
	{
		return !(left == right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override bool Equals(object? obj)
	{
		return Equals(obj as Class1);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public bool Equals(Class1? other)
	{
		return (object)other != null && GetType() == other!.GetType();
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override int GetHashCode()
	{
		HashCode hashCode = default(HashCode);
		hashCode.Add(GetType());
		return hashCode.ToHashCode();
	}
}
```

Apparently not what we want.

```csharp
using Generator.Equals;

namespace Test;

[Equatable]
public partial class Class1
{
    public string A1 { get; set; }

    public string A2 { get; set; }
}
```

Generated code:

```csharp
// Test.Class1
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using Test;

public class Class1 : IEquatable<Class1>
{
	public string A1 { get; set; }

	public string A2 { get; set; }

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator ==(Class1? left, Class1? right)
	{
		return EqualityComparer<Class1>.Default.Equals(left, right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator !=(Class1? left, Class1? right)
	{
		return !(left == right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override bool Equals(object? obj)
	{
		return Equals(obj as Class1);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public bool Equals(Class1? other)
	{
		return (object)other != null && GetType() == other!.GetType() && EqualityComparer<string>.Default.Equals(A1, other!.A1) && EqualityComparer<string>.Default.Equals(A2, other!.A2);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override int GetHashCode()
	{
		HashCode hashCode = default(HashCode);
		hashCode.Add(GetType());
		hashCode.Add(A1, EqualityComparer<string>.Default);
		hashCode.Add(A2, EqualityComparer<string>.Default);
		return hashCode.ToHashCode();
	}
}
```

Another example:

```csharp
using CommunityToolkit.Mvvm.ComponentModel;
using Generator.Equals;

namespace Test;

[Equatable(IgnoreInheritedMembers = true)]
public partial class Class1 : ObservableObject
{
    [ObservableProperty]
    private string? a1;

    [ObservableProperty]
    private string? a2;
}
```

Generated code:

```csharp
// Test.Class1
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.ComponentModel.__Internals;
using Test;

public class Class1 : ObservableObject, IEquatable<Class1>
{
	[ObservableProperty]
	private string? a1;

	[ObservableProperty]
	private string? a2;

	[GeneratedCode("CommunityToolkit.Mvvm.SourceGenerators.ObservablePropertyGenerator", "8.0.0.0")]
	[ExcludeFromCodeCoverage]
	public string? A1
	{
		get
		{
			return a1;
		}
		set
		{
			if (!EqualityComparer<string>.Default.Equals(a1, value))
			{
				OnPropertyChanging(__KnownINotifyPropertyChangingArgs.A1);
				a1 = value;
				OnPropertyChanged(__KnownINotifyPropertyChangedArgs.A1);
			}
		}
	}

	[GeneratedCode("CommunityToolkit.Mvvm.SourceGenerators.ObservablePropertyGenerator", "8.0.0.0")]
	[ExcludeFromCodeCoverage]
	public string? A2
	{
		get
		{
			return a2;
		}
		set
		{
			if (!EqualityComparer<string>.Default.Equals(a2, value))
			{
				OnPropertyChanging(__KnownINotifyPropertyChangingArgs.A2);
				a2 = value;
				OnPropertyChanged(__KnownINotifyPropertyChangedArgs.A2);
			}
		}
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator ==(Class1? left, Class1? right)
	{
		return EqualityComparer<Class1>.Default.Equals(left, right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public static bool operator !=(Class1? left, Class1? right)
	{
		return !(left == right);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override bool Equals(object? obj)
	{
		return Equals(obj as Class1);
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public bool Equals(Class1? other)
	{
		return (object)other != null && GetType() == other!.GetType();
	}

	[GeneratedCode("Generator.Equals", "1.0.0.0")]
	public override int GetHashCode()
	{
		HashCode hashCode = default(HashCode);
		hashCode.Add(GetType());
		return hashCode.ToHashCode();
	}
}
```

```csharp
using CommunityToolkit.Mvvm.ComponentModel;
using Generator.Equals;

namespace Test;

[Equatable(Explicit = true)]
public partial class Class1 : ObservableObject
{
    [ObservableProperty]
    [DefaultEquality]
    private string? a1;

    [ObservableProperty]
    [DefaultEquality]
    private string? a2;
}
```

won't work.
