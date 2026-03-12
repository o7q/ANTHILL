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
    TestEntity(ParticleHandler &particles)
        : Entity(particles), m_aiModule(particles.getParticles())
    {
        m_interactionBox.getBoundingBox().setSize(15, 20);
        m_body.setGravity(0.4f);

        m_aiModule.setSightAngle(100.0f);
        m_aiModule.setSightDistance(500);
        m_aiModule.setSightRayAmount(20);
        m_lookAngle = 0.0f;

        m_body.setPosition(100, 0);
    }

    void update(float dt,
                const std::vector<const Entity *> &nearbyEntities) override
    {
        Vec2<int> pos = m_body.getPosition();
        const Entity *target = nullptr;
        for (const Entity *entity : nearbyEntities)
        {
            if (entity->getMetadata().type == EntityType::Player)
            {
                target = entity;
                break;
            }
        }

        m_aiModule.checkForInterestsInSight(
            m_body.getPosition(), m_lookAngle,
            [&](int x, int y)
            {
                if (Particle *p = r_particleHandler.getParticles().get(x, y))
                {
                    if (p->isSolid())
                    {
                        return true;
                    }
                }

                Vec2<int> targetPos = target->getBody().getPosition();
                m_aiModule.setGoal(pos, targetPos);
                // if (target->getInteractionBox().pointInside(targetPos, x, y))
                // {
                //     return true;
                // }

                return false;
            });

        m_aiModule.update(pos, dt, r_particleHandler.getParticles());
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
