# Chopsticks Qt - Windows 10 Edition

A feature-rich Qt-based implementation of the classic Chopsticks finger game with **multiple game modes**: local multiplayer, single-player vs AI, and network multiplayer support!

## ✅ Project Status

**Current Version**: 1.2.20250625 (Production Ready)
- 🚀 **Fully Functional**: Application launches and runs without crashes
- 🎮 **All Game Modes Working**: Local, AI, and Network multiplayer fully implemented
- 🏗️ **Clean Codebase**: Streamlined, production-ready implementation
- 📦 **Professional Packaging**: Windows installer and portable builds available
- ✅ **Stable & Tested**: Crash-free gameplay across all modes

**What's New in This Version:**
- ✅ Resolved startup crashes and Unicode character issues
- 🔧 Simplified main application architecture  
- 🧹 Cleaned up debug code and temporary files
- 📚 Updated comprehensive documentation
- 🚀 Optimized build scripts and automation

## 🎮 Game Modes

This enhanced version offers **four exciting ways to play**:

### 👥 **Local Two Player** (Default)
- **Classic experience**: Two human players on the same computer
- **Pass-and-play**: Take turns using the same device
- **Perfect for**: Family game time, friends hanging out
- **No setup required**: Launch and play immediately

### 🤖 **Single Player vs Computer**
- **AI Challenge**: Face an intelligent computer opponent
- **Three difficulty levels**: Easy, Medium, and Hard
- **Perfect for**: Strategy practice, solo gaming, skill development
- **Smart AI**: Each difficulty has distinct playing styles and personalities

### 🏠 **Network Server** (Host Game)
- **Host games**: Create a server for remote players to join
- **Share with friends**: Give out your IP address for connections
- **Control the game**: Manage settings and game flow
- **Perfect for**: Hosting game nights with distant friends

### 🔗 **Network Client** (Join Game)  
- **Join remote games**: Connect to friends' hosted games
- **Play anywhere**: Connect from any location with internet
- **Real-time gameplay**: Synchronized moves and game state
- **Perfect for**: Playing with friends across the world

## Game Overview

**Chopsticks** is a classic hand game that combines simple math with strategic thinking. This digital version recreates the beloved finger-counting game where players try to eliminate each other's hands through clever tapping and splitting moves.

## 🚀 Quick Start Guide

### **Launching the Game**
1. **Run the executable**: `chopsticks-qt.exe`
2. **Choose your game mode** from the startup dialog:
   - 👥 **Local Two Player** - Classic same-computer gameplay
   - 🤖 **Single Player vs AI** - Challenge the computer
   - 🏠 **Network Server** - Host a game for friends
   - 🔗 **Network Client** - Join a friend's game
3. **Configure settings** based on your chosen mode
4. **Start playing** and enjoy!

### **Quick Local Game** (Default)
1. Launch the game
2. Select "👥 Local Two Player (Same Computer)" 
3. Click "🎮 Start Local Game"
4. Pass the computer between players on each turn
5. Enjoy classic Chopsticks gameplay!

### **Quick AI Challenge**
1. Launch the game
2. Select "🤖 Single Player vs Computer"
3. Choose difficulty: **Easy** (learning), **Medium** (balanced), or **Hard** (expert)
4. Click "🤖 Challenge Computer"
5. Test your skills against intelligent AI!

### **Quick Network Game**
1. **Host player**: Select "🏠 Network Server", choose port, click "Start Server"
2. **Joining player**: Select "🔗 Network Client", enter host's IP and port, click "Connect"
3. **Both players**: Wait for connection, then click "Start Game"
4. Enjoy real-time multiplayer across any distance!

## 🤖 AI Opponent Features

Your computer opponent offers three distinct personalities:

### 😊 **Easy - "The Learner"**
- **Skill Level**: Beginner-friendly
- **Strategy**: 30% optimal moves, 70% random
- **Personality**: Makes mistakes, unpredictable
- **Perfect for**: New players, children, casual fun

