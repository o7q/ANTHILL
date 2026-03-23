#pragma once

#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "entity/events.hpp"
#include "entity/update_context.hpp"
#include "world/entity/id.hpp"
#include "world/particle/particle_handler.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class EntityHandler
{
  public:
    EntityHandler(ParticleHandler &particleHandler)
        : r_particleHandler(particleHandler)
    {
    }
    EntityHandler(const EntityHandler &other) = delete;
    EntityHandler &operator=(const EntityHandler &other) = delete;

    void update(float dt);
    void handleEvents(Entity *entity);

    void render(Viewport &viewport, const Camera &camera);

    void addEntity(std::unique_ptr<Entity> entity)
    {
        m_latestEntity = entity.get();
        m_entities[entity->getID()] = std::move(entity);
    }

    void addPlayer(std::unique_ptr<Player> player)
    {
        m_currentPlayer = player.get();
        addEntity(std::move(player));
    }

    Player *getCurrentPlayer() { return m_currentPlayer; }
    Entity *getLatestEntity() { return m_latestEntity; }

    const std::vector<const Entity *> getNearbyEntities(const Entity *entity)
    {
        std::vector<const Entity *> nearby;
        for (auto &entity : m_entities)
        {
            nearby.push_back(entity.second.get());
        }
        return nearby;
    }

    EntityIDHandler &getIDHandler() { return m_idHandler; }

  private:
    ParticleHandler &r_particleHandler;
    EntityIDHandler m_idHandler;

    Player *m_currentPlayer = nullptr;
    Entity *m_latestEntity = nullptr;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;
    std::vector<uint64_t> m_entitiesToRemove;
};
