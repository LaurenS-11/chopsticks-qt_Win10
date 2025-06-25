# Chopsticks Qt - Package Creation Script
# This script builds and packages the Chopsticks Qt game for distribution

Write-Host "=== Chopsticks Qt Package Creator ===" -ForegroundColor Cyan
Write-Host ""

# Check if build directory exists
if (!(Test-Path "build")) {
    Write-Host "Creating build directory..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Configure project
Write-Host "Configuring project..." -ForegroundColor Green
cmake -B build -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Configuration failed!" -ForegroundColor Red
    exit 1
}

# Build project
Write-Host "Building project..." -ForegroundColor Green
cmake --build build --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

# Create packages
Write-Host "Creating distribution packages..." -ForegroundColor Green
Set-Location build

# Create ZIP package
Write-Host "  Creating ZIP package..." -ForegroundColor Yellow
cpack -G ZIP

# Check if NSIS is available and create installer
$nsisPath = Get-Command makensis -ErrorAction SilentlyContinue
if ($nsisPath) {
    Write-Host "  Creating NSIS installer..." -ForegroundColor Yellow
    cpack -G NSIS
} else {
    Write-Host "  NSIS not found - skipping installer creation" -ForegroundColor Yellow
    Write-Host "  Install NSIS from https://nsis.sourceforge.io/ to create Windows installers" -ForegroundColor Gray
}

Set-Location ..

# Show results
Write-Host ""
Write-Host "=== Package Creation Complete ===" -ForegroundColor Cyan
Write-Host "Created packages:" -ForegroundColor Green

Get-ChildItem "build\*.zip" | ForEach-Object {
    $size = [math]::Round($_.Length / 1MB, 1)
    Write-Host "  [ZIP] $($_.Name) ($size MB)" -ForegroundColor White
}

Get-ChildItem "build\*.exe" | Where-Object { $_.Name -like "*Chopsticks-Qt*" } | ForEach-Object {
    $size = [math]::Round($_.Length / 1MB, 1)
    Write-Host "  [INSTALLER] $($_.Name) ($size MB)" -ForegroundColor White
}

Write-Host ""
Write-Host "Distribution packages are ready in the 'build' directory!" -ForegroundColor Green
