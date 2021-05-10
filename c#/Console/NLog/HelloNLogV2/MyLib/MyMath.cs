namespace MyLib
{
    using System;

    using NLog;

    public class MyMath
    {
        private static Logger Log = LogManager.GetCurrentClassLogger();

        public static double Sin(double x)
        {
            try
            {
                Log.Info("Calling Math.Sin with input: {0}", x);

                var result = Math.Sin(x);

                Log.Info("Sin({0}) = {1}", x, result);

                return result;
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Failed to call Math.Sin.");
                throw;
            }
        }
    }
}
