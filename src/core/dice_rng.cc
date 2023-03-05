#include "dice_rng.h"

#include <memory>
#include <random>

auto build_real_dice() -> std::function<int()> {
  return [gen = std::mt19937{std::random_device{}()},
          dist = std::uniform_int_distribution<>(1, 6)]() mutable -> int {
    return dist(gen);
  };
}

auto build_predictable_dice(std::vector<int> numbers) -> std::function<int()> {
  return [numbers = std::move(numbers), i = std::size_t{0}]() mutable {
    auto const number = numbers[i++];
    if (numbers.size() == i) {
      i = 0;
    }
    return number;
  };
}