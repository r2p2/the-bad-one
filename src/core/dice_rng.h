#pragma once

#include <functional>
#include <vector>

auto build_real_dice() -> std::function<int()>;
auto build_predictable_dice(std::vector<int>) -> std::function<int()>;