### 😐 **Medium - "The Strategist"**  
- **Skill Level**: Balanced challenge
- **Strategy**: 80% optimal moves with occasional surprises
- **Personality**: Generally smart with tactical variations
- **Perfect for**: Most players, enjoyable challenge

### 😈 **Hard - "The Master"**
- **Skill Level**: Expert-level challenge
- **Strategy**: Always makes optimal moves
- **Personality**: Ruthless efficiency, plans multiple moves ahead
- **Perfect for**: Experienced players, serious competition

### **AI Behavior Examples**

**Easy AI Turn:**
```
*AI thinking* "Hmm... maybe I'll tap here? Or there? Let's try this random move!"
→ Result: Suboptimal but fun and unpredictable gameplay
```

**Medium AI Turn:**
```
*AI calculating* "If I tap here, opponent gets 4 fingers... but they could split... 
80% chance this is the right move, let's go with it!"
→ Result: Generally smart decisions with occasional tactical surprises
```

**Hard AI Turn:**
```
*AI analyzing* "Optimal move: tap left hand to eliminate opponent's right hand.
This sets up winning position in exactly 3 moves."
→ Result: Perfect gameplay that will challenge even expert players
```

## 🌐 Network Multiplayer Features

### **Connection Types**

#### **Local Network** (Same Wi-Fi/LAN)
- **Easy setup**: Use local IP addresses (192.168.x.x)
- **Fast connection**: Low latency gaming
- **No internet required**: Works offline on local networks
- **Perfect for**: Home networks, office games, LAN parties

#### **Internet Play** (Worldwide)
- **Global gaming**: Play with friends anywhere
- **Port forwarding required**: Configure router for hosting
- **Dynamic IP support**: Use external IP addresses
- **Perfect for**: Long-distance friendships, online competitions

### **Network Protocol**
- **Technology**: Qt Network module with TCP connections
- **Message Format**: Lightweight JSON protocol
- **Real-time Sync**: Immediate move updates between players
- **Security**: Input validation and graceful error handling

### **Connection Management**
- **Automatic reconnection**: Handles temporary disconnections
- **Error recovery**: Graceful handling of network issues
- **Status monitoring**: Real-time connection status display
- **Timeout protection**: Prevents indefinite waiting

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

### 🎨 Enhanced User Interface
- **Mode Selection Dialog**: Choose your game type at startup
- **Visual Hand Display**: Clear finger count indicators for all game modes  
- **Click to Play**: Simple point-and-click interface
- **Turn Indicators**: Always know whose turn it is (local/AI/network)
- **Split Button**: Easy access to splitting when available
- **Network Status**: Real-time connection and player status
- **AI Difficulty Display**: Shows current AI opponent level
- **Game Status**: Win/lose notifications and comprehensive game tracking

## Prerequisites

### Required Software
- **CMake** 3.10 or higher
- **MinGW-w64** (GCC compiler)
- **Qt5** with **Network module** (version 5.15.2 or compatible)
- **Visual Studio Code** (recommended IDE)
- **NSIS** (optional, for creating Windows installers)

### Qt5 Installation with Network Support
This project requires Qt5 with the **Network module** for multiplayer functionality. Install at:
```
C:\Qt\5.15.2\mingw81_64\
```

**Ensure Network module is included:**
- Qt5Core, Qt5Gui, Qt5Widgets (standard)
- **Qt5Network** (required for multiplayer)

If your Qt installation is in a different location, update the `CMAKE_PREFIX_PATH` in `CMakeLists.txt`:
```cmake
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")
```

## Project Structure

## 📁 Project Structure

