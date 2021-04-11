namespace MarshalCppClass
{
    using System;
    using System.Runtime.InteropServices;

    class Person : IDisposable
    {
        //public Person()
        //{
        //    person_ = PersonNatives.New();
        //}

        // NOTE: Leave out the finalizer altogether if this class doesn't
        // own unmanaged resources, but leave the other methods
        // exactly as they are.
        ~Person()
        {
            // Finalizer calls Dispose(false)
            Dispose(false);
        }

        public string Name
        {
            get
            {
                var name = PersonNatives.GetName(person_);
                return Marshal.PtrToStringAnsi(name);
            }

            set
            {
                if (value != null)
                    PersonNatives.SetName(person_, value);
            }
        }

        public int Age
        {
            get
            {
                return PersonNatives.GetAge(person_);
            }

            set
            {
                PersonNatives.SetAge(person_, value);
            }
        }

        public void Say(string what) => PersonNatives.Say(person_, what);

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                // Free managed resources
                // ...
            }

            // Free native resources if there are any.
            PersonNatives.Delete(person_);

            disposed_ = true;
        }

        private IntPtr person_ = PersonNatives.New();
        private bool disposed_ = false;
    }
}


// References:
// [CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)
