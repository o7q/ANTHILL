#pragma once

#include "core/time/time_handler.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
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
        EventPool<ExternalEvent> &external;
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

    size_t getEntityCount() const { return m_entities.size(); }

  private:
    void handle_events(EventPool<EntityEvent> &events, EventPoolRefs eventPoolRefs);
    std::unordered_map<uint64_t, const Entity *> get_other_entities(uint64_t base);

  private:
    EntityIDHandler m_idHandler;

    uint64_t m_currentPlayerID = 0;
    uint64_t m_latestEntityID  = 0;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;
    std::vector<uint64_t> m_entitiesToRemove;

    Vec2i m_globalKillRadius = {2000, 2000};
};
