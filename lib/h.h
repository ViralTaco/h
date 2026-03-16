#ifndef com_viraltaco_h_h
#define com_viraltaco_h_h "com.viraltaco.h v" "2.3.1"
/// Copyright 2026 viraltaco_ <https://viraltaco.com/h>
#include <numeric>     // std::accumulate
#include <string_view> // std::string_view

namespace h::inline v2 {
 inline namespace details {
  using size_t = decltype (sizeof "size_t");
  using hash_t = unsigned long long;
 } // h::inline v2::inline details

 constexpr auto hash(const std::string_view str) noexcept -> hash_t {
  // DJB2
  return std::accumulate(str.cbegin(), str.cend(), static_cast<hash_t>(5381),
                         [](auto h, unsigned char c) { return ((h << 5) + h) + c; });
 }
 
 namespace literals {
  consteval auto operator""_h(char const* str, const size_t len) -> hash_t {
    return h::hash(std::string_view{ str, len });
  }
 } // h::inline v2::literals
} // h::inline v2
#endif // com_viraltaco_h_h
