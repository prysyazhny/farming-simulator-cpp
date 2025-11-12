#include "carrot.hpp"

std::string Carrot::symbol()
{
  if (growth_stage == SEED)
  {
    return "x";
  }
  else if (growth_stage == SPROUT)
  {
    return "c";
  }
  else if (growth_stage == MATURE)
  {
    return "C";
  }
  return "";
}

Plot::GrowthStage Carrot::getGrowthStage() const
{
  return growth_stage;
}

void Carrot::endDay()
{
  if (watered)
  {
    age++;
    watered = false;
  }
  age++;
  if (age >= daysToMature + daysToSprout)
  {
    growth_stage = MATURE;
  }
  else if (age == daysToSprout)
  {
    growth_stage = SPROUT;
  }
}

bool Carrot::isMature() const
{
  return growth_stage == MATURE;
}

void Carrot::waterPlant()
{
  watered = true;
}