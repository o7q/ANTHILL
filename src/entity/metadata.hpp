#pragma once

#include <string>

enum class EntityType
{
    Generic,
    Player,
    Projectile,
    Collectible
};

struct EntityMetadata
{
    EntityType type  = EntityType::Generic;
    std::string name = "";
};
