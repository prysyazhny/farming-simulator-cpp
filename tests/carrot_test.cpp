
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

// CARROT TESTS

TEST_CASE( "carrot - it sprouts and matures and returns correct symbols" ) {
  Carrot carrot;
  REQUIRE( carrot.symbol() == "x" ); // initial state
  carrot.endDay();
  REQUIRE( carrot.symbol() == "c" ); // sprout state
  carrot.endDay();
  REQUIRE( carrot.symbol() == "C" ); // mature state
}

TEST_CASE("carrot - sprouts after daysToSprout without watering") {
  Carrot carrot;
  carrot.endDay(); // day 1
  REQUIRE(carrot.getGrowthStage() == Plot::SPROUT);
  REQUIRE(carrot.symbol() == "c");
  REQUIRE_FALSE(carrot.isMature());
}

TEST_CASE("carrot - watering advances growth by one extra day on next endDay") {
  Carrot carrot;
  carrot.waterPlant();
  carrot.endDay(); // advances 2 days (1 + extra) -> immediate maturity
  REQUIRE(carrot.getGrowthStage() == Plot::MATURE);
  REQUIRE(carrot.symbol() == "C");
  REQUIRE(carrot.isMature());
}

TEST_CASE("carrot - matures after full growth period and reports mature") {
  Carrot carrot;
  for (int i = 0; i < 2; ++i) carrot.endDay(); // total daysToSprout + daysToMature
  REQUIRE(carrot.getGrowthStage() == Plot::MATURE);
  REQUIRE(carrot.symbol() == "C");
  REQUIRE(carrot.isMature());
}

TEST_CASE("carrot - watering multiple times before endDay does not double-count beyond one extra day") {
  Carrot carrot;
  carrot.waterPlant();
  carrot.waterPlant();
  carrot.endDay(); // still only +2 growth, reaches maturity
  REQUIRE(carrot.getGrowthStage() == Plot::MATURE);
  REQUIRE(carrot.symbol() == "C");
}

TEST_CASE("carrot - incremental growth with mixed watering") {
  Carrot carrot;
  carrot.waterPlant();
  carrot.endDay(); // maturity reached immediately
  REQUIRE(carrot.isMature());
  REQUIRE(carrot.symbol() == "C");
}