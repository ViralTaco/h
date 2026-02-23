include(FetchContent)

fetchcontent_declare(
		googletest
		URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)

# 1. Target: tests
add_executable(tests test.cxx ../lib/h.h)
target_link_libraries(tests PRIVATE gtest_main)
target_compile_options(tests PRIVATE ${COPTS})
