#include "../lib/h.h" // h{ hash, literals::operator ""_h }
#include <print>      // std::print

int main(int argc, char **argv) {
  if (argc < 2) return EXIT_FAILURE;

  switch (auto arg = argv[1]; h::hash(arg)) {
      using std::println;
      using namespace h::literals;
    case "--version"_h:
    case "-v"_h:
      println("{}", com_viraltaco_h_h);
      break;
    case "--help"_h:
    case "-h"_h:
      println("--help");
      break;
    default:
      println("Invalid input"); //: '{}'", arg);
      return EXIT_FAILURE;
  }
}
