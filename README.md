# Chopsticks Qt - Windows 10 Edition

A Qt-based implementation of the classic Chopsticks finger game built with C++ and Qt5.

## Game Overview

Chopsticks is a simple two-player game that simulates the classic finger game. Players take turns tapping each other's hands to add fingers, trying to eliminate their opponent's hands by reaching five fingers. The game includes features for tapping, bumping, and managing player hands.

### Gameplay Instructions
1. Players start with one finger up on each hand.
2. Decide who goes first.
3. The active player taps the opponent's hand, adding the number of fingers from the tapping hand to the tapped hand.
4. If a hand reaches five fingers, it is out and must be made into a fist.
5. Players can "bump" even numbers to split fingers evenly between their hands.
6. The game continues until one player has both hands out.

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
├── CMakeLists.txt          # Build configuration with automatic DLL deployment
├── CMakePresets.json       # CMake presets
├── README.md              # This file
├── build/                 # Build output directory (auto-generated)
├── resources/             # Resource files
│   └── chopsticks.qrc     # Qt resource file
└── src/                   # Source code
    ├── chopsticks-qt.cpp  # Main application entry point
    ├── gamewindow.cpp     # Game window implementation
    ├── gamewindow.h       # Game window header
    ├── player.cpp         # Player class implementation
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

**Note**: This project is configured specifically for Windows 10 with MinGW-w64 and Qt5. For other platforms or Qt versions, modifications to the CMakeLists.txt may be required.

Enjoy playing Chopsticks!