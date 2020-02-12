#ifndef META_TYPE_NAME_HPP
#define META_TYPE_NAME_HPP

#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>

namespace meta {
  namespace detail {
    std::string demangle_type_name(const char* mangled);
  }

  class DemangleError : public std::runtime_error {
  public:
    DemangleError();
  };

  template <class Static>
  std::string type_name() {
    const auto mangled = typeid(Static).name();
    return detail::demangle_type_name(mangled);
  }

  template <class Dynamic>
  std::string type_name(Dynamic&& obj) {
    const auto mangled = typeid(std::forward<Dynamic>(obj)).name();
    return detail::demangle_type_name(mangled);
  }
}

#endif // META_TYPE_NAME_HPP
