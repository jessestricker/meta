#include "version.hpp"

#include <iostream>
#include <locale>
#include <ostream>
#include <regex>
#include <string_view>
#include <tuple>

#include "util.hpp"

namespace {
  using namespace std::string_view_literals;

  // patterns taken from https://semver.org/#is-there-a-suggested-regular-expression-regex-to-check-a-semver-string,
  // the second one without the named groups

  inline constexpr auto pre_release_pattern
      = R"((?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*)"sv;
  inline constexpr auto build_pattern = R"([0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*)"sv;

  auto make_regex(std::string_view pattern) {
    auto regex = std::regex{};
    regex.imbue(std::locale::classic());
    try {
      regex.assign(pattern.begin(), pattern.end(), std::regex::optimize);
    } catch (const std::regex_error& ex) {
      std::terminate();
    }
    return regex;
  }

  bool match_non_empty(const std::string& target, const std::regex& regex) {
    if (target.empty()) {
      return true;
    }
    // may throw std::regex_error
    return std::regex_match(target, regex);
  }
}

namespace meta {
  bool Version::valid() const {
    static const auto pre_release_regex = make_regex(pre_release_pattern);
    static const auto build_regex = make_regex(build_pattern);

    const auto pre_release_valid = match_non_empty(pre_release, pre_release_regex);
    const auto build_valid = match_non_empty(build, build_regex);
    return pre_release_valid && build_valid;
  }

  std::string Version::to_string() const {
    auto oss = util::make_classic_oss();
    oss << major << '.' << minor << '.' << patch;
    if (!pre_release.empty()) {
      oss << '-' << pre_release;
    }
    if (!build.empty()) {
      oss << '+' << build;
    }
    return oss.str();
  }

  bool operator==(const Version& lhs, const Version& rhs) noexcept {
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.pre_release, lhs.build)
        == std::tie(rhs.major, rhs.minor, rhs.patch, rhs.pre_release, rhs.build);
  }

  bool operator<(const Version& lhs, const Version& rhs) noexcept {
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.pre_release, lhs.build)
        < std::tie(rhs.major, rhs.minor, rhs.patch, rhs.pre_release, rhs.build);
  }

  bool operator!=(const Version& lhs, const Version& rhs) noexcept {
    return !(lhs == rhs);
  }

  bool operator<=(const Version& lhs, const Version& rhs) noexcept {
    return !(rhs < lhs);
  }

  bool operator>(const Version& lhs, const Version& rhs) noexcept {
    return rhs < lhs;
  }

  bool operator>=(const Version& lhs, const Version& rhs) noexcept {
    return !(lhs < rhs);
  }

  std::ostream& operator<<(std::ostream& os, const Version& ver) {
    return os << ver.to_string();
  }
}
