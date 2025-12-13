#pragma once

#include <string>

class Farm;

class FarmPrinter
{
private:
  Farm *farm;

public:
  FarmPrinter(Farm *farm);
  std::string pp();
};
