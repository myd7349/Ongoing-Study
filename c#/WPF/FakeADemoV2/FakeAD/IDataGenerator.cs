namespace FakeAD
{
    interface IDataGenerator
    {
        int Samples { get; }

        double Next();
    }
}
