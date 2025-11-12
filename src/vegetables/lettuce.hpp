#pragma once

#include <string>

#include "../plot.hpp"

class Lettuce : public Plot
{
private:
  GrowthStage growth_stage;
  int age;
  const int daysToSprout = 2;
  const int daysToMature = 2;
  bool watered;

public:
  Lettuce() : growth_stage(SEED), age(0), watered(false) {}
  std::string symbol() override;
  GrowthStage getGrowthStage() const;
  void endDay();
  bool isMature() const;
  void waterPlant();
};
