#pragma once

#include <string>

enum class EntityFaction
{
    Generic,
    Player
};

struct EntityMetadata
{
    EntityFaction faction = EntityFaction::Generic;
    std::string name = "";
};
