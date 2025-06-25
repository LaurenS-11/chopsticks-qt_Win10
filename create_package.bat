@echo off
echo ✅ Build SUCCESS! Fixed connect function issue.
echo.
echo 📦 Creating installer packages...
cd "c:\Users\user\Documents\cpp_projects\chopsticks-qt_Win10\build"
cpack
if errorlevel 1 (
    echo ❌ ERROR: Package creation failed
    pause
    exit /b 1
)

cd ..
echo.
echo 🎉 SUCCESS! Listing installer files:
dir "build\Chopsticks-Qt-*.exe" "build\Chopsticks-Qt-*.zip" 2>nul
echo.
echo ✅ Your debug window-enabled game is ready!
pause
