#pragma once

#include <string>

#include "../plot.hpp"

class Spinach : public Plot
{
private:
  GrowthStage growth_stage;
  int age;
  const int daysToSprout = 2;
  const int daysToMature = 3;
  bool watered;

public:
  Spinach() : growth_stage(SEED), age(0), watered(false) {}
  std::string symbol() override;
  GrowthStage getGrowthStage() const;
  void endDay();
  bool isMature() const;
  void waterPlant();
};
