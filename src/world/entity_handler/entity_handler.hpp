#pragma once

#include "backend/time/time_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "events/event_pool.hpp"
#include "events/scene/base.hpp"
#include "world/entity_handler/id.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class EntityHandler
{
  public:
    struct EventPoolRefs
    {
        EventPool<SceneEvent> &scene;
        EventPool<ParticleEvent> &particle;
    };

  public:
    EntityHandler() {}
    EntityHandler(const EntityHandler &other)            = delete;
    EntityHandler &operator=(const EntityHandler &other) = delete;
    virtual ~EntityHandler()                             = default;

    void update(const ParticleHandler &world, TimeHandler::Info time, Vec2i origin,
                EventPoolRefs eventPoolRefs);

    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut);

    uint64_t addEntity(std::unique_ptr<Entity> entity);
    uint64_t addPlayer(std::unique_ptr<Player> player);

    Player *getCurrentPlayer();
    Entity *getLatestEntity();
    Entity *getEntity(uint64_t id);

    EntityIDHandler &getIDHandler() { return m_idHandler; }

    size_t getEntityCount() const { return m_entities.size(); }

  private:
    void handle_events(EventPool<EntityEvent> &events, EventPoolRefs eventPoolRefs);
    const std::unordered_map<uint64_t, const Entity *> get_nearby_entities(uint64_t nearID);

  private:
    EntityIDHandler m_idHandler;

    uint64_t m_currentPlayerID = 0;
    uint64_t m_latestEntityID  = 0;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;
    std::vector<uint64_t> m_entitiesToRemove;

    Vec2i m_globalKillRadius = {2000, 2000};
};
