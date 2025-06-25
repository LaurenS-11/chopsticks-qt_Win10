# Chopsticks Qt - Windows 10 Edition

A Qt-based implementation of the classic Chopsticks finger game built with C++ and Qt5.

## Game Overview

**Chopsticks** is a classic hand game that combines simple math with strategic thinking. This digital version recreates the beloved finger-counting game where two players try to eliminate each other's hands through clever tapping and splitting moves.

### 🎮 How to Play Chopsticks

#### Basic Setup
- **Players**: 2 players (Player 1 vs Player 2)
- **Starting Position**: Each player begins with **1 finger up** on each hand
- **Goal**: Force your opponent to have **both hands "out"** (5+ fingers) to win

#### 📋 Game Rules

**1. Taking Turns**
- Players alternate turns
- On your turn, choose one of your hands to "tap" one of your opponent's hands
- The opponent's tapped hand gains fingers equal to your tapping hand

**2. Finger Math**
```
Example: Your hand has 3 fingers, opponent's hand has 2 fingers
After tapping: Opponent's hand = 2 + 3 = 5 fingers (now "out"!)
```

**3. Hand States**
- **Active Hand**: 1-4 fingers (can tap and be tapped)
- **Out Hand**: 5+ fingers (cannot tap or be tapped, shown as fist)
- **Dead Hand**: Permanently eliminated (fist icon)

**4. Special Move: "Bumping" (Splitting)**
- When you have an **even number** of fingers on one hand, you can **split** them
- Example: 4 fingers on right hand → Split to 2 fingers on each hand
- This strategic move can revive a dead hand or balance your attack options

#### 🏆 Winning Conditions
- **Victory**: Your opponent has both hands "out" (5+ fingers each)
- **Continue Playing**: As long as each player has at least one active hand

#### 💡 Strategy Tips
- **Offensive**: Try to force your opponent's hands to exactly 5 fingers
- **Defensive**: Use splitting to avoid having both hands reach 5 fingers
- **Tactical**: Sometimes it's better to split even when you don't have to
- **Planning**: Think ahead - consider what your opponent might do next

### 🎯 Example Game Sequence

```
Initial State:
Player 1: Left(1) Right(1)    Player 2: Left(1) Right(1)

Turn 1 - Player 1: Taps Player 2's left hand with right hand
Player 1: Left(1) Right(1)    Player 2: Left(2) Right(1)

Turn 2 - Player 2: Taps Player 1's left hand with left hand  
Player 1: Left(3) Right(1)    Player 2: Left(2) Right(1)

Turn 3 - Player 1: Taps Player 2's right hand with left hand
Player 1: Left(3) Right(1)    Player 2: Left(2) Right(4)

Turn 4 - Player 2: Splits right hand (4 → 2+2)
Player 1: Left(3) Right(1)    Player 2: Left(2) Right(2)

Turn 5 - Player 1: Taps Player 2's left hand with left hand
Player 1: Left(3) Right(1)    Player 2: Left(5-OUT) Right(2)

... Game continues until one player has both hands out!
```

### 🎨 User Interface
- **Visual Hand Display**: Clear finger count indicators
- **Click to Play**: Simple point-and-click interface
- **Turn Indicators**: Always know whose turn it is
- **Split Button**: Easy access to splitting when available
- **Game Status**: Win/lose notifications and score tracking

## Prerequisites

### Required Software
- **CMake** 3.10 or higher
- **MinGW-w64** (GCC compiler)
- **Qt5** (version 5.15.2 or compatible)
- **Visual Studio Code** (recommended IDE)

### Qt5 Installation
This project is configured to work with Qt5 installed at:
```
C:\Qt\5.15.2\mingw81_64\
```

If your Qt installation is in a different location, update the `CMAKE_PREFIX_PATH` in `CMakeLists.txt`:
```cmake
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")
```

## Project Structure

```
chopsticks-qt_Win10/
├── CMakeLists.txt              # Build configuration with automatic DLL deployment & icon embedding
├── CMakePresets.json           # CMake presets
├── README.md                  # This comprehensive documentation
├── LICENSE.txt                # License file
├── create-package.ps1         # Automated build & packaging script
├── build/                     # Build output directory (auto-generated)
├── resources/                 # Resource files & custom branding
│   ├── chopsticks.qrc         # Qt resource file
│   ├── chopsticks-icon.svg    # Custom vector icon (blue gradient, golden chopsticks)
│   ├── chopsticks-icon.ico    # Multi-resolution icon (16x16, 32x32, 48x48, 256x256)
│   ├── chopsticks-icon-simple.svg # Alternative simple icon design
│   └── app.rc.in              # Windows resource template for icon embedding
└── src/                       # Source code
    ├── chopsticks-qt.cpp      # Main application entry point
    ├── gamewindow.cpp         # Game window implementation
    ├── gamewindow.h           # Game window header
    ├── player.cpp             # Player class implementation
    └── player.h           # Player class header
```

