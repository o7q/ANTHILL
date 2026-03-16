#pragma once

#include "backend/input_handler.hpp"
#include "backend/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/directional.hpp"
#include "entity/modules/inventory/inventory.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "item/weapon/weapon.hpp"
#include "utils/bounding_box.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle_handler.hpp"

class Player : public Entity, public IDirectional
{
  public:
    Player(ParticleHandler &particles, InputHandler &input)
        : Entity(EntityType::Player, particles), r_input(input)
    {
        m_interactionBox.getBoundingBox().setSize(10, 25);
        m_body.setGravity(0.4f);
    }
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    virtual void
    update(float dt, const std::vector<const Entity *> &nearbyEntities) override
    {
        if (r_input.getInput("left")->isDown())
        {
            m_body.setVelocityX(-7);
        }
        if (r_input.getInput("right")->isDown())
        {
            m_body.setVelocityX(7);
        }
        if (r_input.getInput("left")->wasUnpressed())
        {
            m_body.setVelocityX(0);
        }
        if (r_input.getInput("right")->wasUnpressed())
        {
            m_body.setVelocityX(0);
        }

        if (r_input.getInput("jump")->wasPressed())
        {
            // m_jumpModule.requestJump();
            m_body.setVelocityY(-m_jumpHandler.getJumpPower());
        }

        if (r_input.getInput("jump")->wasUnpressed())
        {
            // m_jumpModule.cancelJump();
        }

        bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Bottom);
        m_jumpHandler.update(dt, onGround);

        if (m_jumpHandler.canJump())
        {
            // m_body.setVelocityY(-m_jumpModule.getJumpPower());
        }

        updateMotion(dt);
        updateHealth();
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera, Color(79, 255, 94));
    }

  private:
    InputHandler &r_input;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Weapon *weapon = nullptr;
};
