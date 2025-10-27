#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/carrot.hpp"

TEST_CASE( "it returns a v as its when it is a seedling" ) {
  Carrot carrot;
  REQUIRE( carrot.symbol() == "v" );
}

TEST_CASE( "it grows" ) {
  Carrot carrot;
  REQUIRE( carrot.symbol() == "v" );
  carrot.grow();
  REQUIRE( carrot.symbol() == "V" );
}

TEST_CASE( "it reports its growth stage" ) {
  Carrot carrot;
  REQUIRE( carrot.getGrowthStage() == false );
  carrot.grow();
  REQUIRE( carrot.getGrowthStage() == true );
}