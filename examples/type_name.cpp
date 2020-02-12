#include <iostream>
#include <meta/type_name.hpp>

namespace {
  struct InAnonymousNs {};
}

inline namespace example {
  struct InNamespace {};
}

struct Struct {};
class Class {};
union Union {};
enum Enum {};
enum class EnumClass {};

template <class T>
class TypeTemplate {};

template <unsigned N>
class ValueTemplate {};

struct Base {
  virtual ~Base() = default;
};

struct Derived : Base {};

int main() {
  // static
  std::cout << meta::type_name<int>() << '\n';
  std::cout << meta::type_name<InAnonymousNs>() << '\n';
  std::cout << meta::type_name<InNamespace>() << '\n';
  std::cout << meta::type_name<Struct>() << '\n';
  std::cout << meta::type_name<Class>() << '\n';
  std::cout << meta::type_name<Union>() << '\n';
  std::cout << meta::type_name<Enum>() << '\n';
  std::cout << meta::type_name<EnumClass>() << '\n';
  std::cout << meta::type_name<TypeTemplate<int>>() << '\n';
  std::cout << meta::type_name<ValueTemplate<42>>() << '\n';
  std::cout << '\n';

  // dynamic
  Base* ptr = new Derived();
  std::cout << meta::type_name(ptr) << '\n';
  std::cout << meta::type_name(*ptr) << '\n';
  delete ptr;
}
