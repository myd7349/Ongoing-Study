namespace SimpleCalculator
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.Composition;
    using System.Text.RegularExpressions;

    using CalculatorOperation;

    [Export(typeof(ICalculator))]
    class MySimpleCalculator : ICalculator
    {
        public string Calculate(string input)
        {
            if (!ParseInput(input, out int left, out char operation, out int right))
                return "Could not parse command.";

            foreach (var i in operations_)
            {
                if (i.Metadata.Symbol.Equals(operation))
                    return i.Value.Operate(left, right).ToString();
            }

            return "Operation not found.";
        }

        private bool ParseInput(string s, out int left, out char operation, out int right)
        {
            var matchResult = regex_.Match(s);
            if (matchResult.Success)
            {
                left = int.Parse(matchResult.Groups[1].Value);
                operation = matchResult.Groups[2].Value[0];
                right = int.Parse(matchResult.Groups[3].Value);

                return true;
            }
            else
            {
                left = right = 0;
                operation = ' ';

                return false;
            }
        }

#pragma warning disable 0649
        [ImportMany]
        private IEnumerable<Lazy<IOperation, IOperationData>> operations_;
#pragma warning restore 0649

        private Regex regex_ = new Regex(@"^\s*([0-9]+)\s*([^0-9 ])\s*([0-9]+)\s*$");
    }
}
