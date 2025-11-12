#pragma once

#include <string>

class Plot
{
  private:
    int age;
public:
  enum GrowthStage
  {
    SEED,
    SPROUT,
    MATURE
  };
  virtual ~Plot() = default;
  virtual std::string symbol() = 0;
};
