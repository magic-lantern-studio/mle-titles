# Stop if cmake version is below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Project name and enable C++ support
project(null LANGUAGES CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify where to find CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(POLICY CMP0072)
  # Get rid of OpenGL GLVND warning from CMake 3.11
  cmake_policy(SET CMP0072 NEW)
endif()

# Fail early if one of the required packages cannot be found
find_package(OpenGL REQUIRED)
include(FindGTK2)
find_package(GTK2 REQUIRED gtk)
include(FindCoin3D)
find_package(Coin3D REQUIRED)
include(FindSoGtk)
find_package(SoGtk REQUIRED)
include(FindMagicLantern)
find_package(MagicLantern REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules (
  GTK_GL2    # variable will be used by cmake
  REQUIRED   # is required mandatory
  gtkgl-2.0  # name of package to be found
)

# Define the executable
add_executable(null "")

# Define the sources
target_sources(
  null
  PRIVATE
    callback.cpp
    main.cpp
    title.cpp
  )

# Specify the build environment
if(MagicLantern_FOUND)
  message(STATUS "Magic Lantern Variables:")
  message(STATUS "    COIN3D_INCLUDE_DIRS=" ${COIN3D_INCLUDE_DIRS})
  message(STATUS "    COIN3D_LIBRARIES=" ${COIN3D_LIBRARIES})
  message(STATUS "    SoGtk_INCLUDE_DIRS=" ${SoGtk_INCLUDE_DIRS})
  message(STATUS "    SoGtk_LIBRARIES=" ${SoGtk_LIBRARIES})
  message(STATUS "    MagicLantern_INCLUDE_DIRS=" ${MagicLantern_INCLUDE_DIRS})
  message(STATUS "    MagicLantern_LIBRARIES=" ${MagicLantern_LIBRARIES})
  include_directories(${MagicLantern_INCLUDE_DIRS} ${COIN3D_INCLUDE_DIRS} ${SoGtk_INCLUDE_DIRS} ${GTK2_INCLUDE_DIRS})
  add_compile_definitions(${MagicLantern_DEFINITIONS})
  target_link_libraries(null ${MagicLantern_LIBRARIES} ${COIN3D_LIBRARIES} ${SoGtk_LIBRARIES} ${GTK2_LIBRARIES})
endif()
