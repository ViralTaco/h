#include <cstring> // std::strlen
#include <fmt/printf.h>
#include "lib/h.h"


int main(int argc, char** argv) {
	if (argc < 2) return EXIT_FAILURE;
	
	using h::literals::operator""_h;
	using fmt::print;
	
	switch (h::hash(argv[1], std::strlen(argv[1]))) {
	case "--help"_h:
	case "?"_h:
		print("--help");
		break;
	case "--version"_h:
		print("com.viraltaco.h v{}\n", com_viraltaco_h_h);
		break;
	default:
		print("Invalid input: '{}'\n", argv[1]);
		return EXIT_FAILURE;
	}
}
