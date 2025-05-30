# Stop if cmake version is below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Project name and enable C++ support
project(null VERSION 1.0.0 LANGUAGES CXX)

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

# Check for Magic Lantern environment variables
if (DEFINED ENV{MLE_ROOT})
  message(STATUS "MLE_ROOT=" $ENV{MLE_ROOT})
else()
  message(STATUS "MLE_ROOT NOT SET")
  set(ENV{MLE_ROOT} "/opt/MagicLantern")
  message(STATUS "Using " $ENV{MLE_ROOT})
endif()
if (DEFINED ENV{MLE_WORKPRINTS})
  message(STATUS "MLE_WORKPRINTS=" $ENV{MLE_WORKPRINTS})
else()
  message(STATUS "MLE_WORKPRINTS NOT SET")
  set(ENV{MLE_ROOT} "/opt/MagicLantern/include/workprints")
  message(STATUS "Using " $ENV{MLE_WORKPRINTS})
endif()

# Define the executable
add_executable(null "")

# Define the sources for the title executable
target_sources(
  null
  PRIVATE
    main.cpp
    callback.cpp
    title.cpp)

# Define a local library for the title; used for library dependencies
# while linking the executable.
add_library(nullTitle SHARED
  gen/mlchunk.cxx
  gen/mltables.cxx)

# Specify the build environment
if(MagicLantern_FOUND)
  message(STATUS "Magic Lantern Variables:")
  message(STATUS "    MLE_ROOT=" $ENV{MLE_ROOT})
  message(STATUS "    MLE_WORKPRINTS=" $ENV{MLE_WORKPRINTS})
  message(STATUS "    COIN3D_INCLUDE_DIRS=" ${COIN3D_INCLUDE_DIRS})
  message(STATUS "    COIN3D_LIBRARIES=" ${COIN3D_LIBRARIES})
  message(STATUS "    SoGtk_INCLUDE_DIRS=" ${SoGtk_INCLUDE_DIRS})
  message(STATUS "    SoGtk_LIBRARIES=" ${SoGtk_LIBRARIES})
  message(STATUS "    MagicLantern_INCLUDE_DIRS=" ${MagicLantern_INCLUDE_DIRS})
  message(STATUS "    MagicLantern_LIBRARIES=" ${MagicLantern_LIBRARIES})

  # Specify the include directories for the header files
  include_directories(
    gen
    $ENV{MLE_ROOT}/include
    ${MagicLantern_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIRS}
    ${SoGtk_INCLUDE_DIRS}
    ${GTK2_INCLUDE_DIRS})

  # Specify the compiler macro definitions
  add_compile_definitions(
    ${MagicLantern_DEFINITIONS}
    MLE_DIGITAL_PLAYPRINT
    MLE_NOT_UTIL_DLL
    MLE_NOT_MATH_DLL
    MLE_NOT_RUNTIME_DLL
    MLE_NOT_IVSTAGE_DLL
    MLE_NOT_2DSET_DLL)

  # Specify the title executable link options
  target_link_options(null PRIVATE
    -L$ENV{MLE_ROOT}/lib
    -L$ENV{MLE_ROOT}/lib/mle/runtime)

  # Specify the title executable link libraries
  target_link_libraries(null
    nullTitle
    $ENV{MLE_ROOT}/lib/mle/runtime/MleIvStage.so
    $ENV{MLE_ROOT}/lib/mle/runtime/Mle2dSet.so
    ${MagicLantern_LIBRARIES}
    nullTitle
    mlloaders
    playprint
    mlmath
    mlutil
    ${COIN3D_LIBRARIES}
    ${SoGtk_LIBRARIES}
    ${GTK2_LIBRARIES})

endif()
