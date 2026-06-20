#pragma once

#include "px/basic_types/angle.hpp"
#include "px/utils/line.hpp"
#include <vector>

class AIPerception
{
  public:
    AIPerception()          = default;
    virtual ~AIPerception() = default;

    template <typename CheckFunction> void scan(px::Vec2i headPos, float headAngle, CheckFunction &&function)
    {
        m_sightPoints.clear();

        float angleTop = headAngle - m_sightFOV / 2.0f;

        float increment = m_sightFOV / (m_sightRayAmount - 1);

        for (int i = 0; i < m_sightRayAmount; ++i)
        {
            px::Angle angle = px::Degrees(angleTop + i * increment);

            px::Utils::Lines::bresenhamRaycast(
                headPos, angle,
                [&](px::Vec2i pos)
                {
                    if (function(pos))
                    {
                        return true;
                    }

                    m_sightPoints.push_back(pos);

                    return false;
                },
                m_sightDistance);
        }
    }

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightFOV(float fov) { m_sightFOV = fov; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

    const std::vector<px::Vec2i> &getSightPoints() const { return m_sightPoints; }

  private:
    std::vector<px::Vec2i> m_sightPoints;

    float m_detectionRadius = 0.0f;
    float m_sightFOV        = 90.0f;
    int m_sightDistance     = 100;
    int m_sightRayAmount    = 10;
};
