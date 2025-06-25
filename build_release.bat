@echo off
setlocal enabledelayedexpansion

echo ====================================================
echo   Chopsticks Qt - Release Build and Installer
echo ====================================================
echo.

:: Change to project directory
cd /d "c:\Users\user\Documents\cpp_projects\chopsticks-qt_Win10"

:: Check if we're in the right directory
if not exist "CMakeLists.txt" (
    echo ❌ ERROR: CMakeLists.txt not found. Please run this script from the project root.
    pause
    exit /b 1
)

echo ✅ Project directory: %CD%
echo.

:: Step 1: Clean previous builds
echo [1/6] Cleaning previous build artifacts...
if exist "build\" (
    echo    - Removing old installer files...
    del /q "build\Chopsticks-Qt-*.exe" 2>nul
    del /q "build\Chopsticks-Qt-*.zip" 2>nul
    echo    - Clearing CMake cache...
    del /q "build\CMakeCache.txt" 2>nul
    del /q "build\cmake_install.cmake" 2>nul
    if exist "build\CMakeFiles\" rmdir /s /q "build\CMakeFiles" 2>nul
) else (
    echo    - Creating build directory...
    mkdir build
)
echo    [OK] Cleanup complete
echo.

:: Step 2: Configure project
echo [2/6] Configuring CMake project...
cmake -B build -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    pause
    exit /b 1
)
echo    [OK] Configuration complete
echo.

:: Step 3: Build project
echo [3/6] Building project (Release mode)...
cmake --build build --config Release
if errorlevel 1 (
    echo [ERROR] Build failed
    pause
    exit /b 1
)
echo    [OK] Build complete
echo.

:: Step 4: Verify executable
echo [4/6] Verifying build output...
if not exist "build\chopsticks-qt.exe" (
    echo [ERROR] chopsticks-qt.exe not found in build directory
    pause
    exit /b 1
)
echo    [OK] Executable found: build\chopsticks-qt.exe
echo.

:: Step 5: Create installer packages
echo [5/6] Creating installer packages...
cd build
cpack
if errorlevel 1 (
    echo [ERROR] Package creation failed
    cd ..
    pause
    exit /b 1
)
cd ..
echo    [OK] Packages created
echo.

:: Step 6: Display results
echo [6/6] Build Results Summary
echo ====================================================
echo.

:: List all created files
echo [BUILD] Build Directory Contents:
dir "build\chopsticks-qt.exe" 2>nul | find "chopsticks-qt.exe"
echo.

echo [PACKAGES] Installer Packages:
for %%f in (build\Chopsticks-Qt-*.exe) do (
    echo    Installer: %%~nxf
    echo       Size: %%~zf bytes
)
for %%f in (build\Chopsticks-Qt-*.zip) do (
    echo    Archive: %%~nxf  
    echo       Size: %%~zf bytes
)
echo.

:: Show final status
echo ====================================================
echo [SUCCESS] Release build completed successfully!
echo.
echo [RUN] To run the game:
echo    .\build\chopsticks-qt.exe
echo.
echo [DISTRIBUTE] To distribute:
echo    Use the installer .exe file from the build directory
echo.
echo [DEBUG WINDOW] Debug Window Feature:
echo    - Click "Show Debug Info" in setup dialog
echo    - Automatic for network games
echo    - Large scrollable window with categorized tabs
echo ====================================================
echo.

pause
