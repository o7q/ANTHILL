#pragma once

#include <cstdint>
#include <functional>
#include <memory>

class Entity;

struct EntitySpawnEvent
{
    EntitySpawnEvent(const uint64_t caller) : caller(caller) {}

    std::function<std::unique_ptr<Entity>(uint64_t id)> entityFactory;
    const uint64_t caller;
};

struct EntityDamageEvent
{
    EntityDamageEvent(const uint64_t caller) : caller(caller) {}

    uint64_t target = 0;
    float damage = 0.0f;
    const uint64_t caller;
};