```
chopsticks-qt_Win10/
├── CMakeLists.txt              # Enhanced build configuration with Qt Network, automatic DLL deployment & installer creation
├── CMakePresets.json           # CMake presets for development workflow
├── README.md                   # This comprehensive documentation
├── LICENSE.txt                 # License file
├── build_release.bat           # Complete release build script with installer creation
├── quick_build.bat             # Fast incremental build for development  
├── create_package.bat          # Package-only script for existing builds
├── build_installer.bat         # Installer creation script
├── create-package.ps1          # PowerShell packaging script
├── setup-icon.ps1              # Icon setup automation
├── test_qt.cmake               # CMake testing utilities
├── example-installer.nsi       # NSIS installer template
├── build/                      # Build output directory (auto-generated)
│   ├── version.h               # Auto-generated version header with build timestamp
│   ├── chopsticks-qt.exe       # Game executable (optimized)
│   ├── Chopsticks-Qt-1.2.YYYYMMDD-win64.zip    # Portable ZIP package
│   └── Chopsticks-Qt-1.2.YYYYMMDD-win64.exe    # Windows installer
├── resources/                  # Resource files & custom branding
│   ├── chopsticks.qrc          # Qt resource file
│   ├── chopsticks-icon.ico     # Multi-resolution Windows icon
│   └── app.rc.in               # Windows resource template for icon embedding
├── src/                        # Source code with clean, production-ready implementation
│   ├── chopsticks-qt.cpp       # Main application entry point (streamlined)
│   ├── gamewindow.cpp          # Game window implementation
│   ├── gamewindow.h            # Game window header
│   ├── player.cpp              # Player class implementation
│   ├── player.h                # Player class header
│   ├── aiplayer.cpp            # AI opponent with 3 difficulty levels
│   ├── aiplayer.h              # AI opponent header
│   ├── networkmanager.cpp      # Network multiplayer functionality
│   ├── networkmanager.h        # Network multiplayer header
│   ├── networkdialog.cpp       # Game setup dialog (supports all 4 game modes)
│   ├── networkdialog.h         # Game setup dialog header
│   └── version.h.in            # Version template for build-time timestamp generation
└── .git/                       # Git repository (version control)
```

**Key Features:**
- ✅ **Clean Architecture**: Streamlined codebase without debug artifacts
- 🚀 **Automated Building**: Comprehensive batch scripts for easy compilation
- 📦 **Professional Packaging**: Windows installer and portable ZIP creation
- 🎯 **Production Ready**: Optimized executable with proper resource embedding

## 🛠️ Building the Project

### 🚀 Automated Build Scripts (Recommended)

The project includes several Windows batch files to make building easy:

#### **� build_release.bat - Complete Release Build**
```batch
build_release.bat
```
**What it does:**
- ✅ Cleans previous build artifacts  
- ⚙️ Configures CMake project for Release mode
- 🔨 Builds the complete project with optimizations
- 📦 Creates Windows installer (.exe) and portable archive (.zip)
- ✅ Verifies executable works correctly
- 📋 Shows detailed build summary and file sizes

**Generated files:**
- `build/chopsticks-qt.exe` - The game executable (optimized)
- `build/Chopsticks-Qt-1.2.YYYYMMDD-win64.exe` - Windows installer
- `build/Chopsticks-Qt-1.2.YYYYMMDD-win64.zip` - Portable archive

**Best for:** Final releases, distribution packages

#### **⚡ quick_build.bat - Fast Development Build**
```batch
quick_build.bat
```
**What it does:**
- 🔨 Performs incremental build (no cleanup)
- ⚡ Fast compilation for testing changes
- ✅ Builds in Release mode with optimizations
- 🚀 Shows how to run the executable

**Best for:** Development, testing changes quickly

#### **📦 create_package.bat - Package Existing Build**
```batch
create_package.bat
```
**What it does:**
- 📦 Creates installer packages from existing build
- ⚡ No compilation - just packaging
- 📋 Lists generated files with sizes

**Best for:** Creating installers after manual builds

### 🔧 Manual Build Options
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

## 🌐 Network Multiplayer Setup

