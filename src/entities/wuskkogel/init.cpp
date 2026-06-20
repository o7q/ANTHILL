#include "wuskkogel.hpp"

#include "identifiers/spritesheet.hpp"

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
    cfg.astarNeighborCheckFunction = [&](const EntityUpdateContext &context, px::Vec2i index)
    {
        const Navmesh::ChunkData *chunkData =
            context.particleHandler.getNavmesh().getChunkDataFromIndex(index);

        px::Vec2i pos = index * context.particleHandler.getNavmesh().getResolution().toInt();

        px::Vec2i a = m_collider.getPrimary().getA();
        px::Vec2i b = m_collider.getPrimary().getB();

        px::Vec2i topLeft     = pos + px::Vec2i{a.x, a.y};
        px::Vec2i topRight    = pos + px::Vec2i{b.x, a.y};
        px::Vec2i bottomLeft  = pos + px::Vec2i{a.x, b.y};
        px::Vec2i bottomRight = pos + px::Vec2i{b.x, b.y};

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

        if (!chunkData)
        {
            return true;
        }

        return !chunkData->containsSolid;
    };
    m_aiNavigation.setConfig(cfg);

    m_animator.setFPS(12);
    m_animator.restart();
}
