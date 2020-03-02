#include <meta/source_location.hpp>

#include "catch/catch.hpp"
#include "catch/helpers.hpp"

using namespace Catch::Matchers;

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
  REQUIRE(loc.line() == 21);
}

TEST_CASE("SourceLocation: to_string and ostream operator") {
  auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE(loc.to_string() == "test.txt:12");
  REQUIRE(from_stream_to_string(loc) == loc.to_string());

  loc = meta::SourceLocation{"", 12};
  REQUIRE(loc.to_string() == "<unknown>:12");
  REQUIRE(from_stream_to_string(loc) == loc.to_string());
}
