// ...existing code...
#include "carrot.hpp"
#include <string>

std::string Carrot::symbol()
{
  if (growth_stage)
  {
    return "V";
  }
  else
  {
    return "v";
  }
}

bool Carrot::getGrowthStage() const
{
  return growth_stage;
}

void Carrot::grow()
{
  growth_stage = true;
}