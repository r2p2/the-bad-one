#include "core/expected.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>

enum class DivError { DivByZero };

static auto test_div(double a, double b) -> Expected<double, DivError> {
  if (b == 0) {
    return unexpected(DivError::DivByZero);
  }
  return a / b;
}

TEST_CASE("expected with valid value", "[expected]") {
  auto const result = test_div(6.0, 2.0);

  REQUIRE(result.has_value() == true);
  REQUIRE(result.value() == 3.0);
  REQUIRE_THROWS_AS(result.error(), BadExpectedAccess);
}

TEST_CASE("expected with error", "[expected]") {
  auto const result = test_div(6.0, 0.0);

  REQUIRE(result.has_value() == false);
  REQUIRE(result.error() == DivError::DivByZero);
  REQUIRE_THROWS_AS(result.value(), BadExpectedAccess);
}

TEST_CASE("void as success value", "[expected]") {
  Expected<Void, int> expected{Void{}};

  REQUIRE(expected.has_value() == true);
}