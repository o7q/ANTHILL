#pragma once

#include "assets/assets.hpp"
#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/head.hpp"
#include "entity/metadata.hpp"
#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "entity/modules/ai/perception/ai_perception.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "entity/update_context.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"
#include "math/numbers.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/navmesh.hpp"

class Droid : public Entity, public IHead
{
  public:
    Droid(uint64_t id, const Assets &assets) : Entity(id), r_assets(assets)
    {
        m_interactionBox.getBoundingBox().setSize(10, 20);
        m_body.setGravity(0.4f);

        m_aiPerception.setSightFOV(120);
        m_aiPerception.setSightRayAmount(20);
        m_aiPerception.setSightDistance(1000);

        AINavigation::Config cfg;
        cfg.astarIterationsPerFrame = 100;
        cfg.stuckTemper = 100;
        cfg.astarTerminationDistance = 2;
        cfg.astarMaxIterations = 10000000;
        cfg.checkpointEatRadius = 10;
        cfg.astarNeighborCheckFunction =
            [&](const EntityUpdateContext &context, Index2D index)
        {
            auto data = context.particles.getNavmesh().getChunkFromIndex(index);

            Vec2i pos = Vec2i(index.x, index.y) *
                        context.particles.getNavmesh().getResolution().toInt();

            Vec2i a = m_interactionBox.getBoundingBox().getA();
            Vec2i b = m_interactionBox.getBoundingBox().getB();

            Vec2i topLeft = pos + Vec2i(a.x, a.y);
            Vec2i topRight = pos + Vec2i(b.x, a.y);
            Vec2i bottomLeft = pos + Vec2i(a.x, b.y);
            Vec2i bottomRight = pos + Vec2i(b.x, b.y);

            bool solid = false;

            auto test = [&](const Particle *p)
            {
                if (p->isSolid())
                {
                    solid = true;
                    return true;
                }

                return false;
            };

            context.particles.query(topLeft, topRight, test);
            context.particles.query(topLeft, bottomLeft, test);
            context.particles.query(bottomLeft, bottomRight, test);
            context.particles.query(topRight, bottomRight, test);

            if (solid)
            {
                return false;
            }

            if (!data)
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

        if (!player)
        {
            return;
        }

        Vec2i playerPos = player->getBody().getPosition();

        if (playerPos != player->getBody().getLastPosition())
        {
            m_aiNavigation.setGoal(player->getBody().getPosition());
        }

        int dx = std::abs(playerPos.x - m_body.getPosition().x);
        int dy = std::abs(playerPos.y - m_body.getPosition().y);

        if (dx + dy < 50)
        {
            auto particleEvent =
                std::make_unique<EntityParticleDrawEvent>(getID());
            Particle p;
            p.setMatterType(Particle::MatterType::Liquid);
            p.setPhysicsType(Particle::PhysicsType::Water);
            p.setColor(Color(220, 10, 10));
            p.setRestitution(0.1f);
            particleEvent->particleEvent.particle = p;
            particleEvent->particleEvent.position = playerPos;
            particleEvent->particleEvent.radius = 10;

            m_eventEmitter.emit(std::move(particleEvent));
        }

        m_aiNavigation.update(m_body.getPosition(), context);

        auto result = m_aiNavigation.getMoveVector();

        if (result.has_value())
        {
            if (result->y < -4)
            {
                m_body.setVelocityY(-5);
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

        // if (m_jumpHandler.canJump())
        // {
        //     m_body.setVelocityY(-5);
        // }

        updateMotion(context);
        updateHealth();
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);
        viewport.drawTexture(*r_assets.textures().get(TextureID::TheMan2),
                             camera.worldToViewport(m_body.getPosition().x,
                                                    m_body.getPosition().y,
                                                    viewport));
    }

  private:
    const Assets &r_assets;
    JumpHandler m_jumpHandler;
    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;
};
