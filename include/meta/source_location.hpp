#ifndef META_SOURCE_LOCATION_HPP
#define META_SOURCE_LOCATION_HPP

#include <ostream>

namespace meta {
  namespace detail {
    constexpr bool is_null_or_empty(const char* c_str) noexcept {
      return c_str == nullptr || c_str[0] == '\0';
    }
  }

  class SourceLocation {
  public:
    constexpr SourceLocation(const char* file, unsigned line) noexcept
        : file_(file)
        , line_(line) {
    }

    constexpr SourceLocation() noexcept = default;

    constexpr const char* file() const noexcept {
      return file_;
    }

    constexpr unsigned int line() const noexcept {
      return line_;
    }

  private:
    const char* file_ = "";
    unsigned line_ = 0;
  };

  template <class Char, class Traits>
  std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const SourceLocation& loc) {
    static constexpr auto unknown = "<unknown>";
    if (detail::is_null_or_empty(loc.file())) {
      os << unknown;
    } else {
      os << loc.file();
    }
    return os << ':' << loc.line();
  }
}

#define META_CURRENT_SOURCE_LOCATION \
  ::meta::SourceLocation {           \
    __FILE__, __LINE__               \
  }

#endif // META_SOURCE_LOCATION_HPP
