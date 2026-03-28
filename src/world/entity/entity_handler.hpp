#pragma once

#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/backend/base.hpp"
#include "events/event_emitter.hpp"
#include "world/entity/id.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class EntityHandler
{
  public:
    EntityHandler(EventEmitter<BackendEvent> &backendEvents,
                  EventEmitter<ParticleEvent> &particleEvents)
        : r_backendEvents(backendEvents), r_particleEvents(particleEvents)
    {
    }
    EntityHandler(const EntityHandler &other) = delete;
    EntityHandler &operator=(const EntityHandler &other) = delete;

    void update(const ParticleHandler &particleHandler, float dt);
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
    EventEmitter<BackendEvent> &r_backendEvents;
    EventEmitter<ParticleEvent> &r_particleEvents;

    EntityIDHandler m_idHandler;

    Player *m_currentPlayer = nullptr;
    Entity *m_latestEntity = nullptr;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;
    std::vector<uint64_t> m_entitiesToRemove;
};
