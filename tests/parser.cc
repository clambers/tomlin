#include <parser.hh>

#include <exception>
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv) {
  try {
    toml::parser parser(argv[1]);
    parser.parse();
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