## Building the Project

### Quick Build (Command Line)
```bash
# Configure the project
cmake -B build -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build build
```

### Using VS Code
1. Open the project folder in VS Code
2. Use the CMake extension to configure and build
3. The project will automatically configure with the default preset

### Traditional CMake Build
1. Ensure you have CMake and Qt installed on your system.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
5. Build the project:
   ```bash
   cmake --build .
   ```

## Automatic DLL Deployment

🎉 **This project features automatic DLL deployment** that copies all required runtime libraries to the build directory after each successful build, ensuring your application runs on any Windows system without requiring Qt or MinGW to be installed.

### Deployed DLLs

#### Qt5 Libraries
- **Qt5Core.dll** - Core Qt functionality
- **Qt5Gui.dll** - GUI components and rendering
- **Qt5Widgets.dll** - Widget toolkit and UI controls

#### MinGW Runtime Libraries
- **libgcc_s_seh-1.dll** - GCC runtime library
- **libstdc++-6.dll** - C++ standard library
- **libwinpthread-1.dll** - POSIX threading library

#### Qt Platform Plugins
- **platforms/qwindows.dll** - Windows platform integration plugin (required for GUI applications)

### How It Works
The automatic DLL deployment is implemented using CMake's `add_custom_command` with the `POST_BUILD` event:

```cmake
# Automatically copy Qt5 and MinGW runtime DLLs to build directory after build
add_custom_command(TARGET chopsticks-qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/Qt5Gui.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/Qt5Widgets.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/libgcc_s_seh-1.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/libstdc++-6.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/libwinpthread-1.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMAND ${CMAKE_COMMAND} -E make_directory
    $<TARGET_FILE_DIR:chopsticks-qt>/platforms
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>/platforms/
    COMMENT "Copying Qt5, MinGW runtime DLLs and platform plugins to build directory"
)
```

### Benefits
- ✅ **Fully Automatic** - No manual DLL copying required
- ✅ **Efficient** - Only copies DLLs when they change (`copy_if_different`)
- ✅ **Portable** - Executable runs on systems without Qt/MinGW installed
- ✅ **Development Friendly** - Works with any build method (command line, VS Code, etc.)

## Running the Application

After building, the executable and all required DLLs will be in the `build/` directory:

```bash
# Run the application
./build/chopsticks-qt.exe
```

The application will launch the Qt GUI for the Chopsticks game.

## Creating Distribution Packages

🚀 **This project includes CPack configuration for creating professional distribution packages!**

### Available Package Formats

#### ZIP Package (Ready to Use)
Creates a clean ZIP file with the executable and all dependencies:

```bash
# Build in Release mode
cmake -B build -S . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Create ZIP package
cd build
cpack -G ZIP
```

This creates: `Chopsticks-Qt-1.0.0-win64.zip` (~10.9 MB)

#### 🎨 Windows Installer with Custom Icon
For a professional Windows installer with custom chopsticks branding:

1. **Install NSIS** (Nullsoft Scriptable Install System):
   - Download from: https://nsis.sourceforge.io/Download
   - Or using Chocolatey: `choco install nsis`

2. **Create the installer**:
   ```bash
   cd build
   cpack -G NSIS
   ```

This creates: `Chopsticks-Qt-1.0.0-win64.exe` (~9.1 MB installer)

### 🎨 Custom Icon Integration (Complete Setup)

Your project now includes **complete custom icon integration** with a beautiful blue and gold chopsticks design!

#### ✅ **Pre-configured Icon Files**
- **`resources/chopsticks-icon.svg`** - Source vector icon (blue gradient background, golden chopsticks)
- **`resources/chopsticks-icon.ico`** - Multi-resolution ICO file (16x16, 32x32, 48x48, 256x256)
- **`resources/chopsticks-icon-simple.svg`** - Alternative simple design

#### ✅ **Automatic Icon Integration**
The CMakeLists.txt automatically:
1. **Detects** the `chopsticks-icon.ico` file
2. **Embeds** the icon into the Windows executable (`chopsticks-qt.exe`)
3. **Configures** the NSIS installer to use the custom icon
4. **Sets up** Start Menu and Desktop shortcuts with the icon

#### ✅ **Icon Appears In:**
- 🎨 **Installer executable** - Custom icon for the installer file itself
- 🎨 **Installation wizard** - Your icon throughout the installation process
- 🎨 **Game executable** - The `chopsticks-qt.exe` shows your icon in Windows Explorer
- 🎨 **Start Menu shortcut** - Professional shortcut with custom icon
- 🎨 **Desktop shortcut** - (Optional) Desktop shortcut with custom icon
- 🎨 **Uninstaller** - Consistent branding in the uninstall process

