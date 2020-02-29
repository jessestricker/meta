#include <meta/source_location.hpp>
#include <sstream>

#include "catch/catch.hpp"
#include "catch/matchers.hpp"

using namespace Catch::Matchers;

namespace {
  std::string from_stream_to_string(const meta::SourceLocation& obj) {
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

TEST_CASE("SourceLocation: to_string and ostream operator") {
  auto loc = meta::SourceLocation{"test.txt", 12};
  REQUIRE(loc.to_string() == "test.txt:12");
  REQUIRE(from_stream_to_string(loc) == loc.to_string());

  loc = meta::SourceLocation{"", 12};
  REQUIRE(loc.to_string() == "<unknown>:12");
  REQUIRE(from_stream_to_string(loc) == loc.to_string());
}

TEST_CASE("SourceLocation: equality and relational operators") {
  const auto a_1 = meta::SourceLocation{"a", 1};
  const auto a_2 = meta::SourceLocation{"a", 2};
  const auto b_1 = meta::SourceLocation{"b", 1};
  const auto a_1_copy = a_1;

  // equal & not-equal
  REQUIRE_THAT(a_1, is_equal_to(a_1));
  REQUIRE_THAT(a_1, is_equal_to(a_1_copy));
  REQUIRE_THAT(a_1, is_not_equal_to(a_2));
  REQUIRE_THAT(a_1, is_not_equal_to(b_1));

  // file is different
  REQUIRE_THAT(a_1, is_less_than(b_1));

  // line is different
  REQUIRE_THAT(a_1, is_less_than(a_2));

  // both are different, file precedes line
  REQUIRE_THAT(a_2, is_less_than(b_1));
}
