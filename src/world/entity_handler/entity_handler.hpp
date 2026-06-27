#pragma once

#include "entities/player/player.hpp"
#include "entity/entity.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "px/time/time_handler.hpp"
#include "px/canvas/draw_types.hpp"
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

    void update(const ParticleHandler &world, const px::TimeHandler &time, px::Vec2i origin,
                EventPoolRefs eventPoolRefs);

    void render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut);

    uint64_t addEntity(std::unique_ptr<Entity> entity);
    uint64_t addPlayer(std::unique_ptr<Player> player);

    Player *getCurrentPlayer();
    Entity *getLatestEntity();
    Entity *getEntity(uint64_t id);

    size_t getEntityCount() const { return m_entities.size(); }

  private:
    void handle_events(EventPool<EntityEvent> &events, EventPoolRefs eventPoolRefs);
    void get_other_entities(std::unordered_map<uint64_t, const Entity *> &out, uint64_t base);

  private:
    EntityIDHandler m_idHandler;

    uint64_t m_currentPlayerID = 0;
    uint64_t m_latestEntityID  = 0;
    std::unordered_map<uint64_t, std::unique_ptr<Entity>> m_entities;
    std::vector<std::unique_ptr<Entity>> m_entitiesToAdd;

    px::Vec2i m_globalKillRadius = {2000, 2000};
};
