cmake_minimum_required(VERSION 3.23)

get_filename_component(lib_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${lib_name}
        LANGUAGES       CXX
        VERSION         2.1.2
        DESCRIPTION     "30 SLOC String hashing")

# Global Settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Common flags for all targets
set(COPTS -Wall -Wextra -Wpedantic -Wunreachable-code -Wredundant-decls)
set(OPTIMIZED_COPTS ${COPTS} -O3 -march=native)

# 1. Target: tests
find_package(fmt QUIET)
add_subdirectory(tests)
add_subdirectory(bench)


# 2. Target: compile and run example.cxx
add_executable(example_bin example.cxx lib/h.h)
set_target_properties(example_bin PROPERTIES OUTPUT_NAME example)

# Custom target to fulfill "compile and run" requirement
add_custom_target(run-example
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/example "--version"
    DEPENDS example_bin
    COMMENT "Building and running example with --version argument"
)

# 3. Target: run tests, then compile, optimized as a dynamic library
# Target to run the tests
add_custom_target(run-tests
    COMMAND tests
    DEPENDS tests
    COMMENT "Running tests..."
)

# Optimized Dynamic Library
# We include lib/h.cxx to provide a translation unit for the shared library.
add_library(h_shared SHARED lib/h.cxx lib/h.h)
# Force test execution before library compilation
add_dependencies(h_shared run-tests)
# Apply optimization flags
target_compile_options(h_shared PRIVATE ${OPTIMIZED_COPTS})

set_target_properties(h_shared PROPERTIES
    OUTPUT_NAME h
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