### **Local Network Gaming** (Easiest)

#### **Step 1: Host Setup**
1. Launch the game on the host computer
2. Select "🏠 Network Server (Host Game)"
3. Choose a port (default: 8080 works great)
4. Click "Start Server"
5. **Share your local IP** with other players:
   ```
   Example: "Join my game at 192.168.1.100 port 8080"
   ```

#### **Step 2: Join Setup**  
1. Launch the game on the joining computer
2. Select "🔗 Network Client (Join Game)"
3. Enter the host's IP address (e.g., `192.168.1.100`)
4. Enter the port number (e.g., `8080`)
5. Click "Connect to Server"

#### **Step 3: Start Playing**
- Both players see "Connected" status
- Host clicks "Start Game" to begin
- Enjoy real-time multiplayer Chopsticks!

### **Internet Gaming** (For Friends Far Away)

#### **Requirements**
- Host must configure **router port forwarding**
- Host needs to share their **external IP address**

#### **Host Setup** (Router Configuration Required)
1. **Configure router**: Forward TCP port 8080 to host computer's local IP
2. **Find external IP**: Use whatismyip.com or similar service
3. **Start server**: Follow local network steps above
4. **Share external IP**: Give friends your external IP instead of local IP

#### **Join Setup**
1. Get external IP and port from host
2. Follow standard joining steps using external IP
3. Example: Connect to `203.0.113.1` port `8080`

### **Network Troubleshooting**

#### **Connection Issues**
- ✅ **Firewall**: Allow port 8080 through Windows Firewall
- ✅ **IP Address**: Verify correct IP (use `ipconfig` on Windows)  
- ✅ **Port**: Ensure both players use the same port number
- ✅ **Local Test**: Try with local IP first (192.168.x.x)

#### **Router Configuration**
- **Port Forwarding**: TCP port 8080 → host computer's local IP
- **Dynamic IP**: Consider using Dynamic DNS for changing external IPs
- **Multiple Games**: Use different ports for multiple simultaneous games

#### **Network Diagnostics** (Windows)
```powershell
# Test connectivity to server
Test-NetConnection -ComputerName [server-ip] -Port 8080

# Check what ports are listening
netstat -an | Select-String "8080"

# Find your local IP address
ipconfig | Select-String "IPv4"
```

## Automatic DLL Deployment with Network Support

🎉 **This project features automatic DLL deployment** that copies all required runtime libraries to the build directory after each successful build, ensuring your application runs on any Windows system without requiring Qt or MinGW to be installed.

### Deployed DLLs (Complete Runtime)

#### Qt5 Libraries (Enhanced with Network Support)
- **Qt5Core.dll** - Core Qt functionality
- **Qt5Gui.dll** - GUI components and rendering
- **Qt5Widgets.dll** - Widget toolkit and UI controls
- **Qt5Network.dll** - **NEW!** Network communication for multiplayer support

#### MinGW Runtime Libraries
- **libgcc_s_seh-1.dll** - GCC runtime library
- **libstdc++-6.dll** - C++ standard library
- **libwinpthread-1.dll** - POSIX threading library

#### Qt Platform Plugins
- **platforms/qwindows.dll** - Windows platform integration plugin (required for GUI applications)

### How It Works (Updated for Network Support)
The automatic DLL deployment now includes **Qt5Network.dll** for multiplayer functionality:

