
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

// BRUSSELS SPROUTS TESTS

TEST_CASE( "brussels sprouts - it sprouts and matures and returns correct symbols" ) {
  BrusselsSprouts brusselsSprouts;
  REQUIRE( brusselsSprouts.symbol() == "x" ); // initial state
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  REQUIRE( brusselsSprouts.symbol() == "r" ); // sprout state
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  REQUIRE( brusselsSprouts.symbol() == "R" ); // mature state
}

TEST_CASE("brussels sprouts - sprouts after daysToSprout without watering") {
  BrusselsSprouts bs;
  for (int i = 0; i < 5; ++i) bs.endDay();
  REQUIRE(bs.getGrowthStage() == Plot::SPROUT);
  REQUIRE(bs.symbol() == "r");
  REQUIRE_FALSE(bs.isMature());
}

TEST_CASE("brussels sprouts - watering advances growth by one extra day on next endDay") {
  BrusselsSprouts bs;
  bs.waterPlant();
  bs.endDay(); // age 2 (still seed)
  for (int i = 0; i < 3; ++i) bs.endDay(); // reaches age 5 -> sprout on day 4 instead of day 5
  REQUIRE(bs.getGrowthStage() == Plot::SPROUT);
  REQUIRE(bs.symbol() == "r");
}

TEST_CASE("brussels sprouts - matures after full growth period and reports mature") {
  BrusselsSprouts bs;
  for (int i = 0; i < 15; ++i) bs.endDay();
  REQUIRE(bs.getGrowthStage() == Plot::MATURE);
  REQUIRE(bs.symbol() == "R");
  REQUIRE(bs.isMature());
}

TEST_CASE("brussels sprouts - watering multiple times before endDay does not double-count beyond one extra day") {
  BrusselsSprouts bs;
  bs.waterPlant();
  bs.waterPlant();
  bs.endDay(); // should be age 2, still seed
  REQUIRE(bs.symbol() == "x");
  REQUIRE_FALSE(bs.isMature());
  REQUIRE(bs.getGrowthStage() != Plot::SPROUT);
}

TEST_CASE("brussels sprouts - incremental growth with mixed watering") {
  BrusselsSprouts bs;
  bs.waterPlant();
  bs.endDay(); // age 2
  for (int i = 0; i < 3; ++i) bs.endDay(); // age 5 sprout
  REQUIRE(bs.getGrowthStage() == Plot::SPROUT);
  for (int i = 0; i < 10; ++i) bs.endDay(); // mature
  REQUIRE(bs.isMature());
  REQUIRE(bs.symbol() == "R");
}
