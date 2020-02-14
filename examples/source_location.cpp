#include <iostream>
#include <meta/source_location.hpp>

void do_log(const meta::SourceLocation& loc, const char* text) {
  std::cout << loc << ": " << text << '\n';
}

#define LOG(text__) do_log(META_CURRENT_SOURCE_LOCATION, text__)

int main() {
  const auto def_src_loc = meta::SourceLocation{};
  std::cout << def_src_loc << '\n';
  std::cout << '\n';

  const auto src_loc = META_CURRENT_SOURCE_LOCATION;
  std::cout << src_loc << '\n';
  std::cout << '\n';

  LOG("example log message");
}
