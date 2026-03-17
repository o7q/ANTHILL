#pragma once

#include "backend/viewport.hpp"
#include "entities/metadata.hpp"
#include "entities/module_wrappers/ai/grounded_ai_system/grounded_ai_system.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/directional.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "world/camera/camera.hpp"

class TestEntity : public Entity, public IDirectional
{
  public:
    TestEntity()
    {
        m_interactionBox.getBoundingBox().setSize(21, 30);
        m_body.setGravity(0.4f);

        m_ai.getPerception().setSightFOV(100);
        m_ai.getPerception().setSightRayAmount(20);
        m_ai.getPerception().setSightDistance(1000);
        m_ai.getNavigation().setAStarSubIterateAmount(1000);
        m_ai.getNavigation().setAStarMaxIterations(100000);
        m_ai.getNavigation().setAStarTerminationDistance(10);

        m_jumpHandler.setJumpPower(5);
        m_jumpHandler.setHoldDuration(0.0f);
    }

    void update(EntityUpdateContext &context) override
    {
        const Entity *player = nullptr;
        for (const Entity *entity : context.nearbyEntities)
        {
            if (entity->getMetadata().type == EntityType::Player)
            {
                player = entity;
                break;
            }
        }

        Vec2<int> pos = m_body.getPosition();
        if (player)
        {
            Vec2<int> playerPos = player->getBody().getPosition();

            if (playerPos != player->getBody().getLastPosition())
            {
                m_ai.getNavigation().setGoal(pos, playerPos);
            }
        }

        m_ai.update(pos, m_interactionBox.getBoundingBox(),
                    context.particles.getParticles(), context.dt);

        if (m_ai.getMovement().shouldMove())
        {
            m_body.setVelocityX(m_ai.getMovement().getMoveDirection().x * 4);

            if (m_ai.getMovement().getMoveDirection().y < 0)
            {
                m_jumpHandler.requestJump();
            }
        }
        else
        {
            m_body.setVelocityX(0);
        }

        if (m_ai.getMovement().shouldSetPosition())
        {
            m_body.setPosition(m_ai.getMovement().getSetPosition().x,
                               m_ai.getMovement().getSetPosition().y);
        }

        bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), RectangleSide::Bottom, context.particles);
        m_jumpHandler.update(context.dt, onGround);

        if (m_jumpHandler.canJump())
        {
            m_body.setVelocityY(-m_jumpHandler.getJumpPower());
        }
        updateMotion(context);
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);

        // m_aiPerception.renderDebug(viewport, camera);

        for (AINavigation::Checkpoint p :
             m_ai.getMovement().getMutatedCheckpoints())
        {
            Vec2<int> ppos = camera.worldToViewport(p.pos.x, p.pos.y, viewport);
            viewport.setPixel(ppos.x, ppos.y,
                              p.axis == AINavigation::Axis::Horizontal
                                  ? Color(255, 105, 245)
                                  : Color(255, 245, 105));
        }
    }

  private:
    JumpHandler m_jumpHandler;
    GroundedAISystem m_ai;
};
