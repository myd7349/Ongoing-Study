namespace D2KAIContVScaleTest
{
    using System;

    class Program
    {
        static int Main(string[] args)
        {
            var res = D2KDASK.D2K_Register_Card(D2KDASK.DAQ_2213, 0);
            if (res < 0)
            {
                Console.Error.WriteLine("Failed to register card.");
                return 1;
            }

            ushort cardNumber = (ushort)res;
            
            const int Channels = 2;
            var channels = new ushort[Channels];
            var ranges = new ushort[Channels];

            for (int i = 0; i < Channels; ++i)
            {
                channels[i] = (ushort)i;
                ranges[i] = D2KDASK.AD_B_10_V;
            }

            var rawAdData = new short[short.MaxValue];
            for (short i = 0; i < short.MaxValue; ++i)
                rawAdData[i] = (short)(i + 1);

            var voltage = new double[rawAdData.Length];

            // Is it possible to call this function like this?
            // D2KDASK.D2K_AI_ContVScale(D2KDASK.AD_B_10_V, rawAdData, voltage, voltage.Length);
            // Why is card number necessary for such a simple function?
            res = D2KDASK.D2K_AI_ContVScale(cardNumber, D2KDASK.AD_B_10_V,
                rawAdData, voltage, voltage.Length);
            if (res != D2KDASK.NoError)
            {
                Console.Error.WriteLine("D2K_AI_ContVScale failed: {0}.", res);
                D2KDASK.D2K_Release_Card(cardNumber);
                return 1;
            }

            // It is about ADRange / short.MaxValue * 1e6.
            for (int i = 0; i < voltage.Length; ++i)
                Console.WriteLine("{0}", voltage[i] / rawAdData[i] * 1e6);

            D2KDASK.D2K_Release_Card(cardNumber);

            return 0;
        }
    }
}


// References:
// NuDAQ-2213,2214 User's Guide.pdf: Ch4.1.1 DAQ-2213/2214 AI Data Format
