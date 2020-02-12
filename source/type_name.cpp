#include "type_name.hpp"

#ifdef _MSC_VER
  #include <cstddef>
  #include <type_traits>
#else
  #include <cxxabi.h>

  #include <cstdlib>
#endif

namespace meta {
  std::string detail::demangle_type_name(const char* mangled) {
#ifdef _MSC_VER

    static const char* keywords[] = {"class ", "enum ", "struct ", "union "};
    static const std::size_t keyword_lengths[] = {6, 5, 7, 6};
    static const auto keywords_count = std::extent<decltype(keywords)>::value;

    auto str = std::string{mangled};
    for (auto i = std::size_t{0}; i < keywords_count; ++i) {
      auto pos = str.find(keywords[i]);
      while (pos != std::string::npos) {
        str.erase(pos, keyword_lengths[i]);
        pos = str.find(keywords[i], pos);
      }
    }
    return str;

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
