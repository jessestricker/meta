#include "source_location.hpp"

#include <ostream>

#include "util.hpp"

using namespace std::string_view_literals;

namespace meta {
  std::string SourceLocation::to_string() const {
    static constexpr auto unknown = "<unknown>"sv;
    auto oss = util::make_classic_oss();
    oss << (file().empty() ? unknown : file());
    oss << ':' << line();
    return oss.str();
  }

  std::ostream& operator<<(std::ostream& os, const SourceLocation& loc) {
    return os << loc.to_string();
  }
}
