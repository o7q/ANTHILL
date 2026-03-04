#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/kinematic_controller.hpp"
#include "entity/world_collision_handler.hpp"
#include "world/world.hpp"
#include <cstdio>
#include <iostream>

class Entity
{
  public:
    Entity(World &world) : r_world(world), m_worldCollisionHandler(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    KinematicController &getController() { return m_kinematicController; }

  protected:
    void handleMotion() { m_kinematicController.applyGravity(); }

    void handleWorldInteractions(float dt)
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

    void handleWorldInteractions_colliding(float dt)
    {
        m_kinematicController.setMovementDamping(.9, .9);

        Vec2<int> pos = m_kinematicController.getPosition();
        if (m_worldCollisionHandler.againstSolidSurface(
                pos, BoundingBox::Side::Bottom))
        {
            m_kinematicController.haltMotionInDirection(0, 1);
        }

        m_kinematicController.update(dt);
    }
    void handleWorldInteractions_notColliding(float dt)
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
                    m_kinematicController.setPosition(steppedPos.x,
                                                      steppedPos.y);
                    pos = steppedPos;
                    blockedRight = false;
                    blockedLeft = false;
                    break;
                }
            }
        }

        // cancel motion in solid direction
        if (m_worldCollisionHandler.againstSolidSurface(pos,
                                                        BoundingBox::Side::Top))
        {
            m_kinematicController.haltMotionInDirection(0, -1);
        }
        if (m_worldCollisionHandler.againstSolidSurface(
                pos, BoundingBox::Side::Right))
        {
            m_kinematicController.haltMotionInDirection(1, 0);
        }
        if (m_worldCollisionHandler.againstSolidSurface(
                pos, BoundingBox::Side::Bottom))
        {
            m_kinematicController.haltMotionInDirection(0, 1);
        }
        if (m_worldCollisionHandler.againstSolidSurface(
                pos, BoundingBox::Side::Left))
        {
            m_kinematicController.haltMotionInDirection(-1, 0);
        }

        std::cout << m_kinematicController.getVelocity().x << " "
                  << m_kinematicController.getVelocity().y << std::endl;

        // resolve collisions
        Vec2<int> start = pos;

        m_kinematicController.update(dt);

        Vec2<int> end = m_kinematicController.getPosition();

        WorldCollisionHandler::TrajectoryCollisionResponse response =
            m_worldCollisionHandler.calculateCollisionFromTrajectory(start,
                                                                     end);
        if (response.collided)
        {
            m_kinematicController.setPosition(response.resolvePos.x,
                                              response.resolvePos.y);
        }
    }

  protected:
    World &r_world;

    KinematicController m_kinematicController;
    WorldCollisionHandler m_worldCollisionHandler;
};
