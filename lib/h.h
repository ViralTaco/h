#ifndef com_viraltaco_libh_header_included
#define com_viraltaco_libh_header_included() "0.1.1"
/// Copyright 2023 viraltaco_ https://h.viraltaco.com
#include <numeric>

namespace h::inline v1 {
inline namespace details {
using std::size_t;
using hash_t = unsigned long long;
static_assert (8 <= sizeof (hash_t));
}  // namespace details

constexpr auto hash(char const* str, size_t len) noexcept -> hash_t {
  return std::accumulate(str, str + len, hash_t{}, [](hash_t h_, char8_t c) {
    h_ = h_ << 5;
    if ('a' <= c and c <= 'z')
      return h_ | (c - 'a');
    else if ('A' <= c and c <= 'Z')
      return h_ | (c - 'A');
    else switch (c) {
      case ' ': return h_ | 27;
      case ',': return h_ | 29;
      case '-': return h_ | 28;
      case '?': return h_ | 30;
      default:  return h_ | 31;
    }
  });
}

template <class CharT, size_t N>
consteval auto hash(CharT const (&str)[N]) {
  return h::hash(str, N - 1UL);
}

inline namespace literals {
consteval auto operator""_h(char const* str, size_t len) {
  return h::hash(str, len);
}

static_assert("hello"_h != "Hoi"_h, "Error: Wrong Match.");
static_assert("hello"_h == "HELLO"_h, "Error: Case Sensitivity.");
static_assert("hello"_h == h::hash("hello"), "Error: operator \"\"_h.");
}  // namespace literals
}  // namespace h::inline v1

#endif
