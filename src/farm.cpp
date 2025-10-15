#include <string>
#include <vector>

#include "farm.hpp"

Farm::Farm(int rows, int columns) : rows(rows), columns(columns) {
  for(int i = 0; i < rows; i++) {
    std::vector<std::string> row;
    for(int j = 0; j < columns; j++) {
      row.push_back(".");
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
  return plots.at(row).at(column);
}
