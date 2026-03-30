#pragma once

#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/backend/base.hpp"
#include "events/event_emitter.hpp"
#include "world/entity_handler/id.hpp"
#include "world/particle/particle_world.hpp"
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

    void update(const ParticleWorld &world, float dt);
    void handleEvents(EventEmitter<EntityEvent> &emitter);

    void render(Viewport &viewport, const Camera &camera);

    void addEntity(std::unique_ptr<Entity> entity);
    void addPlayer(std::unique_ptr<Player> player);

    Player *getCurrentPlayer() { return m_currentPlayer; }
    Entity *getLatestEntity() { return m_latestEntity; }

    const std::vector<const Entity *> getNearbyEntities(const Entity *entity);

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
