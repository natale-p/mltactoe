# Works with 3.14 and tested through 3.28
cmake_minimum_required(VERSION 3.14...3.28)

# Project name and a few useful settings. Other commands can pick up the results
project(
  mltactoe
  VERSION 0.1
  DESCRIPTION "MLTacToe: awesome ML for Tic Tac Toe"
  LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# Add additional CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
 find_package(GTest)
 if(GTEST_FOUND)
   message(STATUS "GTest found, enabling tests")
   enable_testing()
   add_subdirectory(tests)
 else()
   message(STATUS "GTest not found, tests will not be built")
 endif()

 add_custom_target(
     format
     COMMAND clang-format
         -style=file
         -i
         -assume-filename=${CMAKE_SOURCE_DIR}/.clang-format
         ${CMAKE_SOURCE_DIR}/include/mltactoe/*.h
         ${CMAKE_SOURCE_DIR}/src/*.cpp
         ${CMAKE_SOURCE_DIR}/apps/*.cpp
     COMMENT "Running clang-format on source files"
 )

# Add a custom target to run clang-tidy
add_custom_target(
    tidy
    COMMAND clang-tidy
        --enable-check-profile
        -p ${CMAKE_BINARY_DIR}
        -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/apps/*.cpp
    COMMENT "Running clang-tidy on source files"
)

endif()
