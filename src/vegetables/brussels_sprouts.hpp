#pragma once

#include <string>

#include "../plot.hpp"

class BrusselsSprouts : public Plot
{
private:
  GrowthStage growth_stage;
  int age;
  const int daysToSprout = 5;
  const int daysToMature = 10;
  bool watered;

public:
  BrusselsSprouts() : growth_stage(SEED), age(0), watered(false) {}
  std::string symbol() override;
  GrowthStage getGrowthStage() const;
  void endDay();
  bool isMature() const;
  void waterPlant();
};
