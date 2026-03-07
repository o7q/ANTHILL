#include "entity.hpp"

#include "collision_box/entity_collision_box.hpp"
#include "collision_box/world/entity_world_collision.hpp"

void Entity::handleWorldInteractions(float dt)
{
    Vec2<int> pos = m_body.getPosition();
    Vec2<int> a = m_collisionBox.getBoundingBox().getA() + pos;
    Vec2<int> b = m_collisionBox.getBoundingBox().getB() + pos;

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
    m_body.setMovementDamping(0.9f, 0.9f);

    Vec2<int> pos = m_body.getPosition();
    if (m_collisionBox.getWorldHandler().againstSolidSurface(
            pos, BoundingBox::Side::Bottom))
    {
        m_body.haltMotionInDirection(0, 1);
    }

    m_body.update(dt);
}

void Entity::handleWorldInteractions_notColliding(float dt)
{
    m_body.setMovementDamping(0, 0);

    Vec2<int> pos = m_body.getPosition();
    Vec2<float> vel = m_body.getVelocity();

    bool blockedLeft = m_collisionBox.getWorldHandler().againstSolidSurface(
        pos, BoundingBox::Side::Left);
    bool blockedRight = m_collisionBox.getWorldHandler().againstSolidSurface(
        pos, BoundingBox::Side::Right);

    if ((blockedLeft && vel.x < 0) || (blockedRight && vel.x > 0))
    {
        for (int step = 1; step <= 3; ++step)
        {
            Vec2<int> steppedPos = {pos.x, pos.y - step};

            bool stillBlockedRight =
                blockedRight &&
                m_collisionBox.getWorldHandler().againstSolidSurface(
                    steppedPos, BoundingBox::Side::Right);
            bool stillBlockedLeft =
                blockedLeft &&
                m_collisionBox.getWorldHandler().againstSolidSurface(
                    steppedPos, BoundingBox::Side::Left);

            if (!stillBlockedRight && !stillBlockedLeft)
            {
                EntityWorldCollisionHandler::TrajectoryCollisionResponse test =
                    m_collisionBox.getWorldHandler()
                        .calculateCollisionFromTrajectory(pos, steppedPos);
                if (test.collided)
                {
                    break;
                }
                m_body.setPosition(steppedPos.x, steppedPos.y);
                pos = steppedPos;
                blockedRight = false;
                blockedLeft = false;
                break;
            }
        }
    }

    Vec2<int> start = pos;
    m_body.update(dt);
    Vec2<int> end = m_body.getPosition();

    EntityWorldCollisionHandler::TrajectoryCollisionResponse xy_response =
        m_collisionBox.getWorldHandler().calculateCollisionFromTrajectory(start,
                                                                          end);

    // all axis
    if (xy_response.collided)
    {
        Vec2<int> finalResolve = {0, 0};

        // horizontal axis
        Vec2<int> end_x = {end.x, xy_response.resolvePos.y};
        EntityWorldCollisionHandler::TrajectoryCollisionResponse x_response =
            m_collisionBox.getWorldHandler().calculateCollisionFromTrajectory(
                xy_response.resolvePos, end_x);

        if (xy_response.resolvePos == x_response.resolvePos)
        {
            // vertical axis
            Vec2<int> end_y = {xy_response.resolvePos.x, end.y};
            EntityWorldCollisionHandler::TrajectoryCollisionResponse
                y_response = m_collisionBox.getWorldHandler()
                                 .calculateCollisionFromTrajectory(
                                     xy_response.resolvePos, end_y);

            finalResolve = y_response.resolvePos;
        }
        else
        {
            finalResolve = x_response.resolvePos;
        }

        m_body.setPosition(finalResolve.x, finalResolve.y);
    }
}
