#pragma once

#include "backend/viewport.hpp"
#include "entity/base/interaction/entity_interaction_box.hpp"
#include "entity/base/kinetic_body/entity_kinetic_body.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/line.hpp"
#include "utils/math/numbers.hpp"
#include "utils/pathfinding/a_star.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle.hpp"
#include <iostream>
#include <vector>

class AIModule
{
  public:
    AIModule() {}

    void update(Vec2<int> headPos, float dt,
                const ChunkMap<Particle> &particles)
    {
        if (m_goalSet && !m_astar.endReached())
        {
            m_astar.iteratePath(m_astarSubIterateAmount,
                                [&](int x, int y)
                                {
                                    const Particle *p = particles.get(x, y);

                                    if (!p)
                                    {
                                        return true;
                                    }

                                    if (!p->isSolid())
                                    {
                                        return true;
                                    }

                                    return false;
                                });
        }

        if (m_goalSet && m_astar.endReached())
        {
            m_pathCheckpoints = m_astar.generatePath();
            m_goalSet = false;
        }
    }

    void setAStarMaxIterations(int maxIterations)
    {
        m_astar.setMaxIterations(maxIterations);
    }

    void AStarSubIterateAmount(int subIterateAmount)
    {
        m_astarSubIterateAmount = subIterateAmount;
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

    void updateBody(EntityKineticBody &body)
    {
        if (m_pathCheckpoints.empty())
        {
            return;
        }

        Vec2<int> pos = body.getPosition();

        Vec2<int> p = m_pathCheckpoints[0];

        int dirX = Utils::Math::Numbers::sign(p.x - pos.x);
        if ((dirX == -1 && pos.x <= p.x) || (dirX == 1 && pos.x >= p.x))
        {
            m_pathCheckpoints.erase(m_pathCheckpoints.begin());
        }

        body.setVelocityX(dirX);
    }

    void setGoal(Vec2<int> startPos, Vec2<int> endPos, bool force = false);
    void clearGoal();
    bool isGoalAlreadySet(Vec2<int> start, Vec2<int> end);

    void renderDebug(Viewport &viewport, const Camera &camera,
                     Vec2<int> headPos, float headAngle);

    void setDetectionRadius(float radius) { m_detectionRadius = radius; }
    void setSightAngle(float angle) { m_sightAngle = angle; }
    void setSightDistance(int distance) { m_sightDistance = distance; }
    void setSightRayAmount(int amount) { m_sightRayAmount = amount; }

  private:
    AStarSolver m_astar;
    int m_astarSubIterateAmount = 1000;

    std::vector<Vec2<int>> m_sightPoints;
    std::vector<Vec2<int>> m_pathCheckpoints;

    bool m_goalSet = false;
    Vec2<int> m_goalStartPos = {0, 0};
    Vec2<int> m_goalEndPos = {0, 0};

    float m_detectionRadius = 0.0f;
    float m_sightAngle = 0.0f;
    int m_sightDistance = 0;
    int m_sightRayAmount = 7;
};
