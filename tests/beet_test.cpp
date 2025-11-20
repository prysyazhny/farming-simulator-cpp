#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/vegetables/beet.hpp"
#include "../src/vegetables/brussels_sprouts.hpp"
#include "../src/vegetables/carrot.hpp"
#include "../src/vegetables/lettuce.hpp"
#include "../src/vegetables/spinach.hpp"

// Plant | Days to Sprout | Days to Maturity
// Carrot | 1 | 1
// Lettuce | 2 | 2
// Spinach | 2 | 3
// Beet | 2 | 5
// Brussels Sprouts | 5 | 10

// BEET TESTS

TEST_CASE( "beet - it sprouts and matures and returns correct symbols" ) {
  Beet beet;
  REQUIRE( beet.symbol() == "x" ); // initial state
  beet.endDay();
  beet.endDay();
  REQUIRE( beet.symbol() == "b" ); // sprout state
  beet.endDay();
  beet.endDay();
  beet.endDay();
  beet.endDay();
  beet.endDay();
  REQUIRE( beet.symbol() == "B" ); // mature state
}

TEST_CASE("beet - sprouts after daysToSprout without watering") {
  Beet beet;
  // daysToSprout == 2
  beet.endDay();
  beet.endDay();
  REQUIRE(beet.getGrowthStage() == Plot::SPROUT);
  REQUIRE(beet.symbol() == "b");
  REQUIRE_FALSE(beet.isMature());
}

TEST_CASE("beet - watering advances growth by one extra day on next endDay") {
  Beet beet;
  beet.waterPlant();
  beet.endDay(); // watered -> age increments twice
  REQUIRE(beet.getGrowthStage() == Plot::SPROUT);
  REQUIRE(beet.symbol() == "b");
}

TEST_CASE("beet - matures after full growth period and reports mature") {
  Beet beet;
  // total days = daysToSprout + daysToMature == 2 + 5 == 7
  for (int i = 0; i < 7; ++i) beet.endDay();
  REQUIRE(beet.getGrowthStage() == Plot::MATURE);
  REQUIRE(beet.symbol() == "B");
  REQUIRE(beet.isMature());
}

TEST_CASE("beet - watering multiple times before endDay does not double-count beyond one extra day") {
  Beet beet;
  // simulate calling waterPlant multiple times before a single endDay
  beet.waterPlant();
  beet.waterPlant();
  beet.endDay(); // should still advance by 2 total (not 3+)
  REQUIRE(beet.getGrowthStage() == Plot::SPROUT);
}

TEST_CASE("beet - incremental growth with mixed watering") {
  Beet beet;
  // day 1: water -> effectively +2 -> age==2 -> sprout
  beet.waterPlant();
  beet.endDay();
  REQUIRE(beet.getGrowthStage() == Plot::SPROUT);

  // day 2-6: let it progress normally for 5 more days to mature
  for (int i = 0; i < 5; ++i) beet.endDay();
  REQUIRE(beet.isMature());
  REQUIRE(beet.symbol() == "B");
}