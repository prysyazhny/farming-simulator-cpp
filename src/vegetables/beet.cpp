#include "beet.hpp"

std::string Beet::symbol()
{
    if (growth_stage == SEED)
    {
        return "x";
    }
    else if (growth_stage == SPROUT)
    {
        return "b";
    }
    else if (growth_stage == MATURE)
    {
        return "B";
    }
    return "";
}

Plot::GrowthStage Beet::getGrowthStage() const
{
    return growth_stage;
}

void Beet::endDay()
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

bool Beet::isMature() const
{
    return growth_stage == MATURE;
}

void Beet::waterPlant()
{
    watered = true;
}