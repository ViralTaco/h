#ifndef com_viraltaco_h_h
#define com_viraltaco_h_h "com.viraltaco.h v2.1.2"
/// Copyright 2026 viraltaco_ <https://viraltaco.com/h>
#include <numeric>     // std::reduce
#include <string_view> // std::string_view

namespace h::inline v2 {
 inline namespace details {
  using size_t = decltype (sizeof "size_t");
  using hash_t = unsigned long long;
 } // h::inline v2::inline details

 constexpr auto hash(const std::string_view str) noexcept -> hash_t {
   enum: hash_t { kOffset = 0X9E3779B9 , kPrime = 0x517cc1ed };

   return std::reduce(str.cbegin(), str.cend(), hash_t{ kOffset }
                     , [] (auto h, auto c) { return (h * kPrime) ^ c; });
 }
 
 namespace literals {
  consteval auto operator""_h(char const* str, const size_t len) -> hash_t {
    return h::hash(std::string_view{ str, len });
  }
 } // h::inline v2::inline literals
} // h::inline v2
#endif // com_viraltaco_h_h
