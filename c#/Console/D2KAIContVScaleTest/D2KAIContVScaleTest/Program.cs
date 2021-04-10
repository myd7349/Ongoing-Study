namespace D2KAIContVScaleTest
{
    using System;

    using Common;

    class Program
    {
        static int Main(string[] args)
        {
            var rawAdData = new short[short.MaxValue - short.MinValue];
            for (short i = short.MinValue; i < short.MaxValue; ++i)
                rawAdData[i - short.MinValue] = i;

            var voltage = new double[rawAdData.Length];

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

            // Output: 305.17578125
            // It is about ADRange / (short.MaxValue + 1) * 1e6.
            for (int i = 0; i < voltage.Length; ++i)
                Console.WriteLine("{0}", DoubleConverter.ToExactString(voltage[i] / rawAdData[i] * 1e6));

            var scale = 10.0 / (short.MaxValue + 1);

            var rawAdData2 = new short[]
            {
                -32767, -32766, -10000,
                -1000, -2000, -3000,
                -1, -2, -3,
                1, 2, 3,
                1000, 2000, 3000,
                32767, 32766, 10000,
            };
            var voltage2 = new double[rawAdData2.Length];

            res = D2KDASK.D2K_AI_ContVScale(cardNumber, D2KDASK.AD_B_10_V,
                rawAdData2, voltage2, voltage2.Length);
            if (res != D2KDASK.NoError)
            {
                Console.Error.WriteLine("D2K_AI_ContVScale failed: {0}.", res);
                D2KDASK.D2K_Release_Card(cardNumber);
                return 1;
            }

            for (int i = 0; i < rawAdData2.Length; ++i)
            {
                Console.WriteLine("{0} {1} {2}",
                    rawAdData2[i],
                    DoubleConverter.ToExactString(voltage2[i]),
                    DoubleConverter.ToExactString(rawAdData2[i] * scale));
            }

            D2KDASK.D2K_Release_Card(cardNumber);

            Util.Pause();

            return 0;
        }
    }
}


// References:
// NuDAQ-2213,2214 User's Guide.pdf: Ch4.1.1 DAQ-2213/2214 AI Data Format
// [Formatting doubles for output in C#](https://stackoverflow.com/questions/1421520/formatting-doubles-for-output-in-c-sharp)
// [Analog-Digital converter's LSB formula](https://electronics.stackexchange.com/questions/258490/analog-digital-converters-lsb-formula)
// [What does it mean when we say an A/D converter has 1 LSB accuracy?](https://electronics.stackexchange.com/questions/192092/what-does-it-mean-when-we-say-an-a-d-converter-has-1-lsb-accuracy)
