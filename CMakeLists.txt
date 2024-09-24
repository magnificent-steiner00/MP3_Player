cmake_minimum_required(VERSION 3.16)

project(MP3_Player VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

# Set include directories (where header files are located)
include_directories(${CMAKE_SOURCE_DIR}/include)

# List the sources and headers, using separate directories for organization
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui  # The .ui file, located in the project root or another directory
)

# Add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MP3_Player
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(MP3_Player SHARED ${PROJECT_SOURCES})
    else()
        add_executable(MP3_Player ${PROJECT_SOURCES})
    endif()
endif()

# Link against the necessary Qt libraries
target_link_libraries(MP3_Player PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# Installation settings
set_target_properties(MP3_Player PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MP3_Player
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MP3_Player)
endif()
