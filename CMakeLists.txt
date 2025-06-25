cmake_minimum_required(VERSION 3.10)
project(chopsticks-qt VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt5 installation path
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
# For Qt6, use: find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(chopsticks-qt
    src/chopsticks-qt.cpp
    src/gamewindow.cpp
    src/player.cpp
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
