#ifndef META_TEST_HELPERS_HPP
#define META_TEST_HELPERS_HPP

#include <sstream>
#include <string>

template <class Type>
std::string from_stream_to_string(const Type& obj) {
  auto oss = std::ostringstream{};
  oss << obj;
  return oss.str();
}

#endif // META_TEST_HELPERS_HPP
