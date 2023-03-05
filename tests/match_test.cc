#include "core/dice_bucket.h"
#include "core/dice_rng.h"
#include "core/match.h"
#include "core/player.h"

#include <catch2/catch_test_macros.hpp>

template <class... Numbers>
static auto build_test_match(Numbers... numbers) -> Match {
  return Match{
      std::make_unique<DiceBucket>(build_predictable_dice({numbers...}))};
}

TEST_CASE("empty match", "[match]") {
  auto match = build_test_match(1, 2, 3, 4, 5, 6);

  SECTION("one player joining") {
    auto result = match.join("alice");

    REQUIRE(result.has_value());
    REQUIRE(result.value()->name() == "alice");
  }

  SECTION("join a match with same name shall fail") {
    auto result1 = match.join("alice");
    auto result2 = match.join("alice");

    REQUIRE(result1.has_value());
    REQUIRE(result1.value()->name() == "alice");
    REQUIRE(not result2.has_value());
    REQUIRE(result2.error() == MatchError::PlayerNameAlreadyInUse);
  }

  SECTION("join a match with different name shall succeed") {
    auto result1 = match.join("alice");
    auto result2 = match.join("bob");

    REQUIRE(result1.has_value());
    REQUIRE(result1.value()->name() == "alice");
    REQUIRE(result2.has_value());
    REQUIRE(result2.value()->name() == "bob");
  }
}

TEST_CASE("active match with 2 players", "[match]") {
  auto match = build_test_match(1, 2, 3, 4, 5, 6);
  auto bob = match.join("bob").value();
  auto alice = match.join("alice").value();

  bob->toggle_ready();
  alice->toggle_ready();

  SECTION("it shall be impossible to join as another player") {
    auto join_result = match.join("karen");

    REQUIRE(!join_result.has_value());
    REQUIRE(join_result.error() == MatchError::GameIsActive);
  }

  SECTION("current player can roll the dice") {
    auto const result = match.roll(*bob);
    REQUIRE(result.has_value());
  }

  SECTION("only the current player can roll the dice") {
    auto const result = match.roll(*alice);
    REQUIRE(!result.has_value());
    REQUIRE(result.error() == MatchError::NotThePlayersTurn);
  }

  SECTION("current player can take his eyes") {
    auto const result = match.keep(*bob);
    REQUIRE(result.has_value());
  }

  SECTION("only the current player can take his eyes") {
    auto const result = match.keep(*alice);
    REQUIRE(!result.has_value());
    REQUIRE(result.error() == MatchError::NotThePlayersTurn);
  }
}