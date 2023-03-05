#include "player.h"

#include "dtos.h"

Player::Player(PlayerEvents events, std::string_view name)
    : events_(std::move(events)), name_(name){};
Player::~Player() { events_.left(); };
auto Player::name() const -> std::string const & { return name_; }
auto Player::is_ready() const -> bool { return ready_; }
auto Player::points() const -> int { return points_; }
auto Player::toggle_ready() -> void {
  ready_ = !is_ready();
  events_.ready_state_changed();
}
