#include "match.h"

#include "dtos.h"
#include "expected.h"
#include "player.h"

static auto
is_every_player_ready(std::vector<std::shared_ptr<Player>> const &players)
    -> bool {
  for (auto const &player : players) {
    if (!player->is_ready())
      return false;
  }
  return true;
}

Match::Match(std::unique_ptr<DiceBucket> dice_bucket)
    : dice_bucket_(std::move(dice_bucket)) {}

auto Match::join(std::string_view name)
    -> Expected<std::shared_ptr<Player>, MatchError> {
  if (state_ != MatchState::Lobby) {
    return unexpected(MatchError::GameIsActive);
  }
  for (auto const &player : players_) {
    if (player->name() == name) {
      return unexpected(MatchError::PlayerNameAlreadyInUse);
    }
  }

  PlayerEvents events;
  events.left = []() {}; // TODO
  events.ready_state_changed = [this]() { progress(); };

  auto new_player = std::make_shared<Player>(std::move(events), name);
  players_.push_back(new_player);
  return new_player;
}

auto Match::build_dto_for(Player &) -> MatchDTO {
  // Player argument will help later to hide information not intended for this
  // player.
  auto match_dto = MatchDTO{.state = state_, .players = {}};
  for (auto const &player : players_) {
    match_dto.players.push_back(
        PlayerDTO{.name = player->name(), .ready = player->is_ready()});
  }
  return match_dto;
}

auto Match::roll(Player &player) -> Expected<Void, MatchError> {
  if (!is_players_turn(player)) {
    return unexpected(MatchError::NotThePlayersTurn);
  }
  dice_bucket_->roll_next_dice();

  progress(); // FIXME is that a good idea?

  return Void{};
}
auto Match::keep(Player &player) -> Expected<int, MatchError> {
  if (!is_players_turn(player)) {
    return unexpected(MatchError::NotThePlayersTurn);
  }

  auto eyes =
      dice_bucket_
          ->take_eyes(); // FIXME const int is not cast' into Expected<int, ...>

  curr_player_++;
  if (players_.size() == curr_player_) {
    curr_player_ = 0;
  }

  progress();

  return eyes;
}

auto Match::progress() -> void {
  switch (state_) {
  case MatchState::Lobby:
    if (is_every_player_ready(players_)) {
      state_ = MatchState::RoundOngoing;
      // TODO: Notify players about state transition ?
    }
    break;
  case MatchState::RoundOngoing:
    break;
  case MatchState::RoundCompleted:
    break;
  }
}
auto Match::is_players_turn(Player &player) -> bool {
  return players_[curr_player_].get() == &player;
}
