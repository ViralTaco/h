cmake_minimum_required(VERSION 3.23)
project(test_libh LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(test_libh lib/h.h tst/test.cxx)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(test_libh PRIVATE fmt::fmt fmt::fmt-header-only)
