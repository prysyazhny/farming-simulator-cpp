#pragma once

#include <string>

#include "../plot.hpp"

class Beet : public Plot
{
private:
  GrowthStage growth_stage;
  int age;
  const int daysToSprout = 2;
  const int daysToMature = 5;
  bool watered;

public:
  Beet() : growth_stage(SEED), age(0), watered(false) {}
  std::string symbol() override;
  GrowthStage getGrowthStage() const;
  void endDay();
  bool isMature() const;
  void waterPlant();
};
