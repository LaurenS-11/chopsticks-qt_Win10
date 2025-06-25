cmake_minimum_required(VERSION 3.10)
project(chopsticks-qt VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt5 installation path
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
# For Qt6, use: find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Configure Windows resource file for icon embedding (if available)
if(WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/app.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/app.rc"
        @ONLY
    )
    set(RESOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/app.rc")
else()
    set(RESOURCE_FILES "")
endif()

add_executable(chopsticks-qt
    src/chopsticks-qt.cpp
    src/gamewindow.cpp
    src/player.cpp
    ${RESOURCE_FILES}
)

target_link_libraries(chopsticks-qt Qt5::Widgets)
# For Qt6, use: target_link_libraries(chopsticks-qt Qt6::Widgets)

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

set_property(TARGET chopsticks-qt PROPERTY CXX_STANDARD 17)

# CPack configuration for creating installers
set(CPACK_PACKAGE_NAME "Chopsticks-Qt")
set(CPACK_PACKAGE_VENDOR "Chopsticks Qt Developer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Classic Chopsticks finger game built with Qt5")
set(CPACK_PACKAGE_DESCRIPTION "A Qt-based implementation of the classic Chopsticks finger game with modern UI and automatic dependency deployment.")
set(CPACK_PACKAGE_EXECUTABLES "chopsticks-qt" "Chopsticks Game")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

# Windows-specific installer settings
if(WIN32)
    set(CPACK_GENERATOR "NSIS;ZIP")  # Creates both NSIS installer and ZIP package
    set(CPACK_NSIS_DISPLAY_NAME "Chopsticks Qt Game")
    set(CPACK_NSIS_PACKAGE_NAME "Chopsticks Qt Game")
    set(CPACK_NSIS_CONTACT "chopsticks.qt@example.com")
    set(CPACK_NSIS_HELP_LINK "https://github.com/yourusername/chopsticks-qt")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/yourusername/chopsticks-qt")
    set(CPACK_NSIS_MODIFY_PATH OFF)
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN "chopsticks-qt.exe")
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Chopsticks Game.lnk' '$INSTDIR\\\\chopsticks-qt.exe'"
    )
    set(CPACK_NSIS_DELETE_ICONS_EXTRA
        "Delete '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Chopsticks Game.lnk'"
    )
    # Optional: Create desktop shortcut
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "CreateShortCut '$DESKTOP\\\\Chopsticks Game.lnk' '$INSTDIR\\\\chopsticks-qt.exe'"
    )
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "Delete '$DESKTOP\\\\Chopsticks Game.lnk'"
    )
endif()

# Install the executable
install(TARGETS chopsticks-qt
    RUNTIME DESTINATION .
    COMPONENT Runtime
)

# Install the DLLs
install(FILES
    "${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll"
    "${CMAKE_PREFIX_PATH}/bin/Qt5Gui.dll"
    "${CMAKE_PREFIX_PATH}/bin/Qt5Widgets.dll"
    "${CMAKE_PREFIX_PATH}/bin/libgcc_s_seh-1.dll"
    "${CMAKE_PREFIX_PATH}/bin/libstdc++-6.dll"
    "${CMAKE_PREFIX_PATH}/bin/libwinpthread-1.dll"
    DESTINATION .
    COMPONENT Runtime
)

# Install platform plugins
install(FILES
    "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll"
    DESTINATION platforms
    COMPONENT Runtime
)

# Set custom icon for installer (when available)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "chopsticks-qt.exe")
    # Set installer icon
    set(CPACK_NSIS_INSTALLER_ICON_CODE "!define MUI_ICON \\\"${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico\\\"")
    set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "!define MUI_UNICON \\\"${CMAKE_CURRENT_SOURCE_DIR}/resources/chopsticks-icon.ico\\\"")
    message(STATUS "Using custom icon for installer: chopsticks-icon.ico")
else()
    message(STATUS "Custom icon not found, using default installer icon")
endif()

# Include CPack
include(CPack)
