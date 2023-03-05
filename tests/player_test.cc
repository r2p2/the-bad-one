#include "core/player.h"

#include <catch2/catch_test_macros.hpp>
#include <memory>

TEST_CASE("empty match", "[player]") {
  int left_counter = 0;
  int ready_state_changed_counter = 0;

  auto events = PlayerEvents{};
  events.left = [&left_counter]() { ++left_counter; };
  events.ready_state_changed = [&ready_state_changed_counter]() {
    ++ready_state_changed_counter;
  };
  auto player = std::make_unique<Player>(events, "bob");

  SECTION("setup") {
    REQUIRE(player->name() == "bob");
    REQUIRE(player->is_ready() == false);
  }

  SECTION("toggle ready state") {
    player->toggle_ready();
    REQUIRE(player->is_ready() == true);
    player->toggle_ready();
    REQUIRE(player->is_ready() == false);
    REQUIRE(ready_state_changed_counter == 2);
  }

  SECTION("leave on destruction") {
    player.reset();
    REQUIRE(left_counter == 1);
  }
}