#ifndef com_viraltaco_h_h
#define com_viraltaco_h_h "com.viraltaco.h v2.2.0"
/// Copyright 2026 viraltaco_ <https://viraltaco.com/h>
#include <numeric>     // std::reduce
#include <string_view> // std::string_view

namespace h::inline v2 {
 inline namespace details {
  using size_t = decltype (sizeof "size_t");
  using hash_t = unsigned long long;
 } // h::inline v2::inline details

 constexpr auto hash(const std::string_view str) noexcept -> hash_t {
   return std::reduce(str.cbegin(), str.cend(), hash_t{5381},
                      [](auto h, auto c) { return ((h << 5) + h) + c; });
 }
 
 namespace literals {
  consteval auto operator""_h(char const* str, const size_t len) -> hash_t {
    return h::hash(std::string_view{ str, len });
  }
 } // h::inline v2::inline literals
} // h::inline v2
#endif // com_viraltaco_h_h
