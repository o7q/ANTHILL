#pragma once

#include "backend/utils/vec.hpp"
#include "entity/modules/ai/navigation/entity_ai_navigation_module.hpp"
#include "utils/bounding_box.hpp"
#include "utils/math/numbers.hpp"
#include <iostream>
#include <vector>

class EntityAIMovementModule
{
  public:
    void update(Vec2<int> pos, const BoundingBox &box)
    {
        m_shouldJump = false;
        m_shouldSetPosition = false;
        m_moveDirection = 0;

        if (m_checkpoints.empty())
        {
            return;
        }

        EntityAINavigationModule::Checkpoint current;
        while (true)
        {
            if (m_checkpoints.empty())
            {
                return;
            }

            current = m_checkpoints[0];

            bool breakout = false;

            switch (current.axis)
            {
            case EntityAINavigationModule::Axis::Horizontal:
                if (current.pos.x >= box.getA().x + pos.x &&
                    current.pos.x <= box.getB().x + pos.x)
                {
                    m_checkpoints.erase(m_checkpoints.begin());
                }
                else
                {
                    breakout = true;
                }
                break;
            case EntityAINavigationModule::Axis::Vertical:
                if (current.pos.y >= box.getA().y + pos.y &&
                    current.pos.y <= box.getB().y + pos.y)
                {
                    m_checkpoints.erase(m_checkpoints.begin());
                }
                else
                {
                    breakout = true;
                }
                break;
            }

            if (breakout)
            {
                break;
            }
        }

        if (m_previousCheckpoint.axis ==
                EntityAINavigationModule::Axis::Horizontal &&
            current.axis == EntityAINavigationModule::Axis::Vertical)
        {
            m_setPosition = current.pos;
            m_shouldSetPosition = true;
        }
        else
        {
            int dirX = Utils::Math::Numbers::sign(current.pos.x - pos.x);
            m_moveDirection = dirX;
        }

        if (current.pos.y < pos.y)
        {
            m_shouldJump = true;
        }

        m_previousCheckpoint = current;
    }

    void setCheckpoints(
        const std::vector<EntityAINavigationModule::Checkpoint> &checkpoints)
    {
        // copy checkpoints
        m_checkpoints = checkpoints;
    }

    const std::vector<EntityAINavigationModule::Checkpoint> &
    getMutatedCheckpoints() const
    {
        return m_checkpoints;
    }

    bool shouldJump() const { return m_shouldJump; }
    bool shouldSetPosition() const { return m_shouldSetPosition; }
    int getMoveDirection() const { return m_moveDirection; }
    Vec2<int> getSetPosition() const { return m_setPosition; }

  private:
    bool m_shouldJump = false;
    bool m_shouldSetPosition = false;
    int m_moveDirection = 0;
    Vec2<int> m_setPosition;

    std::vector<EntityAINavigationModule::Checkpoint> m_checkpoints;
    EntityAINavigationModule::Checkpoint m_previousCheckpoint;
};
