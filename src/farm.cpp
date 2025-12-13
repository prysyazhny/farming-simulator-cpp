#include <string>
#include <vector>
#include <random>
#include <ctime>

#include "farm.hpp"
#include "soil.hpp"

#include "vegetables/carrot.hpp"
#include "vegetables/beet.hpp"
#include "vegetables/lettuce.hpp"
#include "vegetables/spinach.hpp"
#include "vegetables/brussels_sprouts.hpp"

Farm::Farm(int rows, int columns, Player *player)
    : rows(rows), columns(columns), player(player), day_count(1)
{
  rng = std::mt19937(static_cast<unsigned int>(std::time(nullptr)));

  for (int i = 0; i < rows; i++)
  {
    std::vector<Plot *> row;
    for (int j = 0; j < columns; j++)
    {
      Soil *soil = new Soil();
      row.push_back(soil);
    }
    plots.push_back(row);
  }
}

int Farm::number_of_rows()
{
  return rows;
}

int Farm::number_of_columns()
{
  return columns;
}

std::string Farm::get_symbol(int row, int column)
{
  if (player->row() == row && player->column() == column)
  {
    return "@";
  }
  else if (bunny.is_alive() && bunny.row() == row && bunny.column() == column)
  {
    return bunny.symbol();
  }
  else
  {
    return plots.at(row).at(column)->symbol();
  }
}

void Farm::plant(int row, int column, Plot *plot)
{
  Plot *current_plot = plots.at(row).at(column);
  plots.at(row).at(column) = plot;
  delete current_plot;
}

void Farm::harvest(int row, int column, Plot * /*unused*/)
{
  Plot *current_plot = plots.at(row).at(column);

  if (Carrot *c = dynamic_cast<Carrot *>(current_plot))
  {
    if (c->isMature())
    {
      delete current_plot;
      plots.at(row).at(column) = new Soil();
    }
    return;
  }

  if (Beet *b = dynamic_cast<Beet *>(current_plot))
  {
    if (b->isMature())
    {
      delete current_plot;
      plots.at(row).at(column) = new Soil();
    }
    return;
  }

  if (Lettuce *l = dynamic_cast<Lettuce *>(current_plot))
  {
    if (l->isMature())
    {
      delete current_plot;
      plots.at(row).at(column) = new Soil();
    }
    return;
  }

  if (Spinach *s = dynamic_cast<Spinach *>(current_plot))
  {
    if (s->isMature())
    {
      delete current_plot;
      plots.at(row).at(column) = new Soil();
    }
    return;
  }

  if (BrusselsSprouts *br = dynamic_cast<BrusselsSprouts *>(current_plot))
  {
    if (br->isMature())
    {
      delete current_plot;
      plots.at(row).at(column) = new Soil();
    }
    return;
  }
}

void Farm::water(int row, int column, Plot * /*unused*/)
{
  Plot *current_plot = plots.at(row).at(column);

  if (Carrot *c = dynamic_cast<Carrot *>(current_plot))
  {
    c->waterPlant();
    return;
  }
  if (Beet *b = dynamic_cast<Beet *>(current_plot))
  {
    b->waterPlant();
    return;
  }
  if (Lettuce *l = dynamic_cast<Lettuce *>(current_plot))
  {
    l->waterPlant();
    return;
  }
  if (Spinach *s = dynamic_cast<Spinach *>(current_plot))
  {
    s->waterPlant();
    return;
  }
  if (BrusselsSprouts *br = dynamic_cast<BrusselsSprouts *>(current_plot))
  {
    br->waterPlant();
    return;
  }
}

void Farm::maybe_spawn_bunny()
{
  if (bunny.is_alive())
  {
    return;
  }

  std::uniform_int_distribution<int> percent(1, 100);
  if (percent(rng) > bunny_spawn_percent)
  {
    return;
  }

  bunny.spawn_random_edge(rows, columns, *player, rng);
}

void Farm::eat_vegetable_under_bunny()
{
  if (!bunny.is_alive())
  {
    return;
  }

  Plot *current_plot = plots.at(bunny.row()).at(bunny.column());

  if (dynamic_cast<Carrot *>(current_plot) || dynamic_cast<Beet *>(current_plot) ||
      dynamic_cast<Lettuce *>(current_plot) || dynamic_cast<Spinach *>(current_plot) ||
      dynamic_cast<BrusselsSprouts *>(current_plot))
  {
    delete current_plot;
    plots.at(bunny.row()).at(bunny.column()) = new Soil();
  }
}

void Farm::check_bunny_scared()
{
  bunny.mark_scared_if_adjacent(*player);
}

void Farm::end_day()
{
  bunny.move_end_of_day(rows, columns, *player, rng);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      Plot *p = plots.at(i).at(j);

      if (Carrot *c = dynamic_cast<Carrot *>(p))
        c->endDay();
      if (Beet *b = dynamic_cast<Beet *>(p))
        b->endDay();
      if (Lettuce *l = dynamic_cast<Lettuce *>(p))
        l->endDay();
      if (Spinach *s = dynamic_cast<Spinach *>(p))
        s->endDay();
      if (BrusselsSprouts *br = dynamic_cast<BrusselsSprouts *>(p))
        br->endDay();
    }
  }

  day_count++;

  maybe_spawn_bunny();

  eat_vegetable_under_bunny();
}
