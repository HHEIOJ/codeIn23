cmake_minimum_required(VERSION 3.0)

project(readFluka)

# Set CMake to use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and include Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Set the source files for your project
set(SOURCES
    cflukadose.cpp
    externdata.cpp
    main.cpp
)

# Set the header files for your project
set(HEADERS
    cflukadose.h
    externdata.h
)

# Set your include directories
set(TPSDIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${TPSDIR}/Include)

# Set your library directories and link libraries
link_directories(${TPSDIR}/Lib)
link_libraries(alglogger)

# Create the executable
add_executable(readFluka ${SOURCES} ${HEADERS})

# Link Qt5 libraries
target_link_libraries(readFluka Qt5::Core Qt5::Gui Qt5::Widgets)

