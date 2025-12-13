#pragma once

#include <string>
#include <random>

class Player;

class Bunny
{
private:
  int current_row = -1;
  int current_column = -1;
  bool scared = false;

public:
  std::string symbol() const;
  bool is_alive() const;
  int row() const;
  int column() const;

  void despawn();

  void spawn_random_edge(int rows, int columns, const Player &player, std::mt19937 &rng);

  void mark_scared_if_adjacent(const Player &player);

  void move_end_of_day(int rows, int columns, const Player &player, std::mt19937 &rng);
};
