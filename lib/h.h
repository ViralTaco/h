#ifndef com_viraltaco_h_h
#define com_viraltaco_h_h "0.2.0"
/// Copyright 2023 viraltaco_ <https://h.viraltaco.com>
#include <numeric>

namespace h::inline v1 {
 inline namespace details {
  using std::size_t;
  using hash_t = unsigned long long;
 } // namespace h::inline v1::inline details
 
 constexpr auto hash(char const* str, size_t len) noexcept -> hash_t {
   return std::accumulate(str, str + len, hash_t{}, [](hash_t h, char8_t c) {
     h <<= 5;
     if ('a' <= c and c <= 'z')
       return h | (c - 'a');
     else if ('A' <= c and c <= 'Z')
       return h | (c - 'A');
     else switch (c) {
       case '\0':return h | 26; // 0b11010
       case '=': return h | 27; // 0b11011
       case '-': return h | 28; // 0b11100
       case ',': return h | 29; // 0b11101
       case ' ': return h | 30; // 0b11110
       default:  return h | 31; // 0b11111
     }
   }) - (3 * len);
 }
 
 template <class CharT, size_t N>
 consteval auto hash(CharT const(&str)[N]) {
   return h::hash(str, N - sizeof '\0');
 }
 
 inline namespace literals {
  consteval auto operator""_h(char const* str, size_t len) {
    return h::hash(str, len);
  }
 
  static_assert ("hello"_h != "Hoi"_h);
  static_assert ("hello"_h == "HELLO"_h);
  static_assert ("hello"_h == h::hash("hello"));
 }  // namespace h::inline v1::inline literals
}  // namespace h::inline v1
#endif // com_viraltaco_h_h
