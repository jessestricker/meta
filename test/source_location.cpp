#include <meta/source_location.hpp>
#include <sstream>

#include "catch/catch.hpp"

using namespace Catch::Matchers;

namespace {
  template <class Obj>
  std::string to_string(const Obj& obj) {
    auto oss = std::ostringstream{};
    oss << obj;
    return oss.str();
  }
}

TEST_CASE("SourceLocation: default constructor") {
  const auto loc = meta::SourceLocation{};
  REQUIRE(loc.file() == "");
  REQUIRE(loc.line() == 0);
}

TEST_CASE("SourceLocation: explicit constructor") {
  const auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE(loc.file() == "test.txt");
  REQUIRE(loc.line() == 12);
}

TEST_CASE("SourceLocation: macro constructor") {
  const auto loc = META_CURRENT_SOURCE_LOCATION;
  REQUIRE_THAT(std::string{loc.file()}, EndsWith("source_location.cpp"));
  REQUIRE(loc.line() == 30);
}

TEST_CASE("SourceLocation: ostream operator") {
  auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE(to_string(loc) == "test.txt:12");

  loc = meta::SourceLocation{"", 12};
  REQUIRE(to_string(loc) == "<unknown>:12");
}