```cmake
# Enhanced deployment with network support
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
    "${CMAKE_PREFIX_PATH}/bin/Qt5Network.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    # ... MinGW runtime DLLs and platform plugins
    COMMENT "Copying Qt5 (including Network), MinGW runtime DLLs and platform plugins"
)
```
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>/platforms/
    COMMENT "Copying Qt5, MinGW runtime DLLs and platform plugins to build directory"
)
```

### Benefits
- ✅ **Fully Automatic** - No manual DLL copying required
- ✅ **Complete Runtime** - Includes network support for multiplayer gaming
- ✅ **Efficient** - Only copies DLLs when they change (`copy_if_different`)
- ✅ **Portable** - Executable runs on systems without Qt/MinGW installed
- ✅ **Development Friendly** - Works with any build method (command line, VS Code, etc.)
- ✅ **Network Ready** - All multiplayer dependencies included

## Running the Application

After building, the executable and all required DLLs will be in the `build/` directory:

```bash
# Run the game (shows startup mode selection dialog)
./build/chopsticks-qt.exe
```

### **Game Startup Flow**
1. **Mode Selection Dialog** appears automatically
2. **Choose your preferred game mode**: Local, AI, Network Server, or Network Client
3. **Configure settings** based on your selection (AI difficulty, network settings, etc.)
4. **Click to start** your chosen game type
5. **Enjoy enhanced Chopsticks gameplay!**

The application launches with the comprehensive Qt GUI that supports all game modes.

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

### Package Contents (Complete Game Suite)
Both packages include:
- ✅ `chopsticks-qt.exe` - Enhanced game executable with all modes (180KB with embedded icon)
- ✅ All required Qt5 DLLs (Qt5Core, Qt5Gui, Qt5Widgets, **Qt5Network**)
- ✅ All MinGW runtime DLLs (libgcc, libstdc++, libwinpthread)
- ✅ Qt platform plugin (`platforms/qwindows.dll`)  
- ✅ **Network multiplayer support** - Play with friends anywhere
- ✅ **AI opponent with 3 difficulty levels** - Single-player challenge
- ✅ **Local two-player mode** - Classic same-computer gameplay
- ✅ Professional custom icon integration throughout
- ✅ Ready to run on any Windows system

### Distribution Benefits
- 🎯 **Complete Game Suite**: All 4 game modes in one package
- 🤖 **AI Challenge**: Three difficulty levels for single-player fun
- 🌐 **Network Gaming**: Real-time multiplayer across any distance
- 👥 **Local Multiplayer**: Classic pass-and-play experience
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

### Qt Features Used (Enhanced)
- **Qt5::Widgets** - Main UI framework and game interface
- **Qt5::Network** - **NEW!** TCP networking for multiplayer support
- **CMAKE_AUTOMOC** - Automatic Meta-Object Compiler
- **CMAKE_AUTORCC** - Automatic Resource Compiler
- **CMAKE_AUTOUIC** - Automatic User Interface Compiler

### Compiler Compatibility
- Built and tested with **MinGW-w64 GCC 14.2.0**
- Compatible with Qt5 MinGW builds
- Uses Qt5.15.2 mingw81_64 build

## 🚀 Automated Build & Package Script

For the ultimate convenience, use the included PowerShell automation script:

```powershell
# One command to build and package everything!
.\create-package.ps1
```

**This enhanced script automatically:**
- ✅ **Configures** the project in Release mode with dynamic versioning
- ✅ **Generates** timestamped version headers with build date/time
- ✅ **Builds** the application with all dependencies and enhanced messages
- ✅ **Copies** Qt5 and MinGW runtime DLLs (including Qt5Network.dll)
- ✅ **Embeds** the custom icon into the executable with Windows resource
- ✅ **Creates** both timestamped ZIP and NSIS installer packages
- ✅ **Validates** all components and provides detailed progress feedback
- ✅ **Shows** final package information with file sizes and locations

**Enhanced Output Files Created:**
- `build/Chopsticks-Qt-2025-06-25-win64.zip` (~10.9 MB) - **Complete game suite** with timestamped version
- `build/Chopsticks-Qt-2025-06-25-win64.exe` (~9.1 MB) - Professional installer with build date branding
- `build/chopsticks-qt.exe` (180KB) - Enhanced executable showing version `1.2.20250625` at startup

**Build Script Features:**
- 🕐 **Timestamped Packages**: Every build gets unique version identifier
- 📊 **Progress Tracking**: Real-time build status with clear feedback
- ✨ **Enhanced Messages**: Professional user experience throughout
- 🔍 **Quality Validation**: Verifies all components before packaging
- 📦 **Professional Output**: Enterprise-ready distribution packages

## Troubleshooting

### Game Mode Issues

#### **AI Opponent Not Working**
- ✅ Ensure you selected "Single Player vs AI" mode
- ✅ Choose difficulty level (Easy/Medium/Hard)
- ✅ Check that AI is taking turns automatically
- ✅ Rebuild project if AI moves seem incorrect

#### **Network Connection Problems**
- ✅ **Firewall**: Allow port 8080 through Windows Firewall
- ✅ **IP Address**: Verify correct IP address (use `ipconfig` command)
- ✅ **Port**: Ensure both players use the same port number
- ✅ **Local Test**: Try with local IP first (192.168.x.x)
- ✅ **Router**: Configure port forwarding for internet play

#### **Game Mode Selection Issues**
- ✅ Restart application if mode dialog doesn't appear
- ✅ Ensure all required DLLs are present (including Qt5Network.dll)
- ✅ Check that game launches with startup dialog

### Qt5 Not Found Error
If you get "Could not find a package configuration file provided by Qt5":
1. Verify Qt5 with **Network module** is installed at `C:\Qt\5.15.2\mingw81_64\`
2. Update `CMAKE_PREFIX_PATH` in `CMakeLists.txt` if needed
3. Ensure you're using the MinGW build of Qt5
4. **Check Qt5Network.dll** is available in your Qt installation

### Missing DLL Errors
If the application fails to start due to missing DLLs:
1. Rebuild the project - DLLs are copied automatically
2. Check that all **7 DLLs** are present in the `build/` directory (including **Qt5Network.dll**)
3. Verify your Qt installation includes the MinGW runtime and Network module

### Qt Platform Plugin Errors
If you get "Could not find the Qt platform plugin 'windows'":
1. Ensure the `platforms/` directory exists in your build folder
2. Verify `qwindows.dll` is present in `build/platforms/`
3. Rebuild the project to copy platform plugins automatically

### Build Errors
- Ensure CMake 3.10+ is installed
- Verify MinGW-w64 is in your PATH
- Check that Qt5 installation is complete **with Network module**
- Verify all source files are present (including AI and network files)

## 🆕 Enhanced Features & Professional Packaging

### 🔍 **Advanced Debug Information Window** (New!)

This version includes a **professional debug information system** that solves console visibility issues:

**Key Features:**
- 📊 **Large Scrollable Window** (800x600) - No more tiny console windows!
- 📑 **Categorized Tabs**: All Messages, Server Info, Network Events, Game Events
- ⏰ **Timestamped Logs** - Every message includes precise timestamps
- 🔍 **Easy Access** - "Show Debug Info" button right in setup dialog
- 🌐 **Auto-Show** - Automatically appears for network games
- 💾 **Export/Clear** - Save debug logs or reset message history
- 📈 **Status Bar** - Shows message counts per category

**How to Use:**
1. **Manual Access**: Click "🔍 Show Debug Info" in the setup dialog
2. **Automatic**: Debug window appears automatically for network games
3. **During Gameplay**: All server/network/game messages are captured and organized

**Perfect for:**
- **Network Debugging** - See all server/client communication clearly
- **Game Development** - Track AI moves and game state changes  
- **Troubleshooting** - Organized, searchable debug information
- **Professional Deployment** - Clean debug interface for support

### ✨ **Automated Versioning & Timestamping**
This project features **dynamic versioning** that automatically timestamps every build:

```cmake
# Automatic timestamp generation
string(TIMESTAMP BUILD_TIMESTAMP "%Y%m%d" UTC)
string(TIMESTAMP BUILD_DATE "%Y-%m-%d" UTC)
project(chopsticks-qt VERSION 1.2.${BUILD_TIMESTAMP})
```

**Benefits:**
- 📅 **Build Date in Version**: Every build gets unique version (e.g., `1.2.20250625`)
- 🏷️ **Installer Branding**: Packages include build date (e.g., `Chopsticks-Qt-2025-06-25-win64.exe`)
- 📺 **Startup Display**: Application shows build version and timestamp at launch
- 🔍 **Traceability**: Easy identification of build dates for support

**Generated Version Header:**
```cpp
// Auto-generated build/version.h
#define VERSION_STRING "1.2.20250625"
#define BUILD_DATE "2025-06-25"
#define BUILD_TIMESTAMP "2025-06-25 14:30:00 UTC"
```

### 🗣️ **Enhanced User Experience Messages**
Every user interaction has been **professionally enhanced** with clear, friendly messaging:

#### **AI Opponent Messages**
```cpp
// Before: "Computer move"
// After:
🤖 Easy AI thinking: "Hmm, maybe I'll try something random... 🎲"
😐 Medium AI calculating: "Let me find a good strategic move... 🧠"  
😈 Hard AI analyzing: "Optimal move detected. Resistance is futile. 💀"
```

#### **Network Game Messages**
```cpp
// Before: "Connection established"
// After:
🏠 Server Status: "🎉 Game server started! Share IP 192.168.1.100:8080 with friends!"
🔗 Client Status: "✅ Connected to game! Waiting for host to start... 🎮"
📡 Network Event: "🎊 Player joined! Game ready to begin!"
```

#### **Game State Messages**
```cpp
// Before: "Player 1 wins"
// After:
🏆 Victory: "🎉 Congratulations Player 1! 🥳 Outstanding strategy!"
🎯 Turn Prompt: "🤖 AI opponent is thinking... ⏳ (Medium difficulty)"
⚡ Move Result: "💥 Great move! Opponent's hand is now out! 🙌"
```

### 🔧 **Professional Build System**
Enhanced CMake configuration with enterprise-level features:

#### **Intelligent Dependency Management**
```cmake
# Automatic DLL deployment with validation
add_custom_command(TARGET chopsticks-qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/Qt5Network.dll"
    $<TARGET_FILE_DIR:chopsticks-qt>
    COMMENT "📦 Deploying Qt5 Network module for multiplayer support..."
)
```

#### **Dynamic CPack Configuration**
```cmake
# Timestamped installer configuration
set(CPACK_PACKAGE_VERSION "${BUILD_DATE}")
set(CPACK_NSIS_DISPLAY_NAME "Chopsticks Qt Game (${BUILD_DATE})")
set(CPACK_PACKAGE_DESCRIPTION "Built on ${BUILD_DATE} with enhanced features")
```

### 📊 **Build Quality & Status**
Real-time build information and quality metrics:

**Build Output Example:**
```
-- 🔨 Configuring Chopsticks Qt v1.2.20250625
-- 📅 Build Date: 2025-06-25
-- ⏰ Build Time: 2025-06-25 14:30:00 UTC
-- 🎨 Using custom icon: chopsticks-icon.ico
-- 📦 Qt5 Network module: FOUND
-- 🔧 MinGW runtime: READY
-- ✅ Configuration complete!

