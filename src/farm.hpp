#pragma once

#include <string>
#include <vector>
#include <random>

#include "plot.hpp"
#include "player.hpp"
#include "bunny.hpp"

#include "vegetables/carrot.hpp"
#include "vegetables/beet.hpp"
#include "vegetables/lettuce.hpp"
#include "vegetables/spinach.hpp"
#include "vegetables/brussels_sprouts.hpp"

class Farm
{
private:
  int rows;
  int columns;
  Player *player;
  std::vector<std::vector<Plot *>> plots;

  Bunny bunny;

  // 15% chance
  const int bunny_spawn_percent = 15;

  std::mt19937 rng;

  void maybe_spawn_bunny();
  void eat_vegetable_under_bunny();

public:
  int day_count;
  Farm(int rows, int columns, Player *player);
  int number_of_rows();
  int number_of_columns();
  std::string get_symbol(int row, int column);
  void plant(int row, int column, Plot *plot);
  void end_day();
  void harvest(int row, int column, Plot *plot);
  void water(int row, int column, Plot *plot);

  void check_bunny_scared();
};
