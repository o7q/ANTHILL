#pragma once

#include "math/angle.hpp"
#include "math/line.hpp"
#include <vector>

class AIPerception
{
  public:
    AIPerception() = default;
    virtual ~AIPerception() = default;

    template <typename CheckFunction>
    void checkForInterestsInSight(Vec2i headPos, float headAngle,
                                  CheckFunction &&function)
    {
        m_sightPoints.clear();

        float angleTop =
            Math::Angle::degreesToRadians(headAngle - m_sightFOV / 2.0f);

        float increment =
            Math::Angle::degreesToRadians(m_sightFOV) / (m_sightRayAmount - 1);

        for (int i = 0; i < m_sightRayAmount; ++i)
        {
            float angle = angleTop + i * increment;

            Math::Line::bresenhamRaycast(
                headPos, angle,
                [&](int x, int y)
                {
                    if (function(x, y))
                    {
                        return true;
                    }

                    m_sightPoints.push_back(Vec2i(x, y));

                    return false;
                },
                m_sightDistance);
        }
    }

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightFOV(float fov) { m_sightFOV = fov; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

  private:
    std::vector<Vec2i> m_sightPoints;

    float m_detectionRadius = 0.0f;
    float m_sightFOV = 90.0f;
    int m_sightDistance = 100;
    int m_sightRayAmount = 10;
};
