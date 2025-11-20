
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

// SPINACH TESTS

TEST_CASE( "spinach - it sprouts and matures and returns correct symbols" ) {
  Spinach spinach;
  REQUIRE( spinach.symbol() == "x" ); // initial state
  spinach.endDay();
  spinach.endDay();
  REQUIRE( spinach.symbol() == "p" ); // sprout state
  spinach.endDay();
  spinach.endDay();
  spinach.endDay();
  REQUIRE( spinach.symbol() == "P" ); // mature state
}

TEST_CASE("spinach - sprouts after daysToSprout without watering") {
  Spinach spinach;
  spinach.endDay();
  spinach.endDay();
  REQUIRE(spinach.getGrowthStage() == Plot::SPROUT);
  REQUIRE(spinach.symbol() == "p");
  REQUIRE_FALSE(spinach.isMature());
}

TEST_CASE("spinach - watering advances growth by one extra day on next endDay") {
  Spinach spinach;
  spinach.waterPlant();
  spinach.endDay(); // +2 days -> sprout (needs 2)
  REQUIRE(spinach.getGrowthStage() == Plot::SPROUT);
  REQUIRE(spinach.symbol() == "p");
}

TEST_CASE("spinach - matures after full growth period and reports mature") {
  Spinach spinach;
  for (int i = 0; i < 5; ++i) spinach.endDay();
  REQUIRE(spinach.getGrowthStage() == Plot::MATURE);
  REQUIRE(spinach.symbol() == "P");
  REQUIRE(spinach.isMature());
}

TEST_CASE("spinach - watering multiple times before endDay does not double-count beyond one extra day") {
  Spinach spinach;
  spinach.waterPlant();
  spinach.waterPlant();
  spinach.endDay(); // age == 2 -> sprout only
  REQUIRE(spinach.getGrowthStage() == Plot::SPROUT);
  REQUIRE_FALSE(spinach.isMature());
}

TEST_CASE("spinach - incremental growth with mixed watering") {
  Spinach spinach;
  spinach.waterPlant();
  spinach.endDay(); // sprout
  for (int i = 0; i < 3; ++i) spinach.endDay(); // mature
  REQUIRE(spinach.isMature());
  REQUIRE(spinach.symbol() == "P");
}
