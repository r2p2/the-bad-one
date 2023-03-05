#pragma once

#include "dtos.h"

#include <functional>
#include <string>
#include <string_view>

struct PlayerEvents {
  std::function<void()> left = [] {};
  std::function<void()> ready_state_changed = [] {};
};

class Player {
public:
  explicit Player(PlayerEvents, std::string_view name);
  ~Player();

  auto name() const -> std::string const &;
  auto is_ready() const -> bool;
  auto points() const -> int;
  auto toggle_ready() -> void;

private:
  PlayerEvents const events_;
  std::string const name_;
  bool ready_ = false;
  int points_ = 0;
};