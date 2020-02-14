#include "source_location.hpp"

#include <ostream>
#include <sstream>

namespace meta {
  std::string SourceLocation::to_string() const {
    static constexpr auto unknown = std::string_view{"<unknown>"};
    auto oss = std::ostringstream{};
    oss << (file().empty() ? unknown : file());
    oss << ':' << line();
    return oss.str();
  }

  std::ostream& operator<<(std::ostream& os, const SourceLocation& loc) {
    return os << loc.to_string();
  }
}
