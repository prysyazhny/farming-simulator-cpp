#include <string>
#include <vector>

#include "farm.hpp"
#include "soil.hpp"

#include "vegetables/carrot.hpp"
#include "vegetables/beet.hpp"
#include "vegetables/lettuce.hpp"
#include "vegetables/spinach.hpp"
#include "vegetables/brussels_sprouts.hpp"

Farm::Farm(int rows, int columns, Player *player) : rows(rows), columns(columns), player(player), day_count(1)
{
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
  // only harvest if it's a fully grown vegetable
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

void Farm::end_day()
{
  day_count++;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      Plot *p = plots.at(i).at(j);
      Carrot *c = dynamic_cast<Carrot *>(p);
      if (c)
      {
        c->endDay();
      }
      Beet *b = dynamic_cast<Beet *>(p);
      if (b)
      {
        b->endDay();
      }
      Lettuce *l = dynamic_cast<Lettuce *>(p);
      if (l)
      {
        l->endDay();
      }
      Spinach *s = dynamic_cast<Spinach *>(p);
      if (s)
      {
        s->endDay();
      }
      BrusselsSprouts *br = dynamic_cast<BrusselsSprouts *>(p);
      if (br)
      {
        br->endDay();
      }
    }
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