# Usage:
# GetVersion.ps1 -Template cpp -VersionSource VERSION.txt -OutputFile GitVersion.h
# GetVersion.ps1 -Template dotnetframework -VersionSource 1.2.3 -OutputFile AssemblyInfo.githash.cs
# GetVersion.ps1 -Template dotnet -VersionSource 1.2.3 -OutputFile Directory.Build.props -TargetFramework netcoreapp3.1

[CmdletBinding()]
Param(
    [Parameter(Mandatory=$False)]
    [string]
    $Template = "",

    [Parameter(Mandatory=$False)]
    [string]
    $TargetFramework = "",

    [Parameter(Mandatory=$False)]
    [string]
    $VersionSource = "",

    # Input version file encoding
    [Parameter(Mandatory=$False)]
    [string]
    $Encoding = "",

    [Parameter(Mandatory=$False)]
    [string]
    $OutputFile = ""
)


function GetLastCommitHash()
{
    try
    {
        $output = git rev-parse --short HEAD

        if ($LastExitCode -eq 0)
        {
            return $output
        }
        else
        {
            Write-Warning "Failed to get last commit hash, exit code $LastExitCode."
            return "rev-unknown"
        }
    }
    catch [System.Management.Automation.CommandNotFoundException]
    {
        Write-Warning "Failed to get last commit hash, git not found."
        return "rev-unknown"
    }
}


if (-not [string]::IsNullOrWhiteSpace($Template) -and
    !($Template -eq "cpp") -and
    !($Template -eq "dotnetframework") -and
    !($Template -eq "dotnet"))
{
    throw "Parameter ""-Template"" only accepts cpp/dotnetframework/dotnet."
}

$fileVersion = ""

if (-not [string]::IsNullOrWhiteSpace($VersionSource))
{
    if (Test-Path $VersionSource)
    {
        if (-not [string]::IsNullOrWhiteSpace($Encoding))
        {
            $fileVersion = Get-Content -Path $VersionSource -Encoding $Encoding -TotalCount 1
        }
        else
        {
            $fileVersion = Get-Content -Path $VersionSource -TotalCount 1
        }

        Write-Verbose "File version read from $VersionSource`: $fileVersion"
    }
    else
    {
        $fileVersion = $VersionSource
        Write-Verbose "File version: $fileVersion"
    }

    if (-not [string]::IsNullOrWhiteSpace($fileVersion) -and
        !($fileVersion -match "^([0-9]+(?:.[0-9]+){1,3})$"))
    {
        throw "Invalid version number: $fileVersion."
    }
}


$lastCommitHash = GetLastCommitHash
Write-Verbose "Last commit SHA-1: $lastCommitHash"

$builtDateTime = Get-Date -Format "yyyy-MM-ddTHH:mm:ss.fffzzz"
Write-Verbose "Current time: $builtDateTime"


$output = ""

if ($Template -eq "cpp")
{
    $output = "#define PRODUCT_VERSION ""{0}({1})""`n" -f $lastCommitHash, $builtDateTime

    if (-not [string]::IsNullOrWhiteSpace($fileVersion))
    {
        $fileVersionCommaSeperated = $fileVersion.Replace('.', ',')

        $output += "#define FILE_VERSION ""$fileVersion""`n"
        $output += "#define FILE_VERSION_COMMA_SEPERATED $fileVersionCommaSeperated`n"
    }
}
elseif ($Template -eq "dotnetframework")
{
    $output = "using System.Reflection;`n`n"
    $output += "[assembly: AssemblyInformationalVersion(""$lastCommitHash($builtDateTime)"")]`n"

    if (-not [string]::IsNullOrWhiteSpace($fileVersion))
    {
        $output += "[assembly: AssemblyVersion(""$fileVersion"")]`n"
        $output += "[assembly: AssemblyFileVersion(""$fileVersion"")]`n"
    }
}
elseif ($Template -eq "dotnet")
{
    if (-not [string]::IsNullOrWhiteSpace($fileVersion))
    {
        $output = @"
<Project>

  <PropertyGroup>
    <TargetFramework>{0}</TargetFramework>
    <Version>{1}</Version>
    <InformationalVersion>{2}({3})</InformationalVersion>
  </PropertyGroup>

</Project>
"@ -f $TargetFramework, $fileVersion, $lastCommitHash, $builtDateTime
    }
    else
    {
        $output = @"
<Project>

  <PropertyGroup>
    <TargetFramework>{0}</TargetFramework>
    <InformationalVersion>{2}({3})</InformationalVersion>
  </PropertyGroup>

</Project>
"@ -f $TargetFramework, $lastCommitHash, $builtDateTime
    }
}


