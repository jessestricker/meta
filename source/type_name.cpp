#include "type_name.hpp"

#ifdef _MSC_VER
  #include <string_view>
#else
  #include <cxxabi.h>

  #include <cstdlib>
#endif

namespace meta {
  std::string detail::demangle_type_name(const char* mangled) {
#ifdef _MSC_VER

    static constexpr std::string_view keywords[] = {"class ", "enum ", "struct ", "union "};

    auto demangled = std::string{mangled};
    for (auto&& keyword : keywords) {
      auto pos = demangled.find(keyword);
      while (pos != std::string::npos) {
        demangled.erase(pos, keyword.size());
        pos = demangled.find(keyword, pos);
      }
    }

    return demangled;

#else

    auto status = 0;
    const auto demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);

    switch (status) {
    case 0: // success
      break;
    case -1: // memory allocation failed
      throw std::bad_alloc{};
    default:
      throw DemangleError{};
    }

    try {
      const auto demangled_str = std::string{demangled};
      ::free(demangled);
      return demangled_str;
    } catch (const std::bad_alloc&) {
      ::free(demangled);
      throw;
    }

#endif
  }

  DemangleError::DemangleError()
      : std::runtime_error{"the internal, ABI-specific demangling function failed"} {
  }
}
