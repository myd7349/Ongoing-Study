// clang-format off
#include <exception>
#include <iostream>
#include <string_view>

#include <simdjson/jsonioutil.h>
#include <simdjson/jsonparser.h>
// clang-format on

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Usage: print_json <file1> ...\n";
    return 0;
  }

  for (int i = 1; i < argc; ++i) {
    try {
      std::cout << ">> " << argv[i] << ":\n";

      auto json = simdjson::get_corpus(argv[i]);
      auto document = simdjson::build_parsed_json(json.data(), json.length());
      document.print_json(std::cout);

      std::cout << '\n';
    } catch (const std::exception &exc) {
      std::cerr << "Failed to load \"" << argv[i] << "\": " << exc.what()
                << '\n';
    }
  }

  return 0;
}
