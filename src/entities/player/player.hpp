#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/viewport.hpp"
#include "entities/projectile/projectile.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/head.hpp"
#include "entity/metadata.hpp"
#include "entity/modules/inventory/inventory.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "events/entity/entity_entity.hpp"
#include "math/angle.hpp"
#include "world/camera/camera.hpp"
#include <memory>

class Player : public Entity, public IHead
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets)
        : Entity(id), r_input(input),
          m_sprite(*assets.textures().get(TextureID::Character))
    {
        m_interactionBox.getBoundingBox().setSize(10, 25);
        m_body.setGravity(0.4f);
        m_metadata.faction = EntityFaction::Player;
    }
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    virtual void update(const EntityUpdateContext &context) override
    {
        if (r_input.getInput(InputID::Left)->isDown())
        {
            m_body.setVelocityX(-7);
        }
        if (r_input.getInput(InputID::Right)->isDown())
        {
            m_body.setVelocityX(7);
        }
        if (r_input.getInput(InputID::Left)->wasUnpressed())
        {
            m_body.setVelocityX(0);
        }
        if (r_input.getInput(InputID::Right)->wasUnpressed())
        {
            m_body.setVelocityX(0);
        }

        if (r_input.getInput(InputID::Jump)->wasPressed())
        {
            m_body.setVelocityY(-m_jumpHandler.getJumpPower());
        }

        if (r_input.getInput(InputID::Action1)->wasPressed())
        {
            auto event = EntitySpawnEvent(getID());

            event.entityFactory = [&](uint64_t id)
            {
                auto proj = std::make_unique<Projectile>(
                    id, getID(), m_body.getPosition(), m_angle);
                return proj;
            };

            m_eventEmitter.emit(event);
        }

        bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), RectangleSide::Bottom, context.particles);
        m_jumpHandler.update(context.dt, onGround);

        updateMotion(context);
        updateHealth();
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        viewport.drawTexture(
            m_sprite, camera.worldToViewport(m_body.getPosition().x,
                                             m_body.getPosition().y, viewport));
        renderDebug_boundingBox(viewport, camera, Color(79, 255, 94));
    }

    void updateAimPosition(Vec2i aimPos)
    {
        m_angle = Math::Angle::vectorsToAngle(m_body.getPosition().toFloat(),
                                              aimPos.toFloat());
    }

  private:
    InputHandler &r_input;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2i m_mouseWorldPos;

    const Texture &m_sprite;
};
