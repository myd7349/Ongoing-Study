// MEF example
namespace SimpleCalculator
{
    using System;
    using System.ComponentModel.Composition;
    using System.ComponentModel.Composition.Hosting;
    using System.IO;
    using System.Reflection;
    
    class Program
    {
        static void Main(string[] args)
        {
            var program = new Program();

            Console.WriteLine("Enter command: ");

            while (true)
            {
                var input = Console.ReadLine();
                Console.WriteLine(program.calculator_.Calculate(input));
            }
        }

        private Program()
        {
            // An aggregate catalog that combines multiple catalogs
            var catalog = new AggregateCatalog();
            // Add all the parts found in the same assembly as the Program class
            catalog.Catalogs.Add(new AssemblyCatalog(typeof(Program).Assembly));
            // Add a directory catalog
            catalog.Catalogs.Add(
                new DirectoryCatalog(
                    Path.GetDirectoryName(Assembly.GetEntryAssembly().Location)
                    ));

            // Create the container with the parts in the catalog
            container_ = new CompositionContainer(catalog);

            // Fill the imports of this object
            try
            {
                container_.ComposeParts(this);
            }
            catch (CompositionException ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        private CompositionContainer container_;

#pragma warning disable 0649
        [Import(typeof(ICalculator))]
        public ICalculator calculator_;
#pragma warning restore 0649
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/framework/mef/index
// https://www.cnblogs.com/pszw/archive/2011/11/27/MEF.html
// https://stackoverflow.com/questions/13726743/disable-suppress-warning-cs0649-in-c-sharp-for-a-specific-field-of-class
// https://stackoverflow.com/questions/1876064/mef-what-if-i-have-multiple-exports-but-need-only-one-import
// https://blogs.msdn.microsoft.com/dsplaisted/2009/08/10/import-cardinality-and-picking-which-export-to-use/
