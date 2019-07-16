<Query Kind="Program">
  <Namespace>System.Net</Namespace>
  <Namespace>System.Net.Sockets</Namespace>
</Query>

void Main()
{
    const int PortNumber = 12345;
    var addressList = Dns.GetHostEntry("localhost").AddressList;
    var address1 = new IPEndPoint(addressList[1], PortNumber).Address;

    var address2 = new IPAddress(new byte[] { 127, 0, 0, 1 });

    var address3 = IPAddress.Parse("127.0.0.1");

    Console.WriteLine(address1);
    Console.WriteLine(address2);
    Console.WriteLine(address3);
    Console.WriteLine("address1 == address2? {0}", address1 == address2);
    Console.WriteLine("address1.Equals(address3)? {0}", address1.Equals(address3));
}

// References:
// https://stackoverflow.com/questions/1016471/how-to-compare-ip-addresses
// https://stackoverflow.com/questions/14021710/strange-net-behavior-on-ipaddress-equals
// https://stackoverflow.com/questions/2722598/compare-two-ip-with-c-sharp
