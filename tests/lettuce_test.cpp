
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

// LETTUCE TESTS

TEST_CASE( "lettuce - it sprouts and matures and returns correct symbols" ) {
  Lettuce lettuce;
  REQUIRE( lettuce.symbol() == "x" ); // initial state
  lettuce.endDay();
  lettuce.endDay();
  REQUIRE( lettuce.symbol() == "l" ); // sprout state
  lettuce.endDay();
  lettuce.endDay();
  REQUIRE( lettuce.symbol() == "L" ); // mature state
}

TEST_CASE("lettuce - sprouts after daysToSprout without watering") {
  Lettuce lettuce;
  lettuce.endDay();
  lettuce.endDay();
  REQUIRE(lettuce.getGrowthStage() == Plot::SPROUT);
  REQUIRE(lettuce.symbol() == "l");
  REQUIRE_FALSE(lettuce.isMature());
}

TEST_CASE("lettuce - watering advances growth by one extra day on next endDay") {
  Lettuce lettuce;
  lettuce.waterPlant();
  lettuce.endDay(); // +2 days -> sprout (needs 2)
  REQUIRE(lettuce.getGrowthStage() == Plot::SPROUT);
  REQUIRE(lettuce.symbol() == "l");
  REQUIRE_FALSE(lettuce.isMature());
}

TEST_CASE("lettuce - matures after full growth period and reports mature") {
  Lettuce lettuce;
  for (int i = 0; i < 4; ++i) lettuce.endDay();
  REQUIRE(lettuce.getGrowthStage() == Plot::MATURE);
  REQUIRE(lettuce.symbol() == "L");
  REQUIRE(lettuce.isMature());
}

TEST_CASE("lettuce - watering multiple times before endDay does not double-count beyond one extra day") {
  Lettuce lettuce;
  lettuce.waterPlant();
  lettuce.waterPlant();
  lettuce.endDay(); // age == 2 -> sprout only
  REQUIRE(lettuce.getGrowthStage() == Plot::SPROUT);
  REQUIRE_FALSE(lettuce.isMature());
}

TEST_CASE("lettuce - incremental growth with mixed watering") {
  Lettuce lettuce;
  lettuce.waterPlant();
  lettuce.endDay(); // sprout
  for (int i = 0; i < 2; ++i) lettuce.endDay(); // mature
  REQUIRE(lettuce.isMature());
  REQUIRE(lettuce.symbol() == "L");
}
