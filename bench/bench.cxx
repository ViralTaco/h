#include <benchmark/benchmark.h>
#include "../lib/h.h"
#include <string>
#include <string_view>
#include <vector>
#include <random>
#include <mutex>

class HashFixture : public benchmark::Fixture {
public:
  // Using static to share data across all benchmark threads of a run
  static std::vector<std::string> strings;
  static std::once_flag init_flag;

  void SetUp([[maybe_unused]] ::benchmark::State const&) {
    std::call_once(init_flag, [&]() {
      std::random_device rd;
      std::mt19937 gen(rd()); 
      std::uniform_int_distribution<> dis(32, 126); // Printable ASCII

      // Max length in the range
      size_t max_length = 8192;
      size_t pool_size = 10000;
      strings.resize(pool_size);

      for (size_t i = 0; i < pool_size; ++i) {
        std::string s(max_length, ' ');
        for (size_t j = 0; j < max_length; ++j) {
          s[j] = static_cast<char>(dis(gen));
        }
        strings[i] = s;
      }
    });
  }

  void TearDown(const ::benchmark::State& state) {
    if (state.thread_index() == 0) {
      // Benchmark framework clears the object, we don't necessarily need to clear static immediately 
      // but it's good practice if running many different fixtures.
    }
  }
};

std::vector<std::string> HashFixture::strings;
std::once_flag HashFixture::init_flag;

BENCHMARK_DEFINE_F(HashFixture, BM_HashStringView)(benchmark::State& state) {
  std::mt19937 gen(state.thread_index());
  std::uniform_int_distribution<size_t> dis(0, strings.size() - 1);

  for (auto _ : state) {
    // Fuzzing & Random interleaving 
    std::string_view sv = strings[dis(gen)];
    auto hash = h::hash(sv);
    benchmark::DoNotOptimize(hash);
  }
  state.SetBytesProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}
BENCHMARK_REGISTER_F(HashFixture, BM_HashStringView)
  ->RangeMultiplier(8)->Range(8, 8192)
  ->Threads(1)->Threads(4)->Threads(8) // Multithreading
  ->Repetitions(3)->MinTime(0.5) // Reduce variance
  ->Complexity(benchmark::oN);


// Alternate Implementation 1: For-loop (old algorithm)
constexpr h::hash_t hash_old(const std::string_view str) noexcept {
  h::hash_t h = 0X9E3779B9;
  h::hash_t kPrime = 0x517cc1ed;
  for (auto c : str) {
    h = (h * kPrime) ^ c;
  }
  return h;
}

BENCHMARK_DEFINE_F(HashFixture, BM_HashOld)(benchmark::State& state) {
  std::mt19937 gen(state.thread_index());
  std::uniform_int_distribution<size_t> dis(0, strings.size() - 1);

  for (auto _ : state) {
    std::string_view sv = strings[dis(gen)];
    auto hash = hash_old(sv);
    benchmark::DoNotOptimize(hash);
  }
  state.SetBytesProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}
BENCHMARK_REGISTER_F(HashFixture, BM_HashOld)
  ->RangeMultiplier(8)->Range(8, 8192)
  ->Threads(1)->Threads(4)->Threads(8)
  ->Repetitions(3)->MinTime(0.5)
  ->Complexity(benchmark::oN);


// Alternate Implementation 2: FNV-1a (64-bit)
constexpr h::hash_t hash_fnv1a(const std::string_view str) noexcept {
  h::hash_t h = 0xcbf29ce484222325ULL;
  for (char c : str) {
    h ^= static_cast<unsigned char>(c);
    h *= 0x100000001b3ULL;
  }
  return h;
}

BENCHMARK_DEFINE_F(HashFixture, BM_HashFNV1a)(benchmark::State& state) {
  std::mt19937 gen(state.thread_index());
  std::uniform_int_distribution<size_t> dis(0, strings.size() - 1);

  for (auto _ : state) {
    std::string_view sv = strings[dis(gen)];
    auto hash = hash_fnv1a(sv);
    benchmark::DoNotOptimize(hash);
  }
  state.SetBytesProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}
BENCHMARK_REGISTER_F(HashFixture, BM_HashFNV1a)
  ->RangeMultiplier(8)->Range(8, 8192)
  ->Threads(1)->Threads(4)->Threads(8)
  ->Repetitions(3)->MinTime(0.5)
  ->Complexity(benchmark::oN);


// Alternate Implementation 3: djb2
constexpr h::hash_t hash_djb2(const std::string_view str) noexcept {
  h::hash_t h = 5381;
  for (char c : str) {
    h = ((h << 5) + h) + c; /* hash * 33 + c */
  }
  return h;
}

BENCHMARK_DEFINE_F(HashFixture, BM_HashDJB2)(benchmark::State& state) {
  std::mt19937 gen(state.thread_index());
  std::uniform_int_distribution<size_t> dis(0, strings.size() - 1);

  for (auto _ : state) {
    std::string_view sv = strings[dis(gen)];
    auto hash = hash_djb2(sv);
    benchmark::DoNotOptimize(hash);
  }
  state.SetBytesProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}
BENCHMARK_REGISTER_F(HashFixture, BM_HashDJB2)
  ->RangeMultiplier(8)->Range(8, 8192)
  ->Threads(1)->Threads(4)->Threads(8)
  ->Repetitions(3)->MinTime(0.5)
  ->Complexity(benchmark::oN);

BENCHMARK_MAIN();
