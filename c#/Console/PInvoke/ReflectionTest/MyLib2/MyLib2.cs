namespace MyLib2
{
    using System.Linq;

    using MyLibBase;

    public class MyLib2 : MyLibBase
    {
        public MyLib2(string message)
        {
            message_ = message;
        }

        public override string Message => string.Join("", message_.Reverse());

        public override string Name => nameof(MyLib2);

        private readonly string message_;
    }
}
