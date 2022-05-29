https://github.com/BornToBeRoot/NETworkManager/blob/main/Source/NETworkManager.Models/Network/DiscoveryProtocol.cs

```csharp
using (System.Management.Automation.PowerShell powerShell = System.Management.Automation.PowerShell.Create())
{
    powerShell.AddScript("Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process");
    powerShell.AddScript("Import-Module NetAdapter");
    powerShell.AddScript(PSDiscoveryProtocolModule);
    powerShell.AddScript($"Invoke-DiscoveryProtocolCapture -Duration {duration}" + (protocol != Protocol.LLDP_CDP ? $" -Type {protocol}" : "") + " -Force | Get-DiscoveryProtocolData");
    
    Collection<PSObject> PSOutput = powerShell.Invoke();
}
```
