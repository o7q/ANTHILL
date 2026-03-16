#pragma once

#include "backend/utils/vec.hpp"
#include "entity/modules/ai/navigation/ai_navigation_module.hpp"
#include "utils/bounding_box.hpp"
#include <vector>

class AIMovementModule
{
  public:
    void update(Vec2<int> pos, const BoundingBox &box);

    void setCheckpoints(
        const std::vector<AINavigationModule::Checkpoint> &checkpoints)
    {
        // copy checkpoints
        m_checkpoints = checkpoints;
    }

    const std::vector<AINavigationModule::Checkpoint> &
    getMutatedCheckpoints() const
    {
        return m_checkpoints;
    }

    bool shouldMove() const { return m_shouldMove; }
    bool shouldSetPosition() const { return m_shouldSetPosition; }
    Vec2<int> getMoveDirection() const { return m_moveDirection; }
    Vec2<int> getSetPosition() const { return m_setPosition; }

  private:
    bool m_shouldMove = false;
    Vec2<int> m_moveDirection;
    bool m_shouldSetPosition = false;
    Vec2<int> m_setPosition;

    std::vector<AINavigationModule::Checkpoint> m_checkpoints;
    AINavigationModule::Checkpoint m_previousCheckpoint;
};
