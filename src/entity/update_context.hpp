#pragma once

#include "core/time/time_handler.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <cstdint>
#include <unordered_map>

class Entity;
class Player;

struct EntityUpdateContext
{
    const uint64_t id = 0;
    const TimeHandler::Info time;
    const ParticleHandler &particleHandler;
    const std::unordered_map<uint64_t, const Entity *> &otherEntities;
    uint64_t currentPlayerID    = 0;
    const Player *currentPlayer = nullptr;
    const float distanceToCurrentPlayer;
    const Vec2f vectorTowardsCurrentPlayer;
};
