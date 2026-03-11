#pragma once

#include "backend/viewport.hpp"
#include "entities/metadata.hpp"
#include "entity/base/entity.hpp"
#include "entity/mixins/directional.hpp"
#include "entity/modules/ai/entity_ai_module.hpp"
#include "entity/modules/jump/entity_jump_module.hpp"
#include "world/camera/camera.hpp"

class TestEntity : public Entity, public IDirectional
{
  public:
    TestEntity(ParticleHandler &particles) : Entity(particles)
    {
        m_interactionBox.getBoundingBox().setSize(15, 20);
        m_body.setGravity(0.4f);

        m_aiModule.setSightAngle(40.0f);
        m_aiModule.setSightDistance(150);
        m_lookAngle = 0.0f;
    }

    void update(float dt,
                const std::vector<const Entity *> &nearbyEntities) override
    {
        Vec2<int> pos = m_body.getPosition();
        Vec2<int> goal = pos;
        for (const Entity *entity : nearbyEntities)
        {
            if (entity->getMetadata().type == EntityType::Player)
            {
                goal = entity->getBody().getPosition();
                break;
            }
        }

        auto check = [&](int x, int y)
        {
            if (Particle *p = r_particleHandler.getParticles().get(x, y))
            {
                if (p->isSolid())
                {
                    return true;
                }
            }

            return false;
        };

        m_aiModule.checkForInterestsInSight(m_body.getPosition(), m_lookAngle,
                                            check);
        updateMotion(dt);
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);
        m_aiModule.renderDebug(viewport, camera, m_body.getPosition(),
                               m_lookAngle);
    }

  private:
    JumpModule m_jumpModule;
    AIModule m_aiModule;
};
