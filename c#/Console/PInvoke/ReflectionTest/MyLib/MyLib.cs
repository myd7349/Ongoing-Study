namespace MyLib
{
    using MyLibBase;

    public class MyLib : MyLibBase
    {
        public MyLib(string message)
        {
            message_ = message;
        }

        public override string Message
        {
            get
            {
                return message_;
            }
        }

        public override string Name => nameof(MyLib);

        private readonly string message_;
    }
}
