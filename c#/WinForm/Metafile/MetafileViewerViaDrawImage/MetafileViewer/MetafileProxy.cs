namespace MetafileViewer
{
    using System.Drawing.Imaging;

    public class MetafileProxy
    {
        public MetafileProxy(Metafile metafile)
        {
            Metafile = metafile;
        }

        public Metafile Metafile
        {
            get
            {
                return metafile_;
            }

            set
            {
                metafile_ = value;
            }
        }

        private Metafile metafile_;
    }
}


// References:
// [How can I create a reference member variable in C# like in C++](https://stackoverflow.com/questions/44291364/how-can-i-create-a-reference-member-variable-in-c-sharp-like-in-c)
// [C# reference member variable](https://stackoverflow.com/questions/6253551/c-sharp-reference-member-variable)
