#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/player.hpp"
#include "../src/farm.hpp"
#include "../src/farm_printer.hpp"
#include "../src/vegetables/carrot.hpp"

static std::string header_for(const Farm &farm)
{
  const std::string legendLine1 = "Movement: WASD | Water: SPACE | Harvest: F | End Day: E | Quit: Q | Bunny: M";
  const std::string legendLine2 = "Plant Carrot: C | Plant Beet: B | Plant Lettuce: L | Plant Spinach: P | Plant Brussels Sprouts: R";
  return "\n\nDay " + std::to_string(farm.day_count) + " | " + legendLine1 + "\n" + legendLine2 + "\n\n";
}

TEST_CASE( "it pretty prints a single plot of land" ) {
  Player player(1, 1);
  Farm farm(1, 1, &player);
  FarmPrinter printer(&farm);

  std::string expected = header_for(farm) + "@ \n";
  REQUIRE( printer.pp() == expected );
}

TEST_CASE( "it pretty prints a 1x2 farm" ) {
  Player player(1, 2);
  Farm farm(1, 2, &player);
  FarmPrinter printer(&farm);

  std::string expected = header_for(farm) + "@ . \n";
  REQUIRE( printer.pp() == expected );
}

TEST_CASE( "it pretty prints a 2x1 farm" ) {
  Player player(2, 1);
  Farm farm(2, 1, &player);
  FarmPrinter printer(&farm);

  std::string expected = header_for(farm) + "@ \n. \n";
  REQUIRE( printer.pp() == expected );
}

TEST_CASE( "it pretty prints a 2x2 farm" ) {
  Player player(2, 2);
  Farm farm(2, 2, &player);
  FarmPrinter printer(&farm);

  std::string expected = header_for(farm) + "@ . \n. . \n";
  REQUIRE( printer.pp() == expected );
}

TEST_CASE( "it pretty prints a farm with a carrot planted" ) {
  Player player(1, 2);
  Farm farm(1, 2, &player);
  Carrot carrot;
  farm.plant(0, 1, &carrot);
  FarmPrinter printer(&farm);

  std::string expected = header_for(farm) + "@ x \n";
  REQUIRE( printer.pp() == expected );
}


