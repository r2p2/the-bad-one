#include "core/dice_rng.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("predictable dice", "[dice]") {
  auto const fn_roll_dice = build_predictable_dice({1, 2, 3});

  REQUIRE(fn_roll_dice() == 1);
  REQUIRE(fn_roll_dice() == 2);
  REQUIRE(fn_roll_dice() == 3);
  REQUIRE(fn_roll_dice() == 1);
}

TEST_CASE("unpredictable dice", "[dice]") {
  auto const fn_roll_dice = build_real_dice();

  for (int i = 0; i < 100; ++i) {
    auto const eyes = fn_roll_dice();
    REQUIRE(eyes > 0);
    REQUIRE(eyes < 7);
  }
}