project(FLUKAMaterial)
cmake_minimum_required(VERSION 2.8.12)

set(TPSDIR ${PROJECT_SOURCE_DIR}/..)

message(${TPSDIR})

if (POLICY CMP0043)
  cmake_policy( SET CMP0043 NEW)
 endif()



link_directories(${TPSDIR}/Lib)

find_package(Qt5 REQUIRED Widgets)
find_package(Qt5 REQUIRED Core)
find_package(Qt5 REQUIRED Gui)
find_package(Qt5 REQUIRED Charts)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(SOURCES main.cpp  material.cpp)
set(HEADERS   material.h)


add_executable(FLUKAMaterial ${SOURCES} ${HEADERS} )
target_link_libraries(FLUKAMaterial Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Charts)
qt5_use_modules(FLUKAMaterial Widgets)
