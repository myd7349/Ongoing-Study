using System;
using System.Runtime.InteropServices;

public class D2KDASK
{
	public const ushort DAQ_2213 = 10;
	public const short NoError = 0;
	public const ushort AD_B_10_V = 1;

	[DllImport("D2K-Dask.dll")]
	public static extern short D2K_Register_Card (ushort CardType, ushort card_num);
	[DllImport("D2K-Dask.dll")]
	public static extern short D2K_Release_Card  (ushort CardNumber);
	[DllImport("D2K-Dask.dll")]
	public static extern short D2K_AI_ContVScale (ushort wCardNumber, ushort adRange, short[] readingArray, double[] voltageArray, int count);
}
