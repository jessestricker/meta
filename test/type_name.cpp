#include <meta/meta.hpp>

#include "catch/catch.hpp"

using namespace Catch::Matchers;

struct Struct {};
class Class {};
union Union {};
enum Enum {};
enum class EnumClass {};
template <class T>
class Template {};

TEST_CASE("type_name: static types") {
  REQUIRE(meta::type_name<int>() == "int");
  REQUIRE(meta::type_name<Struct>() == "Struct");
  REQUIRE(meta::type_name<Class>() == "Class");
  REQUIRE(meta::type_name<Union>() == "Union");
  REQUIRE(meta::type_name<Enum>() == "Enum");
  REQUIRE(meta::type_name<EnumClass>() == "EnumClass");
  REQUIRE(meta::type_name<Template<int>>() == "Template<int>");
}

struct Base {
  virtual ~Base() = default;
};

struct Derived : Base {};

TEST_CASE("type_name: dynamic types") {
  Base* ptr = new Derived();
  REQUIRE_THAT(meta::type_name(ptr), Matches(".*Base\\s*\\*.*"));
  REQUIRE(meta::type_name(*ptr) == "Derived");
  delete ptr;
}
