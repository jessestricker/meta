#include <meta/version.hpp>

#include "catch/catch.hpp"
#include "catch/helpers.hpp"

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
