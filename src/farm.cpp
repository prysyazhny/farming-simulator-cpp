#include <string>
#include <vector>

#include "farm.hpp"
#include "soil.hpp"

Farm::Farm(int rows, int columns) : rows(rows), columns(columns) {
  for(int i = 0; i < rows; i++) {
    std::vector<Plot *> row;
    for(int j = 0; j < columns; j++) {
      Soil *soil = new Soil();
      row.push_back(soil);
    }
    plots.push_back(row);
  }
}

int Farm::number_of_rows() {
  return rows;
}

int Farm::number_of_columns() {
  return columns;
}

std::string Farm::get_symbol(int row, int column) {
  return plots.at(row).at(column)->symbol();
}

void Farm::plant(int row, int column, Plot *plot) {
  Plot *current_plot = plots.at(row).at(column);
  plots.at(row).at(column) = plot;
  delete current_plot;
}