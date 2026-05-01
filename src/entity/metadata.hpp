#pragma once

#include <string>

enum class EntityType
{
    Generic,
    Player,
    Projectile
};

struct EntityMetadata
{
    EntityType type  = EntityType::Generic;
    std::string name = "";
};
