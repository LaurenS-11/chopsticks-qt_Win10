@echo off
echo 🔨 Quick Build - Chopsticks Qt
echo ================================

cd /d "c:\Users\user\Documents\cpp_projects\chopsticks-qt_Win10"

:: Quick build without full cleanup
echo Building...
cmake --build build --config Release
if errorlevel 1 (
    echo ❌ Build failed
    pause
    exit /b 1
)

echo ✅ Build complete!
echo 🚀 Run: .\build\chopsticks-qt.exe
pause
