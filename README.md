# Chopsticks Qt - Windows 10 Edition

A feature-rich Qt-based implementation of the classic Chopsticks finger game with **multiple game modes**: local multiplayer, single-player vs AI, and network multiplayer support!

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

```
chopsticks-qt_Win10/
├── CMakeLists.txt              # Build configuration with Qt Network, AI, automatic DLL deployment & icon embedding
├── CMakePresets.json           # CMake presets
├── README.md                  # This comprehensive documentation
├── NETWORK_FEATURES.md        # Detailed network and AI feature documentation
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
    ├── player.h               # Player class header
    ├── aiplayer.cpp           # AI opponent implementation (3 difficulty levels)
    ├── aiplayer.h             # AI opponent header
    ├── networkmanager.cpp     # Network multiplayer core functionality
    ├── networkmanager.h       # Network multiplayer header
    ├── networkdialog.cpp      # Unified game setup dialog implementation
    └── networkdialog.h        # Game setup dialog header (supports all 4 game modes)
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

## 🌐 Network Multiplayer Setup

### **Local Network Gaming** (Easiest)

#### **Step 1: Host Setup**
1. Launch the game on the host computer
2. Select "🏠 Network Server (Host Game)"
3. Choose a port (default: 12345 works great)
4. Click "Start Server"
5. **Share your local IP** with other players:
   ```
   Example: "Join my game at 192.168.1.100 port 12345"
   ```

#### **Step 2: Join Setup**  
1. Launch the game on the joining computer
2. Select "🔗 Network Client (Join Game)"
3. Enter the host's IP address (e.g., `192.168.1.100`)
4. Enter the port number (e.g., `12345`)
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
1. **Configure router**: Forward TCP port 12345 to host computer's local IP
2. **Find external IP**: Use whatismyip.com or similar service
3. **Start server**: Follow local network steps above
4. **Share external IP**: Give friends your external IP instead of local IP

#### **Join Setup**
1. Get external IP and port from host
2. Follow standard joining steps using external IP
3. Example: Connect to `203.0.113.1` port `12345`

### **Network Troubleshooting**

#### **Connection Issues**
- ✅ **Firewall**: Allow port 12345 through Windows Firewall
- ✅ **IP Address**: Verify correct IP (use `ipconfig` on Windows)  
- ✅ **Port**: Ensure both players use the same port number
- ✅ **Local Test**: Try with local IP first (192.168.x.x)

#### **Router Configuration**
- **Port Forwarding**: TCP port 12345 → host computer's local IP
- **Dynamic IP**: Consider using Dynamic DNS for changing external IPs
- **Multiple Games**: Use different ports for multiple simultaneous games

#### **Network Diagnostics** (Windows)
```powershell
# Test connectivity to server
Test-NetConnection -ComputerName [server-ip] -Port 12345

# Check what ports are listening
netstat -an | Select-String "12345"

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
- `build/Chopsticks-Qt-1.0.0-win64.zip` (~10.9 MB) - **Complete game suite** with all modes
- `build/Chopsticks-Qt-1.0.0-win64.exe` (~9.1 MB) - Professional installer with custom icon
- `build/chopsticks-qt.exe` (180KB) - Enhanced game executable with all features

## Troubleshooting

### Game Mode Issues

#### **AI Opponent Not Working**
- ✅ Ensure you selected "Single Player vs AI" mode
- ✅ Choose difficulty level (Easy/Medium/Hard)
- ✅ Check that AI is taking turns automatically
- ✅ Rebuild project if AI moves seem incorrect

#### **Network Connection Problems**
- ✅ **Firewall**: Allow port 12345 through Windows Firewall
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

## Technical Specifications

- **Target Platform**: Windows 10
- **Compiler**: MinGW-w64 GCC 14.2.0
- **Qt Version**: 5.15.2 (with Network module)
- **CMake Version**: 3.10+
- **C++ Standard**: C++17
- **Build System**: CMake with Unix Makefiles
- **Game Modes**: 4 total (Local, AI, Network Server, Network Client)
- **AI Levels**: 3 difficulty levels with distinct personalities
- **Network Protocol**: TCP with JSON messaging

---

## 🎯 Quick Start Summary

**For immediate results:**
1. **Install prerequisites**: CMake, MinGW-w64, Qt5 (with Network), NSIS
2. **Run the automation script**: `.\create-package.ps1`
3. **Get complete game suite**: ZIP (~10.9MB) and installer (~9.1MB) with custom branding

**🎮 Game Features:**
- ✅ **4 Game Modes**: Local multiplayer, AI opponent, network server, network client
- ✅ **Smart AI**: 3 difficulty levels (Easy, Medium, Hard) with distinct personalities
- ✅ **Network Gaming**: Real-time multiplayer across any distance
- ✅ **Complete automation**: Automatic dependency management and packaging
- ✅ **Professional branding**: Custom chopsticks icon throughout
- ✅ **Production-ready**: Professional distribution packages

**🤖 AI Personalities:**
- 😊 **Easy**: Learning-friendly with random moves (30% optimal)
- 😐 **Medium**: Balanced challenge with smart play (80% optimal)  
- 😈 **Hard**: Expert-level ruthless efficiency (100% optimal)

**🌐 Network Features:**
- 🏠 **Host Games**: Create servers for friends to join
- 🔗 **Join Games**: Connect to remote games anywhere
- 📡 **Local & Internet**: Support for LAN and worldwide play
- 🔒 **Secure Protocol**: JSON messaging with input validation

**Note**: This project is configured specifically for Windows 10 with MinGW-w64 and Qt5. For other platforms or Qt versions, modifications to the CMakeLists.txt may be required.

**📚 Additional Documentation**: See `NETWORK_FEATURES.md` for detailed network and AI implementation information.

**Enjoy the complete Chopsticks gaming experience!** 🥢✨🎮