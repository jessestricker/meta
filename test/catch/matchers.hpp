#ifndef META_TEST_MATCHERS_HPP
#define META_TEST_MATCHERS_HPP

#include <sstream>
#include <stdexcept>

#include "catch.hpp"

template <class T>
class ExhaustiveComparison : public Catch::MatcherBase<T> {
public:
  enum class Operation { Equals, NotEquals, LessThan };

  friend std::ostream& operator<<(std::ostream& os, const Operation& op) {
    switch (op) {
    case Operation ::Equals:
      return os << "is equal to";
    case Operation ::NotEquals:
      return os << "is not equal to";
    case Operation ::LessThan:
      return os << "is less than";
    default:
      throw std::invalid_argument{"op"};
    }
  }

  ExhaustiveComparison(Operation op, const T& rhs)
      : op_(op)
      , rhs_(rhs) {
  }

  bool match(const T& lhs) const override {
    const auto eq = lhs == rhs_;
    const auto ne = lhs != rhs_;
    const auto lt = lhs < rhs_;
    const auto gt = lhs > rhs_;
    const auto le = lhs <= rhs_;
    const auto ge = lhs >= rhs_;

    const auto eq_rev = rhs_ == lhs;
    const auto ne_rev = rhs_ != lhs;
    const auto lt_rev = rhs_ > lhs;
    const auto gt_rev = rhs_ < lhs;
    const auto le_rev = rhs_ >= lhs;
    const auto ge_rev = rhs_ <= lhs;

    // check symmetry
    const auto symmetrical
        = (eq == eq_rev) && (ne == ne_rev) && (lt == lt_rev) && (gt == gt_rev) && (le == le_rev) && (ge == ge_rev);
    if (!symmetrical) {
      return false;
    }

    // perform op
    switch (op_) {
    case Operation::Equals:
      return eq && !ne && !lt && !gt && le && ge;
    case Operation::NotEquals:
      return !eq && ne && (lt != gt) && (le != ge);
    case Operation::LessThan:
      return !eq && ne && lt && !gt && le && !ge;
    default:
      throw std::invalid_argument{"op_"};
    }
  }

  [[nodiscard]] std::string describe() const override {
    auto oss = std::ostringstream{};
    oss << op_ << " " << rhs_;
    return oss.str();
  }

private:
  Operation op_;
  const T& rhs_;
};

template <class T>
ExhaustiveComparison<T> is_equal_to(const T& rhs) {
  return {ExhaustiveComparison<T>::Operation::Equals, rhs};
}

template <class T>
ExhaustiveComparison<T> is_not_equal_to(const T& rhs) {
  return {ExhaustiveComparison<T>::Operation::NotEquals, rhs};
}

template <class T>
ExhaustiveComparison<T> is_less_than(const T& rhs) {
  return {ExhaustiveComparison<T>::Operation::LessThan, rhs};
}

#endif // META_TEST_MATCHERS_HPP