if ([string]::IsNullOrWhiteSpace($OutputFile))
{
    Write-Host $output
}
else
{
    #$output | Out-File -FilePath $OutputFile -Encoding ASCII
    Out-File -FilePath $OutputFile -Encoding ASCII -InputObject $output
}


# References:
# https://github.com/microsoft/vcpkg/pull/11460
# https://github.com/microsoft/vcpkg/blob/7e7dad5fe20cdc085731343e0e197a7ae655555b/scripts/bootstrap.ps1#L2-L8
# https://github.com/Tyrrrz/YoutubeDownloader/blob/master/YoutubeDownloader/DownloadFfmpeg.ps1
# [Get date and time on the same line](https://stackoverflow.com/questions/20246889/get-date-and-time-on-the-same-line)
# [How to handle command-line arguments in PowerShell](https://stackoverflow.com/questions/2157554/how-to-handle-command-line-arguments-in-powershell)
# https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_functions_advanced_parameters?view=powershell-7.2
# [How to compare the contents of two string objects in PowerShell](https://stackoverflow.com/questions/18772063/how-to-compare-the-contents-of-two-string-objects-in-powershell)
# [PowerShell String Formatting: Why is the colon character causing my variable's value to be blank?](https://stackoverflow.com/questions/8386219/powershell-string-formatting-why-is-the-colon-character-causing-my-variables-v)
# [Getting Double Quotation Marks in Write-Host Output](https://stackoverflow.com/questions/34884076/getting-double-quotation-marks-in-write-host-output)
# [How do I concatenate strings and variables in PowerShell?](https://stackoverflow.com/questions/15113413/how-do-i-concatenate-strings-and-variables-in-powershell)
# [How do I add a newline to command output in PowerShell?](https://stackoverflow.com/questions/1639291/how-do-i-add-a-newline-to-command-output-in-powershell)
# [How to specify the assembly version for a .NET Core project?](https://stackoverflow.com/questions/58433665/how-to-specify-the-assembly-version-for-a-net-core-project)
# https://github.com/Tyrrrz/YoutubeDownloader/blob/2d3f0571c19ada5113a1add8313190ecb6ab1eab/Directory.Build.props#L1-L13
# [Setting the version number for .NET Core projects - CSPROJ - not JSON projects](https://stackoverflow.com/questions/43274254/setting-the-version-number-for-net-core-projects-csproj-not-json-projects)
# https://github.com/ProgerXP/Notepad2e/blob/master/src/Notepad2.ver
# https://github.com/ProgerXP/Notepad2e/blob/master/src/version.h
# https://github.com/ProgerXP/Notepad2e/blob/master/src/Extension/PreBuild.cmd
# https://github.com/zeromq/libzmq/blob/master/src/version.rc.in
# https://docs.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource
# https://github.com/andreasfertig/cppinsights/blob/main/version.h.in
# https://github.com/stefankueng/BowPad/blob/main/version.build.in
# https://github.com/mne-tools/mne-cpp/blob/main/libraries/communication/communication_global.cpp
# https://github.com/Z3Prover/z3/blob/z3-4.8.15/scripts/mk_util.py#L129-L138
# https://github.com/sorayuki/srt_build_win32
# https://github.com/veler/clipboardzanager
# https://github.com/BornToBeRoot/NETworkManager/blob/2022.2.22.0/build.ps1
# https://github.com/stefankueng/grepWin/blob/main/version.build.in
# https://github.com/stefankueng/grepWin/blob/main/src/last/version.h
# https://github.com/jonls/redshift/blob/master/src/windows/versioninfo.rc
# https://github.com/Flow-Launcher/Flow.Launcher/blob/dev/Scripts/post_build.ps1
# https://github.com/PixiEditor/PixiEditor/blob/master/assemblyVerReader.ps1
