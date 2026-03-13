#include "entity_ai_module.hpp"

void AIModule::setGoal(Vec2<int> startPos, Vec2<int> endPos, bool force)
{
    m_goalStartPos = startPos;
    m_goalEndPos = endPos;

    if (m_goalSet && !force)
    {
        return;
    }

    m_astar.reset(startPos, endPos);
    m_goalSet = true;
}

void AIModule::clearGoal()
{
    m_pathCheckpoints.clear();
    m_goalSet = false;
}

bool AIModule::isGoalAlreadySet(Vec2<int> start, Vec2<int> end)
{
    return start == m_goalStartPos && end == m_goalEndPos;
}
