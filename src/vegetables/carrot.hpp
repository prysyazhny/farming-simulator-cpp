#pragma once

#include <string>

#include "../plot.hpp"

class Carrot : public Plot
{
private:
  GrowthStage growth_stage;
  int age;
  const int daysToSprout = 1;
  const int daysToMature = 1;
  bool watered;

public:
  Carrot() : growth_stage(SEED), age(0), watered(false) {}
  std::string symbol() override;
  GrowthStage getGrowthStage() const;
  void endDay();
  bool isMature() const;
  void waterPlant();
};
