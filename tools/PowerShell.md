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