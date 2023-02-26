#pragma once

#include <exception>
#include <memory>
#include <string_view>

class BadExpectedAccess : public std::exception {
public:
  explicit BadExpectedAccess() : std::exception() {}

  auto what() const noexcept -> char const * override {
    return "requested type is invalid";
  }
};

template <class E> class Unexpected {
public:
  using error_type = E;

  explicit Unexpected(E &&e) : unexpected(std::forward<E>(e)) {}
  E const unexpected;
};
template <class E> auto unexpected(E &&e) -> Unexpected<E> {
  return Unexpected<E>(std::forward<E>(e));
}

template <class T, class E> class Expected {
public:
  using value_type = T;
  using error_type = E;
  using unexpected_type = Unexpected<E>;

  Expected(T &&t) : has_value_(true), value_(std::forward<T>(t)) {}
  Expected(Unexpected<E> &&e)
      : has_value_(false), unexpected_(std::forward<Unexpected<E>>(e)) {}

  ~Expected() {
    if (has_value()) {
      value_.~value_type();
    } else {
      unexpected_.~unexpected_type();
    }
  }

  auto has_value() const -> bool { return has_value_; }

  auto value() const -> T const & {
    if (!has_value()) {
      throw BadExpectedAccess{};
    }
    return value_;
  }

  auto value_or(T &&alt) const -> T const & {
    if (!has_value()) {
      return std::forward<T>(alt);
    }
    return value_;
  }

  auto error() const -> E const & {
    if (has_value()) {
      throw BadExpectedAccess{};
    }
    return unexpected_.unexpected;
  }

private:
  bool has_value_;
  union {
    value_type value_;
    unexpected_type unexpected_;
  };
};
