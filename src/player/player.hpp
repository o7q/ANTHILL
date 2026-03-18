#pragma once

#include "assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/directional.hpp"
#include "entity/modules/inventory/inventory.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "item/weapon/weapon.hpp"
#include "math/angle.hpp"
#include "math/rectangle.hpp"
#include "world/camera/camera.hpp"

class Player : public Entity, public IDirectional
{
  public:
    Player(InputHandler &input, const Assets &assets)
        : Entity(EntityType::Player), r_input(input),
          m_sprite(*assets.textures().get(TextureID::Character))
    {
        m_interactionBox.getBoundingBox().setSize(10, 25);
        m_body.setGravity(0.4f);
    }
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    virtual void update(EntityUpdateContext &context) override
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
        // renderDebug_boundingBox(viewport, camera, Color(79, 255, 94));
    }

    void updateAimPosition(Vec2<int> aimPos)
    {
        m_lookPosition = aimPos;
        m_lookAngle = Utils::Math::Angle::vectorsToAngle(
            m_body.getPosition().toFloat(), aimPos.toFloat());
    }

  private:
    InputHandler &r_input;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2<int> m_mouseWorldPos;

    const Texture &m_sprite;
};
