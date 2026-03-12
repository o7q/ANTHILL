#pragma once

#include "backend/viewport.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/line.hpp"
#include "utils/pathfinding/a_star_world.hpp"
#include "world/camera/camera.hpp"
#include <iostream>
#include <vector>

class AIModule
{
  public:
    AIModule(ChunkMap<Particle> &particles) : astar(particles)
    {
        astar.setMaxIterations(100000);
    }

    void update(Vec2<int> headPos, float dt, ChunkMap<Particle> &particles)
    {
        if (++m_pathRecalculateTimer >= m_pathRecalculateInterval && m_goalSet)
        {
            astar.reset(headPos, m_goal);
            m_pathRecalculateTimer = 0.0f;
        }
        if (!astar.endReached())
        {
            astar.iteratePath(1000);
            m_pathCheckpoints.clear();
            m_pathCheckpoints = astar.generatePath();
        }
    }

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

    void setGoal(Vec2<int> headPos, Vec2<int> goalPos)
    {
        m_goal = goalPos;
        m_goalSet = true;
    }

    void clearGoal()
    {
        m_pathCheckpoints.clear();
        m_goalSet = false;
    }

    void renderDebug(Viewport &viewport, const Camera &camera,
                     Vec2<int> headPos, float headAngle)
    {
        for (Vec2<int> p : m_sightPoints)
        {
            Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
            viewport.setPixel(ppos.x, ppos.y, Color(255, 252, 99));
        }

        for (Vec2<int> p : m_pathCheckpoints)
        {
            Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
            viewport.setPixel(ppos.x, ppos.y, Color(255, 105, 245));
        }
    }

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightAngle(float angle) { m_sightAngle = angle; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

  private:
    AStarWorldSolver astar;

    std::vector<Vec2<int>> m_sightPoints;

    std::vector<Vec2<int>> m_pathCheckpoints;

    bool m_goalSet = false;
    Vec2<int> m_goal = {0, 0};

    float m_pathRecalculateInterval = 2000.0f;
    float m_pathRecalculateTimer = 0.0f;

    float m_detectionRadius = 0.0f;
    float m_sightAngle = 0.0f;
    int m_sightDistance = 0;
    int m_sightRayAmount = 7;
};
