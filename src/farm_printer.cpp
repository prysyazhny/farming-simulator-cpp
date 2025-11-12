#include <string>

#include "farm.hpp"
#include "farm_printer.hpp"

FarmPrinter::FarmPrinter(Farm *farm) : farm(farm) {}

std::string FarmPrinter::pp()
{
  std::string legendLine1 = "Movement: WASD | Water: SPACE | Harvest: F | End Day: E | Quit: Q";
  std::string legendLine2 = "Plant Carrot: C | Plant Beet: B | Plant Lettuce: L | Plant Spinach: P | Plant Brussels Sprouts: R";
  std::string output = "";
  output += "\n\nDay " + std::to_string(farm->day_count) + " | " + legendLine1 + "\n"; // legend 1 and 2 on seperate lines
  output += legendLine2 + "\n\n";
  for (int i = 0; i < farm->number_of_rows(); i++)
  {
    for (int j = 0; j < farm->number_of_columns(); j++)
    {
      output += farm->get_symbol(i, j);
      output += " ";
    }
    output += "\n";
  }
  return output;
}
