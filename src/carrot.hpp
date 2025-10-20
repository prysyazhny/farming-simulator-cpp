#pragma once

#include <string>

#include "plot.hpp"

class Carrot : public Plot
{
private:
  bool growth_stage;

public:
  Carrot() : growth_stage(false) {}
  std::string symbol() override;
  bool getGrowthStage() const;
  void grow();
};
