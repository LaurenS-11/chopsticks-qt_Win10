cmake_minimum_required(VERSION 3.16)
project(qt_test)

# Use the same Qt setup as the main project
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Create a simple test executable
add_executable(qt_test src/qt_test.cpp)
target_link_libraries(qt_test Qt5::Core Qt5::Widgets)

# Set Windows subsystem
if(WIN32)
    set_target_properties(qt_test PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Copy Qt DLLs to the build directory
if(WIN32)
    # Get Qt installation path
    get_target_property(QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT_WINDEPLOYQT_EXECUTABLE ${QT_QMAKE_EXECUTABLE} PATH)
    set(QT_WINDEPLOYQT_EXECUTABLE "${QT_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    # Copy the required Qt DLLs manually
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/5.15.2/mingw81_64/bin/Qt5Core.dll"
        $<TARGET_FILE_DIR:qt_test>)
    
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/5.15.2/mingw81_64/bin/Qt5Gui.dll"
        $<TARGET_FILE_DIR:qt_test>)
    
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/5.15.2/mingw81_64/bin/Qt5Widgets.dll"
        $<TARGET_FILE_DIR:qt_test>)
    
    # Copy MinGW runtime DLLs
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/Tools/mingw810_64/bin/libgcc_s_seh-1.dll"
        $<TARGET_FILE_DIR:qt_test>)
    
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/Tools/mingw810_64/bin/libstdc++-6.dll"
        $<TARGET_FILE_DIR:qt_test>)
    
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/Tools/mingw810_64/bin/libwinpthread-1.dll"
        $<TARGET_FILE_DIR:qt_test>)

    # Copy Qt platform plugins
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:qt_test>/platforms)
    
    add_custom_command(TARGET qt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Qt/5.15.2/mingw81_64/plugins/platforms/qwindows.dll"
        $<TARGET_FILE_DIR:qt_test>/platforms/)
endif()
