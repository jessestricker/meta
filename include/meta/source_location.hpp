#ifndef META_SOURCE_LOCATION_HPP
#define META_SOURCE_LOCATION_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <string_view>

namespace meta {
  class SourceLocation {
  public:
    constexpr SourceLocation() noexcept = default;

    constexpr SourceLocation(std::string_view file, std::size_t line) noexcept
        : file_(file)
        , line_(line) {
    }

    [[nodiscard]] constexpr std::string_view file() const noexcept {
      return file_;
    }

    [[nodiscard]] constexpr std::size_t line() const noexcept {
      return line_;
    }

    [[nodiscard]] std::string to_string() const;

  private:
    std::string_view file_ = "";
    std::size_t line_ = 0;
  };

  std::ostream& operator<<(std::ostream& os, const SourceLocation& loc);
}

#define META_CURRENT_SOURCE_LOCATION \
  ::meta::SourceLocation {           \
    __FILE__, __LINE__               \
  }

#endif // META_SOURCE_LOCATION_HPP
