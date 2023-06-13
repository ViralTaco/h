#include "../lib/h.h"
#include <fmt/core.h>

auto main() -> int {
  using h::literals::operator ""_h;
  using fmt::print, fmt::arg;
#define PRINT_h(STR)                                                           \
  print("\"{}\"_h{x:^{w}}{h:#x}\n{x:^33}{h:>64b}\n", STR,                      \
    arg("x", ' '), arg("w", 30u - sizeof STR), arg("h", STR##_h));             \
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
  static_assert ("hello"_h == "HELLO"_h);
  static_assert ("hello"_h == h::hash("hello"));
}
