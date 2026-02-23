include(FetchContent)

fetchcontent_declare(
		googlebenchmark
		GIT_REPOSITORY https://github.com/google/benchmark.git
		GIT_TAG v1.8.3
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_EXCEPTIONS ON CACHE BOOL "" FORCE)

fetchcontent_makeavailable(googlebenchmark)

# 4. Target: benchmarks
add_executable(benchmarks bench.cxx ../lib/h.h)
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)
target_compile_options(benchmarks PRIVATE ${OPTIMIZED_COPTS})