#### 🔄 **To Update the Icon:**
1. Replace `resources/chopsticks-icon.ico` with your new icon
2. Run `.\create-package.ps1` to rebuild with the new icon
3. The system automatically detects and uses the updated icon

### Package Contents
Both packages include:
- ✅ `chopsticks-qt.exe` - The game executable (180KB with embedded icon)
- ✅ All required Qt5 DLLs (Qt5Core, Qt5Gui, Qt5Widgets)
- ✅ All MinGW runtime DLLs (libgcc, libstdc++, libwinpthread)
- ✅ Qt platform plugin (`platforms/qwindows.dll`)
- ✅ Professional custom icon integration throughout
- ✅ Ready to run on any Windows system

### Distribution Benefits
- 🎯 **Professional**: Clean, properly structured packages with custom branding
- 📦 **Self-contained**: No installation dependencies required
- 🚀 **Easy sharing**: Single file distribution
- 💾 **Optimized size**: ~10.9 MB ZIP package, ~9.1 MB NSIS installer
- 🛠️ **Professional installer**: NSIS installer with custom icon and shortcuts
- ✨ **Complete branding**: Custom chopsticks icon throughout user experience

## Development Notes

### C++ Standard
The project uses **C++17** features:
```cmake
set_property(TARGET chopsticks-qt PROPERTY CXX_STANDARD 17)
```

### Qt Features Used
- **Qt5::Widgets** - Main UI framework
- **CMAKE_AUTOMOC** - Automatic Meta-Object Compiler
- **CMAKE_AUTORCC** - Automatic Resource Compiler
- **CMAKE_AUTOUIC** - Automatic User Interface Compiler

### Compiler Compatibility
- Built and tested with **MinGW-w64 GCC 14.2.0**
- Compatible with Qt5 MinGW builds
- Uses Qt5.15.2 mingw81_64 build

### 🚀 Automated Build & Package Script

For the ultimate convenience, use the included PowerShell automation script:

```powershell
# One command to build and package everything!
.\create-package.ps1
```

**This script automatically:**
- ✅ Configures the project in Release mode
- ✅ Builds the application with all dependencies
- ✅ Copies Qt5 and MinGW runtime DLLs
- ✅ Embeds the custom icon into the executable
- ✅ Creates both ZIP and NSIS installer packages
- ✅ Provides detailed progress and success confirmation

**Output files created:**
- `build/Chopsticks-Qt-1.0.0-win64.zip` (~10.9 MB) - Portable ZIP package
- `build/Chopsticks-Qt-1.0.0-win64.exe` (~9.1 MB) - Professional installer with custom icon
- `build/chopsticks-qt.exe` (180KB) - Game executable with embedded icon

## Troubleshooting

### Qt5 Not Found Error
If you get "Could not find a package configuration file provided by Qt5":
1. Verify Qt5 is installed at `C:\Qt\5.15.2\mingw81_64\`
2. Update `CMAKE_PREFIX_PATH` in `CMakeLists.txt` if needed
3. Ensure you're using the MinGW build of Qt5

### Missing DLL Errors
If the application fails to start due to missing DLLs:
1. Rebuild the project - DLLs are copied automatically
2. Check that all 6 DLLs are present in the `build/` directory
3. Verify your Qt installation includes the MinGW runtime

### Qt Platform Plugin Errors
If you get "Could not find the Qt platform plugin 'windows'":
1. Ensure the `platforms/` directory exists in your build folder
2. Verify `qwindows.dll` is present in `build/platforms/`
3. Rebuild the project to copy platform plugins automatically

### Build Errors
- Ensure CMake 3.10+ is installed
- Verify MinGW-w64 is in your PATH
- Check that Qt5 installation is complete

## Technical Specifications

- **Target Platform**: Windows 10
- **Compiler**: MinGW-w64 GCC 14.2.0
- **Qt Version**: 5.15.2
- **CMake Version**: 3.10+
- **C++ Standard**: C++17
- **Build System**: CMake with Unix Makefiles

---

## 🎯 Quick Start Summary

**For immediate results:**
1. **Install prerequisites**: CMake, MinGW-w64, Qt5, NSIS
2. **Run the automation script**: `.\create-package.ps1`
3. **Get professional packages**: ZIP (~10.9MB) and installer (~9.1MB) with custom branding

**Key Features:**
- ✅ **Complete Qt5 game** with enhanced UI
- ✅ **Automatic dependency management** (no manual DLL copying)
- ✅ **Professional custom icon** throughout installer and executable
- ✅ **One-click packaging** with PowerShell automation
- ✅ **Production-ready distribution** packages

**Note**: This project is configured specifically for Windows 10 with MinGW-w64 and Qt5. For other platforms or Qt versions, modifications to the CMakeLists.txt may be required.

**Enjoy playing Chopsticks!** 🥢✨