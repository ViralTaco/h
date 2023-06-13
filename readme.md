<div class="d-flex mb-3 px-3 px-md-4 px-lg-5">
  <div class="flex-auto min-width-0 width-fit mr-3">
      <h1 class="d-flex flex-wrap flex-items-center break-word f3 text-normal">
        <span itemprop="name" class="ml-2 flex-self-stretch">h</span>
        <span class="mr-2 flex-self-stretch">
          <a class="flex-shrink-0 d-none d-md-inline"
             href="https://travis-ci.com/ViralTaco/h">
            <img src="https://travis-ci.com/ViralTaco/h.svg?branch=master">
          </a>
        </span>  
      </h1>
    </div>
  </div>
Switch on string constants!

## Getting Started

### Prerequisites

* [CMake](https://cmake.org)
* git

### Installing

#### As a library:

Coming if anybody asks.

#### Adding it to your code:

Download [h.h](/lib/h.h). Add it to you project.
For example in a folder named `include`.

Include the header to your .cpp file containing you main function.

```c++
#include "include/h.h" // h::hash, h::operator ""_h
// ...

int main(int argc, char** argv) {
  switch (h::hash(argv[1], std::strlen(argv[1]))) {
    using namespace h::literals;
  case "foo"_h:
    // ...
  case "bar"_h:
    // ...
  }
}

```

### Example

For a full example check out [example.cpp](./example.cpp).

```c++
#include <cstring>     // std::strlen
#include <cstdio>      // std::printf
#include "include/h.h" // h::hash, h::operator ""_h

int main(int argc, char** argv) {
  using namespace h::literals;
  
  if (argc < 2) return EXIT_FAILURE;
  
  switch (h::hash(argv[1], std::strlen(argv[1]))) {
  case "--version"_h:
    std::printf("com.viraltaco.h v%s\n", com_viraltaco_h_h);
    break;
  case "--help"_h:
  case "-h"_h:
    std::printf("--help\n");
    break;
  default:
    std::printf("Invalid input: '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }
}

```

## Running the tests

Run the CMake project `test_libh`.  
Or compile and run `./tst/test.cxx`.

## Deployment

This library is provided as-is. Use at your own discretion.

## Contributing

1. Fork
2. Code (if you add a feature don't forget to write tests for it)
3. Test
4. Add and commit (if possible: each file individually)
5. Push to your remote
6. Make a pull request on this repo.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available,
see
the [tags on this repository](https://github.com/ViralTaco/h/tags).

## Authors

* **Anthony Capobianco** - *Initial work* -
  [viraltaco_](https://github.com/ViralTaco)

See also the list
of [contributors](https://github.com/your/project/contributors) who participated
in this project.

## License

This project is licensed under the MIT License -
see [MIT](https://opensource.org/licenses/MIT) for more information.

## Acknowledgments

* [PurpleBooth](https://github.com/PurpleBooth/) for
  their `README.md` [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
