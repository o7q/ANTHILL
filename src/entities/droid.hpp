#pragma once

#include "backend/viewport/viewport.hpp"
#include "debug/renderers.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/head.hpp"
#include "entity/metadata.hpp"
#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "entity/modules/ai/perception/ai_perception.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "entity/update_context.hpp"
#include "math/numbers.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/navmesh.hpp"
#include "world/particle/particle.hpp"

class Droid : public Entity, public IHead
{
  public:
    Droid(uint64_t id) : Entity(id)
    {
        m_interactionBox.getBoundingBox().setSize(10, 20);
        m_body.setGravity(0.4f);

        m_aiPerception.setSightFOV(120);
        m_aiPerception.setSightRayAmount(20);
        m_aiPerception.setSightDistance(1000);

        AINavigation::Config cfg;
        cfg.astarIterationsPerFrame = 100;
        cfg.stuckTemper = 100;
        cfg.astarTerminationDistance = 0;
        cfg.astarMaxIterations = 10000000;
        cfg.checkpointEatRadius = 4;
        cfg.astarNeighborCheckFunction =
            [&](const EntityUpdateContext &context, Index2D index)
        {
            auto data = context.particles.getNavmesh().getChunk(index);

            if (!data.has_value())
            {
                return true;
            }

            return !data->containsSolid;
        };
        m_aiNavigation.setConfig(cfg);

        m_jumpHandler.setJumpPower(5);
        m_jumpHandler.setHoldDuration(0.0f);

        m_metadata.name = "Droid";
    }

    void update(const EntityUpdateContext &context) override
    {
        const Entity *player = nullptr;
        for (const Entity *entity : context.nearbyEntities)
        {
            if (entity->getMetadata().faction == EntityFaction::Player)
            {
                player = entity;
                break;
            }
        }

        if (player->getBody().getPosition() !=
            player->getBody().getLastPosition())
        {
            m_aiNavigation.setGoal(player->getBody().getPosition());
        }

        m_aiNavigation.update(m_body.getPosition(), context);

        auto result = m_aiNavigation.getMoveVector();

        if (result.has_value())
        {
            if (result->y < -4)
            {
                m_jumpHandler.requestJump();
            }
            m_body.setVelocityX(Math::Numbers::sign(result->x) * 5);
        }
        else
        {
            m_body.setVelocityX(0);
        }

        m_jumpHandler.update(
            context.dt, m_interactionBox.getWorldHandler().againstSolidSurface(
                            m_body.getPosition(), RectangleSide::Bottom,
                            context.particles));

        if (m_jumpHandler.canJump())
        {
            m_body.setVelocityY(-5);
        }

        updateMotion(context);
        updateHealth();
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);
        DEBUG_renderAINavigationInProgress(viewport, camera, m_aiNavigation);
        DEBUG_renderAINavigation(viewport, camera, m_aiNavigation);
    }

  private:
    JumpHandler m_jumpHandler;
    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;
};
