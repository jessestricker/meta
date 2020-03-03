#include <iostream>
#include <meta/version.hpp>

int main() {
  std::cout << std::boolalpha;

  const auto ver = meta::Version{0, 1, 0, "alpha.1", "32041"};
  std::cout << "version: " << ver << '\n';
  std::cout << "valid: " << ver.valid() << '\n';
}
