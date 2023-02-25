#include "core/expected.h"

#include <iostream>

enum class DivError { DivByZero };

auto div(double a, double b) -> Expected<double, DivError> {
  if (b == 0) {
    return unexpected(DivError::DivByZero);
  }
  return a / b;
}

int main() {
  auto r1 = div(1.2, 3.2);
  auto r2 = div(1.2, 0.0);

  std::cout << "1: " << r1.value() << std::endl;
  std::cout << "2.1: " << r2.has_value() << std::endl;
  std::cout << "2: " << r2.value_or(0) << std::endl;
  std::cout << "3: " << (r2.error() == DivError::DivByZero ? "ok" : "err")
            << std::endl;

  return 0;
}