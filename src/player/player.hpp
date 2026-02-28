#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "utils/render.hpp"
#include <iostream>

class Player : public Entity
{
  public:
    Player(World &world) : Entity(world)
    {
        m_collisionBox.setSize(Vec2<float>(30, 40));
    }
    ~Player() override {}

    void update(float dt) override { m_verletBody.update(dt); }

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<float> pos = m_verletBody.getPosition();

        Vec2<float> a = m_collisionBox.getA() + pos;
        Vec2<float> b = m_collisionBox.getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y) - 1;

        Utils::Render::drawRectOutline(viewport, Vec2<int>(a.x, a.y),
                                       Vec2<int>(b.x, b.y), Color(0, 255, 100));

        Vec2<float> avg;
        int iter = 0;
        Vec2<float> centerpos = camera.worldToViewport(pos.x, pos.y);

        for (int y = 0; y < m_collisionBox.getSize().y; ++y)
        {
            for (int x = 0; x < m_collisionBox.getSize().x; ++x)
            {
                int px = x + pos.x - m_collisionBox.getSize().x / 2.0f;
                int py = y + pos.y - m_collisionBox.getSize().y / 2.0f;

                Vec2<float> ppos = camera.worldToViewport(px, py);

                Particle *p =
                    r_world.getParticleHandler().getParticles().get(px, py);
                if (!p)
                {
                    continue;
                }

                if (p->isSolid())
                {
                    Utils::Render::drawSegment(viewport, ppos, centerpos,
                                               Color(0, 0, 255));
                    avg += ppos;

                    ++iter;
                }
            }
        }

        if (iter > 0)
        {
            avg /= iter;

            Utils::Render::drawSegment(viewport, centerpos, avg,
                                       Color(255, 0, 0));
        }
    }
};
