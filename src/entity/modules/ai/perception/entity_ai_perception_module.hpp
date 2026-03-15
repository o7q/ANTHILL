#pragma once

#include "backend/viewport.hpp"
#include "utils/bounding_box.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/line.hpp"
#include "world/camera/camera.hpp"
#include <vector>

class EntityAIPerceptionModule
{
  public:
    EntityAIPerceptionModule() {}

    // template <typename CheckFunction>
    // void checkForBoundingBoxInSight(Vec2<int> headPos, float headAngle,
    //                                 Vec2<int> boxPosition,
    //                                 const BoundingBox &box,
    //                                 CheckFunction &&function)
    // {
    //     for (int i = 0; i < box.getSize().x; ++i)
    //     {
            
    //     }

    //     for (int i = 0; i < box.getSize().x; ++i)
    //     {

    //     }
    // }

    template <typename CheckFunction>
    void checkForInterestsInSight(Vec2<int> headPos, float headAngle,
                                  CheckFunction &&function)
    {
        m_sightPoints.clear();

        float angleTop =
            Utils::Math::Angle::degreesToRadians(headAngle - m_sightFOV / 2.0f);

        float increment = Utils::Math::Angle::degreesToRadians(m_sightFOV) /
                          (m_sightRayAmount - 1);

        for (int i = 0; i < m_sightRayAmount; ++i)
        {
            float angle = angleTop + i * increment;

            Utils::Math::Line::bresenhamRaycast(
                headPos, angle,
                [&](int x, int y)
                {
                    if (function(x, y))
                    {
                        return true;
                    }

                    m_sightPoints.push_back(Vec2<int>(x, y));

                    return false;
                },
                m_sightDistance);
        }
    }

    void renderDebug(Viewport &viewport, const Camera &camera);

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightFOV(float fov) { m_sightFOV = fov; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

  private:
    std::vector<Vec2<int>> m_sightPoints;

    float m_detectionRadius = 0.0f;
    float m_sightFOV = 90.0f;
    int m_sightDistance = 100;
    int m_sightRayAmount = 10;
};
