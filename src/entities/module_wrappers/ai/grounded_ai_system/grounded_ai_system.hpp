#pragma once

#include "entity/modules/ai/movement/ai_movement_module.hpp"
#include "entity/modules/ai/navigation/ai_navigation_module.hpp"
#include "entity/modules/ai/perception/ai_perception_module.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle/particle.hpp"

class GroundedAISystem
{
  public:
    void update(Vec2<int> pos, const BoundingBox &bb,
                const ChunkMap<Particle> &particles, float dt)
    {
        auto neighborCheck = [&](int x, int y)
        {
            Vec2<int> a = bb.getA();
            Vec2<int> b = bb.getB();

            Vec2<int> corners[4] = {{x + a.x, y + a.y},
                                    {x + b.x, y + a.y},
                                    {x + a.x, y + b.y},
                                    {x + b.x, y + b.y}};

            for (int i = 0; i < 4; ++i)
            {
                const Particle *p = particles.get(corners[i].x, corners[i].y);

                if (!p)
                {
                    continue;
                }

                if (!p->isSolid())
                {
                    continue;
                }

                return false;
            }

            return true;
        };

        m_aiNavigation.update(dt, neighborCheck);

        if (m_aiNavigation.getPathState() ==
            AINavigationModule::PathState::Ready)
        {
            m_aiMovement.setCheckpoints(m_aiNavigation.getCheckpoints());
            m_aiNavigation.sleep();
        }

        m_aiMovement.update(pos, bb);
    }

    AIPerceptionModule &getPerception() { return m_aiPerception; }
    AINavigationModule &getNavigation() { return m_aiNavigation; }
    AIMovementModule &getMovement() { return m_aiMovement; }

  private:
    AIPerceptionModule m_aiPerception;
    AINavigationModule m_aiNavigation;
    AIMovementModule m_aiMovement;
};
