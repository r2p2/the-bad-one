#pragma once

#include "match_state.h"

#include <string>
#include <vector>

struct PlayerDTO {
  std::string name;
  bool ready;
};

struct MatchDTO {
  MatchState state;
  std::vector<PlayerDTO> players;
};