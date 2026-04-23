#include "identifiers/assets/spritesheet.hpp"
#include "wuskkogel.hpp"

Wuskkogel::Wuskkogel(uint64_t id, const Assets &assets)
    : Entity(id), m_bodyHandler(m_body, m_boundingBox),
      m_animator(*assets.spriteSheets().get(SpriteSheetID::Entity_Wuskkogel))
{
    m_metadata.name = "Wuskkogel";

    m_boundingBox.setSize({12, 16});
    m_body.setGravity(0.0f);
    m_body.setTargetDamping({0.92f, 0.92f});

    m_aiPerception.setSightFOV(120);
    m_aiPerception.setSightRayAmount(20);
    m_aiPerception.setSightDistance(500);

    AINavigation::Config cfg;
    cfg.astarIterationsPerFrame = 100;
    cfg.stuckTemper = 100;
    cfg.astarTerminationDistance = 0;
    cfg.astarMaxIterations = 10000000;
    cfg.checkpointEatRadius = 10;
    cfg.astarNeighborCheckFunction =
        [&](const EntityUpdateContext &context, Index2D index)
    {
        auto data =
            context.particleHandler.getNavmesh().getChunkFromIndex(index);

        Vec2i pos =
            Vec2i(index.x, index.y) *
            context.particleHandler.getNavmesh().getResolution().toInt();

        Vec2i a = m_boundingBox.getA();
        Vec2i b = m_boundingBox.getB();

        Vec2i topLeft = pos + Vec2i(a.x, a.y);
        Vec2i topRight = pos + Vec2i(b.x, a.y);
        Vec2i bottomLeft = pos + Vec2i(a.x, b.y);
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
}
