#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm.hpp"
#include "../src/carrot.hpp"

TEST_CASE( "it can be initialized with a single plot" ) {
  Farm farm(1, 1);
  REQUIRE( farm.number_of_rows() == 1 );
  REQUIRE( farm.number_of_columns() == 1 );
}

TEST_CASE( "it can be initialized as a 1x2 farm" ) {
  Farm farm(1, 2);
  REQUIRE( farm.number_of_rows() == 1 );
  REQUIRE( farm.number_of_columns() == 2 );
}

TEST_CASE( "it can be initialized as a 2x1 farm" ) {
  Farm farm(2, 1);
  REQUIRE( farm.number_of_rows() == 2 );
  REQUIRE( farm.number_of_columns() == 1 );
}

TEST_CASE( "it returns the symbol for a single soil plot" ) {
  Farm farm(1, 1);
  REQUIRE( farm.get_symbol(0, 0) == "." );
}

TEST_CASE( "it returns the symbols for a 1x2 farm" ) {
  Farm farm(1, 2);
  REQUIRE( farm.get_symbol(0, 0) == "." );
  REQUIRE( farm.get_symbol(0, 1) == "." );
}

TEST_CASE( "it returns the symbols for a 2x1 farm" ) {
  Farm farm(2, 1);
  REQUIRE( farm.get_symbol(0, 0) == "." );
  REQUIRE( farm.get_symbol(1, 0) == "." );
}

TEST_CASE( "it allows us to plant a carrot" ) {
  Farm farm(1, 1);
  Carrot carrot;
  farm.plant(0, 0, &carrot);
  REQUIRE( farm.get_symbol(0, 0) == "v" );
}
