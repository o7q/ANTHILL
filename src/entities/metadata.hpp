#pragma once

enum class EntityType
{
    Generic,
    Player,
    Projectile
};

struct EntityMetadata
{
    EntityType type;
};
