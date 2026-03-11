#pragma once

#include "backend/viewport.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/line.hpp"
#include "world/camera/camera.hpp"
#include <vector>

class AIModule
{
  public:
    enum class GoalType
    {
        Attack,
        Follow
    };

    struct Goal
    {
        GoalType type;
        int actRadius = 40;
        Vec2<int> pos;
    };

  public:
    AIModule() {}

    void update(Vec2<int> headPos, float angle) {}

    template <typename CheckFunction>
    void checkForInterestsInSight(Vec2<int> headPos, float headAngle,
                                  CheckFunction &&function)
    {
        m_sightPoints.clear();

        float angleTop = Utils::Math::Angle::degreesToRadians(
            headAngle - m_sightAngle / 2.0f);

        float increment = Utils::Math::Angle::degreesToRadians(m_sightAngle) /
                          (m_sightRayAmount - 1);

        for (int i = 0; i < m_sightRayAmount; ++i)
        {
            float a = angleTop + i * increment;

            auto test = [&](int x, int y)
            {
                if (function(x, y))
                {
                    return true;
                }

                m_sightPoints.push_back(Vec2<int>(x, y));

                return false;
            };

            Utils::Math::Line::bresenhamRaycast(headPos, a, test,
                                                m_sightDistance);
        }
    }

    void setGoal(int x, int y)
    {
        m_goal.x = x;
        m_goal.y = y;
    }

    void renderDebug(Viewport &viewport, const Camera &camera,
                     Vec2<int> headPos, float headAngle)
    {
        for (Vec2<int> p : m_sightPoints)
        {
            Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
            viewport.setPixel(ppos.x, ppos.y, Color(255, 252, 99));
        }
    }

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightAngle(float angle) { m_sightAngle = angle; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

  private:
    std::vector<Vec2<int>> m_sightPoints;

    float m_detectionRadius = 0.0f;
    float m_sightAngle = 0.0f;
    int m_sightDistance = 0;
    int m_sightRayAmount = 7;

    Vec2<int> m_goal = {0, 0};
};
