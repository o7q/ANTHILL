#include "entity.hpp"

void Entity::handleWorldInteractions(float dt)
{
    Vec2<int> pos = m_kinematicController.getPosition();
    Vec2<int> a = m_worldCollisionHandler.getCollisionBox().getA() + pos;
    Vec2<int> b = m_worldCollisionHandler.getCollisionBox().getB() + pos;

    int solidCount = 0;
    auto query = [&](Particle *p)
    {
        if (p->isSolid() && !p->inMotion())
        {
            solidCount++;
            return true;
        }
        return false;
    };
    r_world.getParticleHandler().query(a, b, query);

    if (solidCount > 0)
    {
        handleWorldInteractions_colliding(dt);
    }
    else
    {
        handleWorldInteractions_notColliding(dt);
    }
}

void Entity::handleWorldInteractions_colliding(float dt)
{
    m_kinematicController.setMovementDamping(0.9f, 0.9f);

    Vec2<int> pos = m_kinematicController.getPosition();
    if (m_worldCollisionHandler.againstSolidSurface(pos,
                                                    BoundingBox::Side::Bottom))
    {
        m_kinematicController.haltMotionInDirection(0, 1);
    }

    m_kinematicController.update(dt);
}

void Entity::handleWorldInteractions_notColliding(float dt)
{
    m_kinematicController.setMovementDamping(0, 0);

    Vec2<int> pos = m_kinematicController.getPosition();
    Vec2<float> vel = m_kinematicController.getVelocity();

    bool blockedLeft = m_worldCollisionHandler.againstSolidSurface(
        pos, BoundingBox::Side::Left);
    bool blockedRight = m_worldCollisionHandler.againstSolidSurface(
        pos, BoundingBox::Side::Right);

    if ((blockedLeft && vel.x < 0) || (blockedRight && vel.x > 0))
    {
        for (int step = 1; step <= 3; ++step)
        {
            Vec2<int> steppedPos = {pos.x, pos.y - step};

            bool stillBlockedRight =
                blockedRight && m_worldCollisionHandler.againstSolidSurface(
                                    steppedPos, BoundingBox::Side::Right);
            bool stillBlockedLeft =
                blockedLeft && m_worldCollisionHandler.againstSolidSurface(
                                   steppedPos, BoundingBox::Side::Left);

            if (!stillBlockedRight && !stillBlockedLeft)
            {
                m_kinematicController.setPosition(steppedPos.x, steppedPos.y);
                pos = steppedPos;
                blockedRight = false;
                blockedLeft = false;
                break;
            }
        }
    }

    Vec2<int> start0 = pos;
    m_kinematicController.update(dt);
    Vec2<int> end0 = m_kinematicController.getPosition();

    WorldCollisionHandler::TrajectoryCollisionResponse response0 =
        m_worldCollisionHandler.calculateCollisionFromTrajectory(start0, end0);

    // initial diagonal check
    if (response0.collided)
    {
        Vec2<int> finalResolve(0, 0);

        // horizontal check
        Vec2<int> end1 = {end0.x, response0.resolvePos.y};
        WorldCollisionHandler::TrajectoryCollisionResponse response1 =
            m_worldCollisionHandler.calculateCollisionFromTrajectory(start0,
                                                                     end1);

        if (response0.resolvePos == response1.resolvePos)
        {
            // vertical check
            Vec2<int> end2 = {response0.resolvePos.x, end0.y};
            WorldCollisionHandler::TrajectoryCollisionResponse response2 =
                m_worldCollisionHandler.calculateCollisionFromTrajectory(start0,
                                                                         end2);

            finalResolve = response2.resolvePos;
        }
        else
        {
            finalResolve = response1.resolvePos;
        }

        m_kinematicController.setPosition(finalResolve.x, finalResolve.y);
    }
}
