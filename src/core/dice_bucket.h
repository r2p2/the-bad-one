#pragma once

#include "expected.h"

#include <array>
#include <functional>

enum class DiceBucketError {
  MaximumRollsReaced,
};

class DiceBucket {
public:
  explicit DiceBucket(std::function<int()> fn_roll_dice);

  auto eyes() const -> int;
  auto dice_rolls() const -> std::array<int, 5> const &;

  auto take_eyes() -> int;
  auto roll_next_dice() -> Expected<Void, DiceBucketError>;

private:
  std::function<int()> const fn_roll_dice_;
  std::array<int, 5> dice_;
};

auto debug_fmt(DiceBucket const &) -> std::string;