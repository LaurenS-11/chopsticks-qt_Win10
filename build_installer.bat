@echo off
echo ====================================
echo   Chopsticks Qt - Clean Build Script
echo ====================================

cd /d "c:\Users\user\Documents\cpp_projects\chopsticks-qt_Win10"

echo.
echo [1/5] Cleaning old installer files...
if exist "build\Chopsticks-Qt-1.0.0-win64.exe" del "build\Chopsticks-Qt-1.0.0-win64.exe"
if exist "build\Chopsticks-Qt-1.0.0-win64.zip" del "build\Chopsticks-Qt-1.0.0-win64.zip"

echo [2/5] Clearing CMake cache for fresh build...
if exist "build\CMakeCache.txt" del "build\CMakeCache.txt"

echo [3/5] Configuring project with new versioning...
cmake -B build -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo [4/5] Building project...
cmake --build build --config Release

echo [5/5] Creating installer packages...
cd build
cpack

echo.
echo ====================================
echo   Build Complete! Checking results...
echo ====================================
echo.

echo Installer files created:
dir Chopsticks-Qt-*.exe Chopsticks-Qt-*.zip 2>nul

echo.
echo Done! Your new installer files should now have timestamped versions.
pause
