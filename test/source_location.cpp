#include <meta/meta.hpp>
#include <sstream>

#include "catch/catch.hpp"

using namespace Catch::Matchers;

namespace {
  template <class Char, class Obj>
  std::basic_string<Char> to_string(const Obj& obj) {
    auto oss = std::basic_ostringstream<Char>{};
    oss << obj;
    return oss.str();
  }
}

TEST_CASE("SourceLocation: default constructor") {
  const auto loc = meta::SourceLocation{};
  REQUIRE_THAT(loc.file(), Equals(""));
  REQUIRE(loc.line() == 0);
}

TEST_CASE("SourceLocation: explicit constructor") {
  const auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE_THAT(loc.file(), Equals("test.txt"));
  REQUIRE(loc.line() == 12);
}

TEST_CASE("SourceLocation: macro constructor") {
  const auto loc = META_CURRENT_SOURCE_LOCATION;
  REQUIRE_THAT(loc.file(), EndsWith("source_location.cpp"));
  REQUIRE(loc.line() == 30);
}

TEST_CASE("SourceLocation: ostream operator") {
  auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE(to_string<char>(loc) == "test.txt:12");
  REQUIRE(to_string<wchar_t>(loc) == L"test.txt:12");

  loc = meta::SourceLocation{"", 12};
  REQUIRE(to_string<char>(loc) == "<unknown>:12");
  REQUIRE(to_string<wchar_t>(loc) == L"<unknown>:12");

  loc = meta::SourceLocation{nullptr, 12};
  REQUIRE(to_string<char>(loc) == "<unknown>:12");
  REQUIRE(to_string<wchar_t>(loc) == L"<unknown>:12");
}
