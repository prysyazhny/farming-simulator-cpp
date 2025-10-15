#include <iostream>

#include "src/farm.hpp"
#include "src/farm_printer.hpp"

int main() {
  Farm farm(10, 5);
  FarmPrinter printer(&farm);
  std::cout << printer.pp();
}
