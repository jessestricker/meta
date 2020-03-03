#include <meta/version.hpp>

#include "catch/catch.hpp"
#include "catch/helpers.hpp"
#include "catch/matchers.hpp"

TEST_CASE("Version: constructor and getters") {
  const auto def = meta::Version{};
  REQUIRE(def.major == 0);
  REQUIRE(def.minor == 0);
  REQUIRE(def.patch == 0);
  REQUIRE(def.pre_release.empty());
  REQUIRE(def.build.empty());

  const auto exp = meta::Version{1, 2, 3, "alpha", "123456"};
  REQUIRE(exp.major == 1);
  REQUIRE(exp.minor == 2);
  REQUIRE(exp.patch == 3);
  REQUIRE(exp.pre_release == "alpha");
  REQUIRE(exp.build == "123456");
}

TEST_CASE("Version: to_string and ostream operator") {
  const auto ver = meta::Version{1, 2, 3, "alpha", "123456"};
  const auto str = "1.2.3-alpha+123456";
  REQUIRE(ver.to_string() == str);
  REQUIRE(from_stream_to_string(ver) == str);
}

TEST_CASE("Version: equality operators") {
  const auto def = meta::Version{};
  REQUIRE_THAT(def, is_equal_to(def));

  const auto exp = meta::Version{1, 2, 3, "alpha", "123456"};
  REQUIRE_THAT(exp, is_equal_to(exp));

  REQUIRE_THAT(def, is_not_equal_to(exp));

  const auto exp_copy = exp;
  REQUIRE_THAT(exp, is_equal_to(exp_copy));
}

TEST_CASE("Version: relational operators") {
  REQUIRE_THAT((meta::Version{0, 0, 0}), is_less_than(meta::Version{1, 0, 0}));
  REQUIRE_THAT((meta::Version{0, 0, 0}), is_less_than(meta::Version{0, 1, 0}));
  REQUIRE_THAT((meta::Version{0, 0, 0}), is_less_than(meta::Version{0, 0, 1}));
  REQUIRE_THAT((meta::Version{0, 0, 0, "a"}), is_less_than(meta::Version{0, 0, 0, "b"}));
  REQUIRE_THAT((meta::Version{0, 0, 0, "", "1"}), is_less_than(meta::Version{0, 0, 0, "", "2"}));
}
