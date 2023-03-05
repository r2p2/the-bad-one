#include "core/dice_bucket.h"
#include "core/dice_rng.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("dice bucket", "[dice]") {
  auto dice_bucket = DiceBucket{build_predictable_dice({1, 2, 3, 4, 5, 6})};

  SECTION("initial dice bucket has 0 eyes") {
    REQUIRE(dice_bucket.eyes() == 0);
    REQUIRE(dice_bucket.dice_rolls() == std::array<int, 5>{});
  }

  SECTION("only five rolls are allowed") {
    REQUIRE(dice_bucket.roll_next_dice().has_value());
    REQUIRE(dice_bucket.roll_next_dice().has_value());
    REQUIRE(dice_bucket.roll_next_dice().has_value());
    REQUIRE(dice_bucket.roll_next_dice().has_value());
    REQUIRE(dice_bucket.roll_next_dice().has_value());
    REQUIRE(dice_bucket.roll_next_dice().error() ==
            DiceBucketError::MaximumRollsReaced);
  }

  SECTION("taking eyes will reset the dice bucket") {
    dice_bucket.roll_next_dice();
    dice_bucket.roll_next_dice();
    dice_bucket.roll_next_dice();

    REQUIRE(dice_bucket.take_eyes() == 6);
    REQUIRE(dice_bucket.eyes() == 0);
  }
}