#include "dice_bucket.h"

#include "dice_rng.h"
#include <string>

DiceBucket::DiceBucket(std::function<int()> fn_dice)
    : fn_roll_dice_(std::move(fn_dice)), dice_({}){};

auto DiceBucket::eyes() const -> int {
  int eyes = 0;
  for (auto const &dice : dice_) {
    eyes += dice;
  }
  return eyes;
}
auto DiceBucket::dice_rolls() const -> std::array<int, 5> const & {
  return dice_;
};
auto DiceBucket::take_eyes() -> int {
  auto const eyes = this->eyes();
  for (auto &dice : dice_) {
    dice = 0;
  }
  return eyes;
}
auto DiceBucket::roll_next_dice() -> Expected<Void, DiceBucketError> {
  for (auto &dice : dice_) {
    if (dice != 0) {
      continue;
    }
    dice = fn_roll_dice_();
    return Void{};
  }
  return unexpected(DiceBucketError::MaximumRollsReaced);
};

auto debug_fmt(DiceBucket const &dice_bucket) -> std::string {
  std::string s = "DiceBucket{ ";
  for (auto const &dice : dice_bucket.dice_rolls()) {
    s += std::to_string(dice);
    s += " ";
  }
  s += "}";
  return s;
}