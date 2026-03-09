#pragma once

#include "entity/living/living_entity.hpp"
#include "world/particle/particle_handler.hpp"

class AIEntity : public LivingEntity
{
  public:
    AIEntity(ParticleHandler &particles, Entity *target)
        : LivingEntity(particles)
    {
        m_interactionBox.getBoundingBox().setSize(10, 10);
        m_body.setGravity(0.5f);

        m_target = target;
    }
    AIEntity(const AIEntity &other) = delete;
    AIEntity &operator=(const AIEntity &other) = delete;
    virtual ~AIEntity() = default;

  protected:
    void setGoal(int x, int y) { m_goal = {x, y}; }

    void update(float dt) override
    {
        if (m_target)
        {
            setGoal(m_target->getBody().getPosition().x,
                    m_target->getBody().getPosition().y);
        }

        Vec2<int> pos = m_body.getPosition();

        if (pos.x < m_goal.x)
        {
            m_body.setVelocityX(3);
        }
        if (pos.x > m_goal.x)
        {
            m_body.setVelocityX(-3);
        }

        if (pos.y > m_goal.y &&
            m_body.getPosition().x == m_body.getLastPosition().x)
        {
            jump();
        }

        updateInternal(dt);
    }

  private:
    Vec2<int> m_goal = {0, 0};

    Entity *m_target = nullptr;
};
