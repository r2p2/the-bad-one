#pragma once

#include "dice_bucket.h"
#include "dtos.h"
#include "expected.h"
#include "match_state.h"

#include <memory>
#include <string_view>
#include <vector>

class Player;

enum class MatchError {
  GameIsActive,
  PlayerNameAlreadyInUse,
  NotThePlayersTurn,
};

class Match {
public:
  Match(std::unique_ptr<DiceBucket>);

  auto join(std::string_view name)
      -> Expected<std::shared_ptr<Player>, MatchError>;
  auto build_dto_for(Player &) -> MatchDTO;

  auto roll(Player &) -> Expected<Void, MatchError>;
  auto keep(Player &) -> Expected<int, MatchError>;

private:
  auto progress() -> void;
  auto is_players_turn(Player &) -> bool;

private:
  MatchState state_ = MatchState::Lobby;
  std::vector<std::shared_ptr<Player>> players_ = {};
  std::size_t curr_player_ = 0;
  std::unique_ptr<DiceBucket> dice_bucket_;
};