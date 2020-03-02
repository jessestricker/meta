#ifndef META_UTIL_HPP
#define META_UTIL_HPP

#include <locale>
#include <sstream>

namespace meta::util {
  /// Creates an output string stream, with the classic locale imbued.
  /// \return A new output string stream.
  inline auto make_classic_oss() {
    auto oss = std::ostringstream{};
    oss.imbue(std::locale::classic());
    return oss;
  }
}

#endif // META_UTIL_HPP
