#ifndef META_VERSION_HPP
#define META_VERSION_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

namespace meta {
  struct Version {
    std::size_t major = 0;
    std::size_t minor = 0;
    std::size_t patch = 0;
    std::string pre_release = "";
    std::string build = "";

    [[nodiscard]] bool valid() const;
    [[nodiscard]] std::string to_string() const;
  };

  bool operator==(const Version& lhs, const Version& rhs) noexcept;
  bool operator<(const Version& lhs, const Version& rhs) noexcept;
  bool operator!=(const Version& lhs, const Version& rhs) noexcept;
  bool operator<=(const Version& lhs, const Version& rhs) noexcept;
  bool operator>(const Version& lhs, const Version& rhs) noexcept;
  bool operator>=(const Version& lhs, const Version& rhs) noexcept;

  std::ostream& operator<<(std::ostream& os, const Version& ver);
}

#endif // META_VERSION_HPP
