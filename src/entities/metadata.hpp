#pragma once

enum class EntityType
{
    None,
    Player
};

struct EntityMetadata
{
    EntityType type;
};
