#include <gtest/gtest.h>
#include "../lib/h.h"
#include <string>
#include <string_view>
#include <random>
#include <vector>

using h::literals::operator""_h;

// Alternate Implementation 1: For-loop (same algorithm)
constexpr h::hash_t hash_for(const std::string_view str) noexcept {
  h::hash_t h = 0X9E3779B9;
  h::hash_t kPrime = 0x517cc1ed;
  for (auto c : str) {
    h = (h * kPrime) ^ c;
  }
  return h;
}

// Alternate Implementation 2: FNV-1a (64-bit)
constexpr h::hash_t hash_fnv1a(const std::string_view str) noexcept {
  h::hash_t h = 0xcbf29ce484222325ULL;
  for (char c : str) {
    h ^= static_cast<unsigned char>(c);
    h *= 0x100000001b3ULL;
  }
  return h;
}

// Alternate Implementation 3: djb2
constexpr h::hash_t hash_djb2(const std::string_view str) noexcept {
  h::hash_t h = 5381;
  for (char c : str) {
    h = ((h << 5) + h) + c; /* hash * 33 + c */
  }
  return h;
}

TEST(HashCoreTest, HandlesEmptyString) {
  EXPECT_EQ(""_h, 5381);
  EXPECT_EQ(h::hash(""), 5381);
  EXPECT_EQ(hash_for(""), 0X9E3779B9ULL);
}

TEST(HashCoreTest, HandlesSingleCharacterAndNulls) {
  auto one_char_hash = [] (char c) {
    auto h = 5381;
    h *= 33;
    h += static_cast<unsigned char>(c);
    return h;
  };
  EXPECT_EQ("a"_h, one_char_hash('a'));
  EXPECT_EQ("\0"_h, one_char_hash('\0')); 
}

TEST(HashCoreTest, HandlesCaseSensitivity) {
  EXPECT_NE("hello"_h, "HELLO"_h);
  EXPECT_NE("hello"_h, "Hoi"_h);
}

TEST(HashCoreTest, LengthDependenceAndEmbeddedNulls) {
  EXPECT_NE("prefix"_h, "prefix_suffix"_h);
  EXPECT_NE(h::hash(std::string_view("a\0b", 3)), h::hash(std::string_view("a\0c", 3)));
}

TEST(HashCoreTest, NonAsciiCharacters) {
  EXPECT_NE("ñ"_h, "n"_h);
  EXPECT_EQ("こんにちは"_h, h::hash("こんにちは"));
}


class ConsistencyTest : public ::testing::TestWithParam<size_t> {};

TEST_P(ConsistencyTest, RandomizedMemoryLayoutConsistency) {
  size_t length = GetParam();
  std::mt19937 gen(42 + length);
  std::uniform_int_distribution<> dis(32, 126); 

  std::vector<char> buffer(length * 2); 
  for (size_t i = 0; i < buffer.size(); ++i) {
    buffer[i] = static_cast<char>(dis(gen));
  }

  // Create a string_view out of the offset middle of the buffer
  // to test hashing unaligned strings/randomized layouts
  std::string_view target_span(buffer.data() + length / 2, length);
  
  // Convert span to a newly heap-allocated string
  std::string target_string(target_span);
  
  // Consistency Check 1: String View vs String
  EXPECT_EQ(h::hash(target_span), h::hash(target_string));
  EXPECT_EQ(hash_for(target_span), hash_for(target_string));
  EXPECT_EQ(hash_fnv1a(target_span), hash_fnv1a(target_string));
  EXPECT_EQ(hash_djb2(target_span), hash_djb2(target_string));

  // Consistency Check 2: h::hash vs imperative loop version
  EXPECT_EQ(h::hash(target_span), hash_djb2(target_span));
  
  // Consistency Check 3: Unique algos generate different hashes
  if (length > 0) {
    EXPECT_NE(h::hash(target_span), hash_fnv1a(target_span));
    EXPECT_EQ(h::hash(target_span), hash_djb2(target_span));
  }
}

INSTANTIATE_TEST_SUITE_P(
  VaryingLengths,
  ConsistencyTest,
  ::testing::Values(0, 1, 8, 16, 64, 512, 1024, 4096, 8192)
);
