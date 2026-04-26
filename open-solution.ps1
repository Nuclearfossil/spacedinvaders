<#
.SYNOPSIS
    Opens the SpacedInvaders solution in the specified Visual Studio version.
.DESCRIPTION
    Locates devenv.exe for the requested VS version using vswhere, then opens
    the pre-generated solution from the corresponding build directory.
.PARAMETER Version
    Visual Studio year shorthand: 22 (VS 2022) or 26 (VS 2026).
.EXAMPLE
    .\open-solution.ps1 22
    .\open-solution.ps1 -Version 26
#>
param(
    [Parameter(Position = 0)]
    [ValidateSet('22', '26')]
    [string]$Version,

    [Alias('h')]
    [switch]$Help
)

if ($Help -or -not $Version) {
    Get-Help $MyInvocation.MyCommand.Path -Detailed
    exit 0
}

$vsYear     = if ($Version -eq '22') { '2022' } else { '2026' }
# vswhere uses internal VS major versions: 2022=17, 2026=18
$vsMajor    = if ($Version -eq '22') { 17 } else { 18 }
$buildDir   = Join-Path $PSScriptRoot "build-vs$vsYear"
$slnExt     = if ($Version -eq '22') { 'sln' } else { 'slnx' }
$slnPath    = Join-Path $buildDir "SpacedInvaders.$slnExt"

if (-not (Test-Path $slnPath)) {
    Write-Error "Solution not found: $slnPath`nRun 'make vs$Version' first."
    exit 1
}

$devenv = $null

# Try vswhere first (may not know about VS 2026 if installer is old)
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vswhere) {
    $devenv = & $vswhere -version "[$vsMajor.0,$($vsMajor + 1).0)" `
        -products * -requires Microsoft.Component.MSBuild `
        -find 'Common7\IDE\devenv.exe' | Select-Object -First 1
}

# Fallback: glob for devenv.exe under the internal-version directory (e.g. \18\)
if (-not $devenv) {
    $devenv = Get-ChildItem "$env:ProgramFiles\Microsoft Visual Studio\$vsMajor\*\Common7\IDE\devenv.exe" `
        -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName
}

if (-not $devenv) {
    Write-Error "Visual Studio $vsYear not found."
    exit 1
}

Write-Host "Opening $slnPath with Visual Studio $vsYear..."
& $devenv $slnPath
