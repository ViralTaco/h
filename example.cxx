#include <cstring> // std::strlen
#include <fmt/printf.h>
#include "lib/h.h"


int main(int argc, char** argv) {
  if (argc < 2) return EXIT_FAILURE;
  
  
  switch (h::hash(argv[1], std::strlen(argv[1]))) {
    using fmt::print;
    using namespace h::literals;
  case "--version"_h:
    print("com.viraltaco.h v{}\n", com_viraltaco_h_h);
    break;
  case "--help"_h:
  case "-h"_h:
    print("--help");
    break;
  default:
    print("Invalid input: '{}'\n", argv[1]);
    return EXIT_FAILURE;
  }
}
