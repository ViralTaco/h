#include "../lib/h.h"
#include <fmt/core.h>

auto main() -> int {
  using h::literals::operator ""_h;
  using fmt::print, fmt::arg;
#define PRINT_h(STRING)                               \
   print("\"{}\"_h{:^{w}}{h_:#x}\n", STRING, ' ',\
    arg("w", 30ull - sizeof (STRING)), arg("h_", STRING##_h))

  PRINT_h("Hello");
  PRINT_h("HELLO");
  PRINT_h("Hi");
  PRINT_h("Lorem Ipsum Dolor");
  PRINT_h("--help");
  PRINT_h("--help license");
  PRINT_h("--license");
  PRINT_h("--");
  PRINT_h("Hello, World!");
#undef PRINT_h
}
