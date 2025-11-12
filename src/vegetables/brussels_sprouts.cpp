#include "brussels_sprouts.hpp"

std::string BrusselsSprouts::symbol()
{
    if (growth_stage == SEED)
    {
        return "x";
    }
    else if (growth_stage == SPROUT)
    {
        return "r";
    }
    else if (growth_stage == MATURE)
    {
        return "R";
    }
    return "";
}

Plot::GrowthStage BrusselsSprouts::getGrowthStage() const
{
    return growth_stage;
}

void BrusselsSprouts::endDay()
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

bool BrusselsSprouts::isMature() const
{
    return growth_stage == MATURE;
}

void BrusselsSprouts::waterPlant()
{
    watered = true;
}