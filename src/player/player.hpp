#pragma once

#include "backend/input_handler.hpp"
#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/living/living_entity.hpp"
#include "types/bounding_box.hpp"
#include "utils/render.hpp"
#include "world/particle/particle_handler.hpp"

class Player : public LivingEntity
{
  public:
    Player(ParticleHandler &particles, InputHandler &input)
        : LivingEntity(particles), r_input(input)
    {
        m_interactionBox.getBoundingBox().setSize(20, 30);
        m_body.setGravity(0.4f);

        m_metadata.type = EntityType::Player;
    }
    virtual ~Player() = default;

    void update(float dt) override
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
            jump();
        }

        updateInternal(dt);
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<int> pos = m_body.getPosition().toGrid();

        Vec2<int> a = m_interactionBox.getBoundingBox().getA() + pos;
        Vec2<int> b = m_interactionBox.getBoundingBox().getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y);

        Utils::Render::drawRectOutline(viewport, a, b, Color(0, 255, 100));
    }

  private:
    InputHandler &r_input;
};
