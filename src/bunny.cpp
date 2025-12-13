#include "bunny.hpp"
#include "player.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

std::string Bunny::symbol() const
{
  return "M";
}

bool Bunny::is_alive() const
{
  return current_row != -1 && current_column != -1;
}

int Bunny::row() const
{
  return current_row;
}

int Bunny::column() const
{
  return current_column;
}

void Bunny::despawn()
{
  current_row = -1;
  current_column = -1;
  scared = false;
}

void Bunny::spawn_random_edge(int rows, int columns, const Player &player, std::mt19937 &rng)
{
  if (is_alive())
  {
    return;
  }

  std::uniform_int_distribution<int> edge_dist(0, 3); 
  std::uniform_int_distribution<int> row_dist(0, rows - 1);
  std::uniform_int_distribution<int> col_dist(0, columns - 1);

  for (int tries = 0; tries < 50; tries++)
  {
    int edge = edge_dist(rng);
    int r = 0;
    int c = 0;

    if (edge == 0)
    {
      r = 0;
      c = col_dist(rng);
    }
    else if (edge == 1)
    {
      r = rows - 1;
      c = col_dist(rng);
    }
    else if (edge == 2)
    {
      r = row_dist(rng);
      c = 0;
    }
    else
    {
      r = row_dist(rng);
      c = columns - 1;
    }

    if (!(player.row() == r && player.column() == c))
    {
      current_row = r;
      current_column = c;
      scared = false;
      return;
    }
  }
}

void Bunny::mark_scared_if_adjacent(const Player &player)
{
  if (!is_alive())
  {
    return;
  }

  int pr = player.row();
  int pc = player.column();

  bool adjacent = (pr == current_row && std::abs(pc - current_column) == 1) ||
                  (pc == current_column && std::abs(pr - current_row) == 1);

  if (adjacent)
  {
    scared = true;
  }
}

void Bunny::move_end_of_day(int rows, int columns, const Player &player, std::mt19937 &rng)
{
  if (!is_alive())
  {
    return;
  }

  int new_r = current_row;
  int new_c = current_column;

  if (scared)
  {
    int dr = current_row - player.row();
    int dc = current_column - player.column();

    if (dr != 0)
    {
      dr = (dr > 0) ? 1 : -1;
      dc = 0;
    }
    else if (dc != 0)
    {
      dc = (dc > 0) ? 1 : -1;
      dr = 0;
    }

    new_r = current_row + 4 * dr;
    new_c = current_column + 4 * dc;

    scared = false; 
  }
  else
  {
    std::vector<std::pair<int, int>> options;
    options.push_back({current_row - 1, current_column});
    options.push_back({current_row + 1, current_column});
    options.push_back({current_row, current_column - 1});
    options.push_back({current_row, current_column + 1});

    std::shuffle(options.begin(), options.end(), rng);

    for (auto &opt : options)
    {
      int r = opt.first;
      int c = opt.second;

      if (r >= 0 && r < rows && c >= 0 && c < columns)
      {
        if (player.row() == r && player.column() == c)
        {
          continue;
        }
      }

      new_r = r;
      new_c = c;
      break;
    }
  }

  if (new_r < 0 || new_r >= rows || new_c < 0 || new_c >= columns)
  {
    despawn();
    return;
  }

  if (player.row() == new_r && player.column() == new_c)
  {
    return;
  }

  current_row = new_r;
  current_column = new_c;
}
