namespace SimpleCalculator
{
    using System.ComponentModel.Composition;

    using CalculatorOperation;

    [Export(typeof(IOperation))]
    [ExportMetadata("Symbol", '-')]
    class Subtract : IOperation
    {
        public int Operate(int left, int right)
        {
            return left - right;
        }
    }
}
