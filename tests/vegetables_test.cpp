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

TEST_CASE( "beet - it returns a x as its when it is a seedling" ) {
  Beet beet;
  REQUIRE( beet.symbol() == "x" );
}

TEST_CASE( "beet - it sprouts and matures" ) {
  Beet beet;
  REQUIRE( beet.symbol() == "x" );
  beet.endDay();
  beet.endDay();
  REQUIRE( beet.symbol() == "b" );
  beet.endDay();
  beet.endDay();
  beet.endDay();
  beet.endDay();
  beet.endDay();
  REQUIRE( beet.symbol() == "B" );
}

// BRUSSELS SPROUTS TESTS

TEST_CASE( "brussels sprouts - it returns a x as its when it is a seedling" ) {
  BrusselsSprouts brusselsSprouts;
  REQUIRE( brusselsSprouts.symbol() == "x" );
}

TEST_CASE( "brussels sprouts - it sprouts and matures" ) {
  BrusselsSprouts brusselsSprouts;
  REQUIRE( brusselsSprouts.symbol() == "x" );
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  brusselsSprouts.endDay();
  REQUIRE( brusselsSprouts.symbol() == "r" );
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
  REQUIRE( brusselsSprouts.symbol() == "R" );
}

// CARROT TESTS

TEST_CASE( "carrot - it returns a x as its when it is a seedling" ) {
  Carrot carrot;
  REQUIRE( carrot.symbol() == "x" );
}

TEST_CASE( "carrot - it sprouts and matures" ) {
  Carrot carrot;
  REQUIRE( carrot.symbol() == "x" );
  carrot.endDay();
  REQUIRE( carrot.symbol() == "c" );
  carrot.endDay();
  REQUIRE( carrot.symbol() == "C" );
}

// LETTUCE TESTS

TEST_CASE( "lettuce - it returns a x as its when it is a seedling" ) {
  Lettuce lettuce;
  REQUIRE( lettuce.symbol() == "x" );
}

TEST_CASE( "lettuce - it sprouts and matures" ) {
  Lettuce lettuce;
  REQUIRE( lettuce.symbol() == "x" );
  lettuce.endDay();
  lettuce.endDay();
  REQUIRE( lettuce.symbol() == "l" );
  lettuce.endDay();
  lettuce.endDay();
  REQUIRE( lettuce.symbol() == "L" );
}

// SPINACH TESTS

TEST_CASE( "spinach - it returns a x as its when it is a seedling" ) {
  Spinach spinach;
  REQUIRE( spinach.symbol() == "x" );
}

TEST_CASE( "spinach - it sprouts and matures" ) {
  Spinach spinach;
  REQUIRE( spinach.symbol() == "x" );
  spinach.endDay();
  spinach.endDay();
  REQUIRE( spinach.symbol() == "p" );
  spinach.endDay();
  spinach.endDay();
  spinach.endDay();
  REQUIRE( spinach.symbol() == "P" );
}
