#include "../lib/h.h"
#include <print>

auto main() -> int {
  using h::literals::operator ""_h;
#define PRINT_h(STR)                                            \
  std::print("\"{0}\"_h{1:^{2}}{3:#x}\n{1:^33}{3:>64b}\n", STR, \
    ' ', 30u - sizeof STR, STR##_h);                            \
  static_assert (__LINE__, "Semicolon Required.")
  
  PRINT_h("Hello");
  PRINT_h("HELLO");
  PRINT_h("Hi");
  PRINT_h("Lorem Ipsum Dolor");
  PRINT_h("help");
  PRINT_h("-help");
  PRINT_h("--help");
  PRINT_h("--help license");
  PRINT_h("--license");
  PRINT_h("--");
  PRINT_h("Hello, World!");
#undef PRINT_h
  static_assert ("hello"_h != "Hoi"_h);
  static_assert ("hello"_h != "HELLO"_h); // CASE SENSITIVE IN V2
  static_assert ("hello"_h == h::hash("hello"));
}
