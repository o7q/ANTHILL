#pragma once

#include "backend/viewport/render_command.hpp"
#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/backend/base.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "world/entity_handler/id.hpp"
#include "world/particle_world/particle_world.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class EntityHandler
{
  public:
    struct EventPoolRefs
    {
        EventPool<BackendEvent> &backend;
        EventPool<ParticleEvent> &particle;
    };

  public:
    EntityHandler() {}
    EntityHandler(const EntityHandler &other) = delete;
    EntityHandler &operator=(const EntityHandler &other) = delete;
    virtual ~EntityHandler() = default;

    void update(const ParticleWorld &world, float dt,
                EventPoolRefs eventPoolRefs);
    void handleEvents(EventPool<EntityEvent> &events,
                      EventPoolRefs eventPoolRefs);

    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut);

    void addEntity(std::unique_ptr<Entity> entity);
    void addPlayer(std::unique_ptr<Player> player);

    Player *getCurrentPlayer() { return m_currentPlayer; }
    Entity *getLatestEntity() { return m_latestEntity; }

    const std::vector<const Entity *>
        getNearbyEntities(/*const Entity *entity*/);

    EntityIDHandler &getIDHandler() { return m_idHandler; }

  private:
    EntityIDHandler m_idHandler;

    Player *m_currentPlayer = nullptr;
    Entity *m_latestEntity = nullptr;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;
    std::vector<uint64_t> m_entitiesToRemove;
};
