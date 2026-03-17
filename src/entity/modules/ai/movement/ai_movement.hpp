#pragma once

#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include <vector>

class AIMovement
{
  public:
    AIMovement() = default;
    virtual ~AIMovement() = default;

    void update(Vec2<int> pos, const StaticGridRectangle &bb);

    void
    setCheckpoints(const std::vector<AINavigation::Checkpoint> &checkpoints)
    {
        // copy checkpoints
        m_checkpoints = checkpoints;
    }

    const std::vector<AINavigation::Checkpoint> &getMutatedCheckpoints() const
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

    std::vector<AINavigation::Checkpoint> m_checkpoints;
    AINavigation::Checkpoint m_previousCheckpoint;
};
