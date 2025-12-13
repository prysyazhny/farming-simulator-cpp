#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/bunny.hpp"
#include "../src/player.hpp"

#include <random>
#include <cmath>

TEST_CASE("a bunny starts not alive")
{
  Bunny bunny;
  REQUIRE(bunny.is_alive() == false);
}

TEST_CASE("a bunny has the correct symbol")
{
  Bunny bunny;
  REQUIRE(bunny.symbol() == "M");
}

TEST_CASE("spawning a bunny places it on the edge of the farm")
{
  Player player(10, 10);
  Bunny bunny;
  std::mt19937 rng(42);

  bunny.spawn_random_edge(10, 10, player, rng);

  REQUIRE(bunny.is_alive() == true);

  bool on_edge =
      bunny.row() == 0 ||
      bunny.row() == 9 ||
      bunny.column() == 0 ||
      bunny.column() == 9;

  REQUIRE(on_edge == true);
}

TEST_CASE("a bunny never spawns on the player")
{
  Player player(10, 10);
  Bunny bunny;
  std::mt19937 rng(1337);

  bunny.spawn_random_edge(10, 10, player, rng);

  bool same_spot =
      bunny.row() == player.row() &&
      bunny.column() == player.column();

  REQUIRE(same_spot == false);
}

TEST_CASE("a bunny moves one square during normal movement (or despawns)")
{
  Player player(10, 10);
  Bunny bunny;
  std::mt19937 rng(99);

  bunny.spawn_random_edge(10, 10, player, rng);

  int start_row = bunny.row();
  int start_col = bunny.column();

  bunny.move_end_of_day(10, 10, player, rng);

  if (bunny.is_alive())
  {
    int dr = std::abs(bunny.row() - start_row);
    int dc = std::abs(bunny.column() - start_col);

    REQUIRE(dr + dc == 1);
  }
  else
  {
    REQUIRE(bunny.is_alive() == false);
  }
}

TEST_CASE("a bunny does not move onto the player")
{
  Player player(10, 10);
  Bunny bunny;
  std::mt19937 rng(2025);

  bunny.spawn_random_edge(10, 10, player, rng);

  bunny.move_end_of_day(10, 10, player, rng);

  if (bunny.is_alive())
  {
    bool on_player =
        bunny.row() == player.row() &&
        bunny.column() == player.column();

    REQUIRE(on_player == false);
  }
  else
  {
    REQUIRE(bunny.is_alive() == false);
  }
}

TEST_CASE("despawn makes the bunny not alive")
{
  Bunny bunny;
  Player player(10, 10);
  std::mt19937 rng(7);

  bunny.spawn_random_edge(10, 10, player, rng);
  REQUIRE(bunny.is_alive() == true);

  bunny.despawn();
  REQUIRE(bunny.is_alive() == false);
}