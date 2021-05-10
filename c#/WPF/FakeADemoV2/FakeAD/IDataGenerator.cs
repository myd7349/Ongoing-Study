namespace FakeAD
{
    interface IDataGenerator
    {
        int Samples { get; }

        double Next();
    }
}

// References:
// [Simple Signal Generator](https://www.codeproject.com/Articles/30180/Simple-Signal-Generator)
