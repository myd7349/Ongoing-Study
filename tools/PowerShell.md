[Capturing standard out and error with Start-Process](https://stackoverflow.com/questions/8761888/capturing-standard-out-and-error-with-start-process)

[How do I capture the output into a variable from an external process in PowerShell?](https://stackoverflow.com/questions/8097354/how-do-i-capture-the-output-into-a-variable-from-an-external-process-in-powershe)

[Difference between $? and $LastExitCode in PowerShell](https://stackoverflow.com/questions/10666035/difference-between-and-lastexitcode-in-powershell)

[Capture program stdout and stderr to separate variables](https://stackoverflow.com/questions/24222088/capture-program-stdout-and-stderr-to-separate-variables)

[How to capture output in a variable rather than a logfile?](https://stackoverflow.com/questions/8423368/how-to-capture-output-in-a-variable-rather-than-a-logfile)

[Obtaining ExitCode using Start-Process and WaitForExit instead of -Wait](https://stackoverflow.com/questions/10262231/obtaining-exitcode-using-start-process-and-waitforexit-instead-of-wait)

```powershell
function getLastCommitHash()
{
    try
    {
        $processStartInfo = New-Object System.Diagnostics.ProcessStartInfo
        $processStartInfo.RedirectStandardError = $true
        $processStartInfo.RedirectStandardOutput = $true
        $processStartInfo.UseShellExecute = $false
        $processStartInfo.Arguments = "git rev-parse --short HEAD"
        $processStartInfo.CreateNoWindow = $true

        $process = New-Object System.Diagnostics.Process
        $process.Start($processStartInfo) | Out-Null

        $lastCommitHash = $process.StandardOutput.ReadToEnd()
        $stderr = $process.StandardError.ReadToEnd()
        $ec = $process.ExitCode

        $process.WaitForExit()

        if ($ec -ne 0)
        {
            Write-Verbose "Failed to get last commit hash($ec): $stderr"
            return "unknownhash"
        }
        else
        {
            return $lastCommitHash
        }
    }
    catch [System.Management.Automation.CommandNotFoundException]
    {
        return "unknownhash"
    }
}
```

[touch](https://stackoverflow.com/questions/51841259/touch-function-in-powershell)

```powershell
echo $null > .gitkeep
```

[Use PowerShell to Set Environment Variables](https://www.tachytelic.net/2019/03/powershell-environment-variables/)

```
$env:HTTP_PROXY='127.0.0.1:7079'
Get-ChildItem Env:HTTP_PROXY
```

[batch menu outlines and design](https://stackoverflow.com/questions/34977487/batch-menu-outlines-and-design)

```
$ iwr https://deno.land/x/install/install.ps1 -useb | iex
$ Get-Alias -Definition Invoke-WebRequest | Format-Table -AutoSize
$ Get-Alias -Definition Invoke-Expression
```

> Set-ExecutionPolicy RemoteSigned

https://github.com/RehanSaeed/Windows

https://github.com/JanDeDobbeleer/oh-my-posh

https://github.com/star2000/BingWallpaper

[PowerRemoteDesktop](https://github.com/DarkCoderSc/PowerRemoteDesktop): Remote Desktop entirely coded in PowerShell.

[PowerRunAsAttached](https://github.com/DarkCoderSc/PowerRunAsAttached): This script allows to spawn a new interactive console as another user account in the same calling console (console instance/window).

[PowerAssembly](https://github.com/DarkCoderSc/PowerAssembly): Map remote .NET assemblies to memory for further invocation.

[PowerShell's Clear-History doesn't clear history](https://stackoverflow.com/questions/13257775/powershells-clear-history-doesnt-clear-history)

> ```scss
> (Get-PSReadlineOption).HistorySavePath
> ```

[Use PowerShell and WMI to Get Processor Information](https://devblogs.microsoft.com/scripting/use-powershell-and-wmi-to-get-processor-information/)

```
Get-WmiObject Win32_Processor
Get-WmiObject -class win32_processor -Property ProcessorId
```

[ConvertTo-Jpeg](https://github.com/DavidAnson/ConvertTo-Jpeg)

[PowerShell redirect input from file](https://cloud.tencent.com/developer/ask/sof/63560)

> Get-Content input.txt | ./program > output.txt

https://github.com/nodejs/node/blob/master/deps/corepack/shims/npm.ps1

[oh-my-posh](https://github.com/JanDeDobbeleer/oh-my-posh)

[posh-git](https://github.com/dahlbyk/posh-git)

Modules

- [ImportExcel](https://github.com/dfinke/ImportExcel)

- [NameIT](https://github.com/dfinke/NameIT)

- [PowerShellHumanizer](https://github.com/dfinke/PowerShellHumanizer)

- [PSFuzzySearch](https://github.com/dfinke/PSFuzzySearch)

Others

- [PoShLucene](https://github.com/dfinke/PoShLucene)

- [powershell-algorithms](https://github.com/dfinke/powershell-algorithms)

- [PowerShellNotebook](https://github.com/dfinke/PowerShellNotebook)

- [Tiny-PowerShell-Projects](https://github.com/dfinke/Tiny-PowerShell-Projects)

- https://github.com/sailay1996/SpoolTrigger

- https://github.com/Yamato-Security/WELA

- https://github.com/sorayuki/srt_build_win32

https://github.com/bitwarden/server

> ```powershell
> Invoke-RestMethod -OutFile bitwarden.ps1 `
>     -Uri https://raw.githubusercontent.com/bitwarden/server/master/scripts/bitwarden.ps1
> ```

https://www.powershellgallery.com/

[Command line reference.](https://ss64.com/)

[Fido](https://github.com/pbatard/Fido)
