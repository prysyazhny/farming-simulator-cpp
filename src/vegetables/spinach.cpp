#include "spinach.hpp"

std::string Spinach::symbol()
{
    if (growth_stage == SEED)
    {
        return "x";
    }
    else if (growth_stage == SPROUT)
    {
        return "p";
    }
    else if (growth_stage == MATURE)
    {
        return "P";
    }
}

Plot::GrowthStage Spinach::getGrowthStage() const
{
    return growth_stage;
}

void Spinach::endDay()
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

bool Spinach::isMature() const
{
    return growth_stage == MATURE;
}

void Spinach::waterPlant()
{
    watered = true;
}