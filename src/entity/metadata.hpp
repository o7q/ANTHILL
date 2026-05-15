#pragma once

#include <string>

enum class EntityType
{
    Generic,
    Player,
    Projectile,
    Energy
};

struct EntityMetadata
{
    EntityType type  = EntityType::Generic;
    std::string name = "";
};
