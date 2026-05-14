#include "wuskkogel.hpp"

#include "entities/player_point/player_point.hpp"
#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include <memory>

Wuskkogel::Wuskkogel(const Assets &assets, uint64_t id)
    : Entity(id), m_bodyHandler(m_body, m_collider),
      m_animator(assets.spriteSheets().get(SpriteSheetID::Entity_Wuskkogel))
{
    m_metadata.name = "Wuskkogel";

    m_collider.addRect({}, {18, 24});
    m_body.setGravity(0.0f);
    m_body.setTargetDamping({0.92f, 0.92f});

    m_idleSoundTimer.restart();

    m_health = 40.0f;

    m_aiPerception.setSightFOV(120);
    m_aiPerception.setSightRayAmount(20);
    m_aiPerception.setSightDistance(500);

    AINavigation::Config cfg;
    cfg.iterationsPerFrame         = 10;
    cfg.satisfactoryDistance       = 20.0f;
    cfg.maxStuckTime               = 0.5f;
    cfg.checkpointEatRadius        = 10;
    cfg.astar.endCutoffAmount      = 5;
    cfg.astar.maxIterations        = 100000;
    cfg.astarNeighborCheckFunction = [&](const EntityUpdateContext &context, Index2D index)
    {
        auto data = context.particleHandler.getNavmesh().getChunkFromIndex(index);

        Vec2i pos = Vec2i(index.x, index.y) * context.particleHandler.getNavmesh().getResolution().toInt();

        Vec2i a = m_collider.getPrimary().getA();
        Vec2i b = m_collider.getPrimary().getB();

        Vec2i topLeft     = pos + Vec2i(a.x, a.y);
        Vec2i topRight    = pos + Vec2i(b.x, a.y);
        Vec2i bottomLeft  = pos + Vec2i(a.x, b.y);
        Vec2i bottomRight = pos + Vec2i(b.x, b.y);

        bool impassible = false;

        auto test = [&](const Particle *p)
        {
            if (!p || p->isSolid())
            {
                impassible = true;
                return true;
            }

            return false;
        };

        context.particleHandler.query(topLeft, topRight, test, false);
        context.particleHandler.query(topLeft, bottomLeft, test, false);
        context.particleHandler.query(bottomLeft, bottomRight, test, false);
        context.particleHandler.query(topRight, bottomRight, test, false);

        if (impassible)
        {
            return false;
        }

        if (!data)
        {
            return true;
        }

        return !data->containsSolid;
    };
    m_aiNavigation.setConfig(cfg);

    m_animator.setFPS(12);
    m_animator.restart();

    m_onKillFunction = [&](EventPool<EntityEvent> &eventsOut, const EntityUpdateContext &context)
    {
        auto pointSpawn      = std::make_unique<PlayerPoint>(m_body.getPosition());
        auto pointSpawnEvent = std::make_unique<EntitySpawnEvent>(context.id, std::move(pointSpawn));
        eventsOut.emit(std::move(pointSpawnEvent));
    };
}
