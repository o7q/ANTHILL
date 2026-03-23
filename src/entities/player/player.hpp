#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/viewport.hpp"
#include "entities/projectile/projectile.hpp"
#include "entity/entity.hpp"
#include "entity/events.hpp"
#include "entity/interfaces/directional.hpp"
#include "entity/modules/inventory/inventory.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "math/angle.hpp"
#include "world/camera/camera.hpp"
#include <memory>

class Player : public Entity, public IDirectional
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets)
        : Entity(id, EntityType::Player), r_input(input),
          m_sprite(*assets.textures().get(TextureID::Character))
    {
        m_interactionBox.getBoundingBox().setSize(10, 25);
        m_body.setGravity(0.4f);
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
            // m_jumpModule.requestJump();
            m_body.setVelocityY(-m_jumpHandler.getJumpPower());
        }

        if (r_input.getInput(InputID::Jump)->wasUnpressed())
        {
            // m_jumpModule.cancelJump();
        }

        if (r_input.getInput(InputID::Action1)->wasPressed())
        {
            auto event = std::make_unique<EntitySpawnEvent>(getID());

            event->entityFactory = [&](uint64_t id)
            {
                auto proj = std::make_unique<Projectile>(
                    id, m_body.getPosition(), m_lookAngle);
                proj->setParent(getID());
                return proj;
            };

            m_eventEmitter.emit(std::move(event));
        }

        bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), RectangleSide::Bottom, context.particles);
        m_jumpHandler.update(context.dt, onGround);

        if (m_jumpHandler.canJump())
        {
            // m_body.setVelocityY(-m_jumpModule.getJumpPower());
        }

        updateMotion(context);
        updateHealth();
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        // viewport.drawSegment(camera.worldToViewport(m_body.getPosition().x,
        //                                             m_body.getPosition().y,
        //                                             viewport),
        //                      camera.worldToViewport(m_lookPosition.x,
        //                                             m_lookPosition.y,
        //                                             viewport),
        //                      Color(255, 0, 0));
        viewport.drawTexture(
            m_sprite, camera.worldToViewport(m_body.getPosition().x,
                                             m_body.getPosition().y, viewport));
        renderDebug_boundingBox(viewport, camera, Color(79, 255, 94));
    }

    void updateAimPosition(Vec2i aimPos)
    {
        m_lookPosition = aimPos;
        m_lookAngle = Math::Angle::vectorsToAngle(
            m_body.getPosition().toFloat(), aimPos.toFloat());
    }

  private:
    InputHandler &r_input;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2i m_mouseWorldPos;

    const Texture &m_sprite;
};
