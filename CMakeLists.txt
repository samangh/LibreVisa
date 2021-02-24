cmake_minimum_required(VERSION 3.13.4)

# This will allow using MSVC statically
# Requires cmake 3.15.0 and above
if (MSVC)
  cmake_minimum_required(VERSION 3.15.0)

  # The poolicy must be set before project()
  cmake_policy(SET CMP0091 NEW)
endif()

project(librevisa
  VERSION "0.0.20130812"
  DESCRIPTION "Open source VISA implementation"
  LANGUAGES C CXX)

set(NAMESPACE librevisa)

##
## Build options
##

# Set this to OFF to build static libraries
option (BUILD_SHARED_LIBS "Build shared libraries" ON)
option (WITH_USB "With USB support (requires libusb)" OFF)
option (WITH_VXI "With USB support (requires libusb)" OFF)
option (WITH_MDNS "With MDNS support (requires avahi)" OFF)


# MDNS immplies VXI support
if(WITH_MDNS)
  set(WITH_VXI ON)
endif()

if(MSVC)
  # Note: will require any libraries that we use to also be staticaly
  # linked against the same version of the runtim

  # We only use this on MSVC
  option(USE_STATIC_RUNTIME "Statically link against the C++ runtime" OFF)
endif()

##
## Misc
##

# Export compile database for IDEs, needed for QtCreator
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


##
## CMake module paths
##

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

##
## Packages
##

if(WITH_USB)
  find_package(LibUSB)
endif()

if(WITH_MDNS)
endif()

find_package(Boost REQUIRED COMPONENTS regex)

# Use boost statially if making a static library
if(NOT BUILD_SHARED_LIBS)
  set(Boost_USE_STATIC_LIBS ON)
endif()

if (USE_STATIC_RUNTIME)
  set(Boost_USE_STATIC_RUNTIME ON)
endif()

# Configure Boost in Windows
if(MSVC)
  # Target Windows 7 and higher
  add_compile_definitions(_WIN32_WINNT=_WIN32_WINNT_WIN7)

  # Boost tries to use auto linking (i.e. #pragma lib in headers) to tell
  # the compiler what to link to. This does not work properly on
  # Widnows/MSVC.
  add_compile_definitions(BOOST_ALL_NO_LIB)
endif()

##
## Targets/Sources
##

add_subdirectory(src)


##
## Compile options
##

foreach(t visa)
  # Link against MSVC statically if enabled
  if (USE_STATIC_RUNTIME AND MSVC)
    set_property(TARGET ${t} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endforeach()

foreach(t ${TARGETS})
  target_compile_features(${t} PRIVATE cxx_std_17)
endforeach()
