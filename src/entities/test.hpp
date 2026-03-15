#pragma once

#include "backend/viewport.hpp"
#include "entities/metadata.hpp"
#include "entity/entity.hpp"
#include "entity/mixins/directional.hpp"
#include "entity/modules/ai/movement/ai_movement_module.hpp"
#include "entity/modules/ai/navigation/ai_navigation_module.hpp"
#include "entity/modules/ai/perception/ai_perception_module.hpp"
#include "entity/modules/jump/jump_module.hpp"
#include "world/camera/camera.hpp"

class TestEntity : public Entity, public IDirectional
{
  public:
    TestEntity(ParticleHandler &particles) : Entity(particles)
    {
        m_interactionBox.getBoundingBox().setSize(11, 11);
        m_body.setGravity(0.4f);

        m_aiPerception.setSightFOV(100);
        m_aiPerception.setSightRayAmount(20);
        m_aiPerception.setSightDistance(1000);
        m_aiNavigation.setAStarSubIterateAmount(1000);
        m_aiNavigation.setAStarMaxIterations(100000);
        m_aiNavigation.setAStarTerminationDistance(10);

        m_jumpModule.setHoldDuration(0.0f);
        m_jumpModule.setJumpPower(5);
    }

    void update(float dt,
                const std::vector<const Entity *> &nearbyEntities) override
    {
        const Entity *player = nullptr;
        for (const Entity *entity : nearbyEntities)
        {
            if (entity->getMetadata().type == EntityType::Player)
            {
                player = entity;
                break;
            }
        }

        if (player)
        {
            Vec2<int> pos = m_body.getPosition();
            Vec2<int> playerPos = player->getBody().getPosition();

            if (playerPos != player->getBody().getLastPosition())
            {
                m_aiNavigation.setGoal(pos, playerPos);
            }

            m_aiPerception.checkForInterestsInSight(
                pos, 0,
                [&](int x, int y)
                {
                    const Particle *p =
                        r_particleHandler.getParticles().get(x, y);

                    if (!p)
                    {
                        return false;
                    }

                    if (p->isSolid())
                    {
                        return true;
                    }

                    return false;
                });

            auto validSpot = [&](int x, int y)
            {
                Vec2<int> a = m_interactionBox.getBoundingBox().getA();
                Vec2<int> b = m_interactionBox.getBoundingBox().getB();

                Vec2<int> points[4] = {{x + a.x, y + a.y},
                                       {x + b.x, y + a.y},
                                       {x + a.x, y + b.y},
                                       {x + b.x, y + b.y}};

                // if (y < pos.y)
                // {
                //     bool ground = false;
                //     for (int i = 0; i < 40; ++i)
                //     {
                //         const Particle *p =
                //             r_particleHandler.getParticles().get(x, y + i);

                //         if (p)
                //         {
                //             if (p->isSolid())
                //             {
                //                 ground = true;
                //                 break;
                //             }
                //         }
                //     }

                //     if (!ground)
                //     {
                //         return false;
                //     }
                // }

                for (int i = 0; i < 4; ++i)
                {
                    const Particle *p = r_particleHandler.getParticles().get(
                        points[i].x, points[i].y);

                    if (!p)
                    {
                        continue;
                    }

                    if (!p->isSolid())
                    {
                        continue;
                    }

                    return false;
                }

                return true;
            };

            m_aiNavigation.update(dt, validSpot);

            if (m_aiNavigation.getPathState() ==
                AINavigationModule::PathState::Ready)
            {
                m_aiMovement.setCheckpoints(m_aiNavigation.getCheckpoints());
                m_aiNavigation.sleep();
            }

            m_aiMovement.update(pos, m_interactionBox.getBoundingBox());
        }

        if (m_aiMovement.shouldMove())
        {
            m_body.setVelocityX(m_aiMovement.getMoveDirection().x * 6);

            if (m_aiMovement.getMoveDirection().y < 0)
            {
                m_jumpModule.requestJump();
            }
        }
        else
        {
            m_body.setVelocityX(0);
        }

        if (m_aiMovement.shouldSetPosition())
        {
            m_body.setPosition(m_aiMovement.getSetPosition().x,
                               m_aiMovement.getSetPosition().y);
        }

        bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Bottom);
        m_jumpModule.update(dt, onGround);

        if (m_jumpModule.canJump())
        {
            m_body.setVelocityY(-m_jumpModule.getJumpPower());
        }
        updateMotion(dt);
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);

        m_aiPerception.renderDebug(viewport, camera);

        // for (AINavigationModule::Checkpoint p :
        //      m_aiMovement.getMutatedCheckpoints())
        // {
        //     Vec2<int> ppos = camera.worldToViewport(p.pos.x, p.pos.y, viewport);
        //     viewport.setPixel(ppos.x, ppos.y,
        //                       p.axis == AINavigationModule::Axis::Horizontal
        //                           ? Color(255, 105, 245)
        //                           : Color(255, 245, 105));
        // }
    }

  private:
    JumpModule m_jumpModule;
    AIPerceptionModule m_aiPerception;
    AINavigationModule m_aiNavigation;
    AIMovementModule m_aiMovement;
};
