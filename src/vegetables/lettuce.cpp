#include "lettuce.hpp"

std::string Lettuce::symbol()
{
    if (growth_stage == SEED)
    {
        return "x";
    }
    else if (growth_stage == SPROUT)
    {
        return "l";
    }
    else if (growth_stage == MATURE)
    {
        return "L";
    }
    return "";
}

Plot::GrowthStage Lettuce::getGrowthStage() const
{
    return growth_stage;
}

void Lettuce::endDay()
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

bool Lettuce::isMature() const
{
    return growth_stage == MATURE;
}

void Lettuce::waterPlant()
{
    watered = true;
}