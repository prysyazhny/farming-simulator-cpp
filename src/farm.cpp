#include <string>
#include <vector>

#include "farm.hpp"
#include "soil.hpp"
#include "carrot.hpp"

Farm::Farm(int rows, int columns, Player *player) : rows(rows), columns(columns), player(player), day_count(0)
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
    return "🯅";
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

void Farm::harvest(int row, int column, Plot *plot)
{
  // only harvest if it's a fully grown carrot
  Plot *current_plot = plots.at(row).at(column);
  Carrot *carrot = dynamic_cast<Carrot *>(current_plot);
  if (!carrot || !carrot->getGrowthStage())
  {
    return; // nothing to harvest
  }
  // resets to blank soil plot
  Soil *soil = new Soil();
  plots.at(row).at(column) = soil;
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
        c->grow();
      }
    }
  }
}
