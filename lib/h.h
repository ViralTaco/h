#ifndef com_viraltaco_h_h
#define com_viraltaco_h_h "1.0.3"
/// Copyright 2023 viraltaco_ <https://h.viraltaco.com>
#include <numeric>

namespace h::inline v1 {
 inline namespace details {
   using std::size_t;
   using hash_t = unsigned long long;
 } // h::inline v1::inline details

 constexpr auto hash(char const* str, size_t len) noexcept -> hash_t {
   return std::accumulate(str, &str[len], hash_t{}, [](auto h, char8_t c) {
     if (c == '-') { return h; }
     
     h <<= 5;
     switch (c) {
     case '\0':return h | 0b11010; // h bit_or 26
     case '=': return h | 0b11011; // h bit_or 27
     case ',': return h | 0b11101; // h bit_or 29
     case ' ': return h | 0b11110; // h bit_or 30
     default:
      if ('a' <= c and c <= 'z') {
        return h | (c - 'a');
      } else if ('A' <= c and c <= 'Z') {
        return h | (c - 'A');
      } else {
        return h | 0b11111; // h bit_or 31;
      }
     }
   });
 }
 
 template <class CharT, size_t N>
 consteval auto hash(CharT const(&str)[N]) { return h::hash(str, N - 1u); }
 
 inline namespace literals {
   consteval auto operator""_h(char const* str, size_t len) {
     return h::hash(str, len);
   }
 } // h::inline v1::inline literals
} // h::inline v1
#endif // com_viraltaco_h_h