🏗️ Building enhanced Chopsticks Qt...
📦 Copying Qt5 Network, MinGW runtime DLLs and platform plugins...
🎨 Embedding custom icon into executable...
✨ Build successful! Version 1.2.20250625 ready!

📦 Creating distribution packages...
📁 ZIP Package: Chopsticks-Qt-2025-06-25-win64.zip (10.9 MB)
🎁 NSIS Installer: Chopsticks-Qt-2025-06-25-win64.exe (9.1 MB)
🚀 Professional packages ready for distribution!
```

### 📚 **Comprehensive Documentation**
Auto-generated documentation tracking all improvements:

- **`MESSAGE_IMPROVEMENTS.md`** - Complete log of all user experience enhancements
- **`BUILD_STATUS.md`** - Build system improvements and packaging details  
- **`TIMESTAMP_UPDATE.md`** - Versioning automation and timestamp features
- **`CLEANUP_STATUS.md`** - Project cleanup and organization status

## Technical Specifications

- **Target Platform**: Windows 10+ (Professional packaging)
- **Compiler**: MinGW-w64 GCC 14.2.0 (Optimized build)
- **Qt Version**: 5.15.2 (with Network module + enhanced integration)
- **CMake Version**: 3.10+ (Enhanced configuration)
- **C++ Standard**: C++17 (Modern features)
- **Build System**: CMake with automated timestamping & packaging
- **Game Modes**: 4 total (Local, AI, Network Server, Network Client)
- **AI Levels**: 3 difficulty levels with distinct personalities & enhanced messages
- **Network Protocol**: TCP with JSON messaging + user-friendly status
- **Versioning**: Dynamic timestamping with build date integration
- **Packaging**: Professional NSIS installer + ZIP with custom branding
- **User Experience**: Enhanced messages throughout with emojis & context

---

## 🎯 Quick Start Summary

**For immediate results with enhanced features:**
1. **Install prerequisites**: CMake, MinGW-w64, Qt5 (with Network), NSIS
2. **Run the enhanced automation script**: `.\create-package.ps1`
3. **Get timestamped professional packages**: ZIP (~10.9MB) and installer (~9.1MB) with dynamic versioning

**🎮 Enhanced Game Features:**
- ✅ **4 Game Modes**: Local multiplayer, AI opponent, network server, network client
- ✅ **Smart AI with Personality**: 3 difficulty levels with unique messages and behaviors
- ✅ **Professional Network Gaming**: Real-time multiplayer with enhanced user feedback
- ✅ **Dynamic Versioning**: Every build automatically timestamped (e.g., v1.2.20250625)
- ✅ **Enhanced User Experience**: Friendly messages with emojis and clear context throughout
- ✅ **Complete automation**: Professional dependency management and packaging
- ✅ **Enterprise branding**: Custom chopsticks icon with build date integration
- ✅ **Production-ready**: Professional distribution packages with quality validation

**🤖 AI Personalities with Enhanced Messages:**
- 😊 **Easy**: Learning-friendly with encouraging random moves (30% optimal)
- 😐 **Medium**: Balanced challenge with strategic thinking messages (80% optimal)  
- 😈 **Hard**: Expert-level with intimidating efficiency messages (100% optimal)

**🌐 Network Features with Professional Feedback:**
- 🏠 **Host Games**: Create servers with clear setup instructions and status
- 🔗 **Join Games**: Connect to remote games with helpful connection guidance
- 📡 **Local & Internet**: Support for LAN and worldwide play with troubleshooting tips
- 🔒 **Secure Protocol**: JSON messaging with user-friendly error handling

**⏰ Version & Build Features:**
- 📅 **Automatic Timestamping**: Every build gets unique date-based version
- 🏷️ **Professional Branding**: Installers show build date in name and display
- 📺 **Startup Information**: Application displays version and build timestamp
- 📊 **Quality Tracking**: Complete build documentation and status reporting

**Note**: This project is professionally configured for Windows 10+ with MinGW-w64 and Qt5, featuring automated versioning, enhanced user experience, and enterprise-ready packaging. For other platforms or Qt versions, modifications to the CMakeLists.txt may be required.

**📚 Additional Documentation**: 
- `MESSAGE_IMPROVEMENTS.md` - Details of all user experience enhancements
- `BUILD_STATUS.md` - Build system improvements and packaging information
- `TIMESTAMP_UPDATE.md` - Automatic versioning and timestamp features
- `NETWORK_FEATURES.md` - Detailed network and AI implementation information

**Enjoy the complete enhanced Chopsticks gaming experience!** 🥢✨🎮