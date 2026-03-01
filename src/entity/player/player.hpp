#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "types/bounding_box.hpp"
#include "utils/math/line.hpp"
#include "utils/render.hpp"

class Player : public Entity
{
  public:
    struct CollisionResult
    {
        bool collided = false;
        Vec2<float> resolveDirection;
    };

  public:
    Player(World &world) : Entity(world)
    {
        m_collisionBox.setSize(Vec2<float>(30, 40));
    }
    ~Player() override {}

    void update(float dt) override
    {
        Vec2<int> start = m_verletBody.getPosition();

        m_verletBody.update(dt);

        Vec2<int> end = m_verletBody.getPosition();
        Vec2<int> size = m_collisionBox.getSize().floor();

        bool collided = false;
        int prevX = 0, prevY = 0;

        auto check = [&](int x, int y)
        {
            Vec2<int> topLeft = Vec2<int>(x, y) - size / 2;

            for (int y = 0; y < size.y; ++y)
            {
                for (int x = 0; x < size.x; ++x)
                {
                    Vec2<int> worldPos = topLeft + Vec2<int>(x, y);

                    Particle *p =
                        r_world.getParticleHandler().getParticles().get(
                            worldPos.x, worldPos.y);

                    if (!p)
                    {
                        continue;
                    }

                    if (p->isSolid())
                    {
                        collided = true;
                        return false;
                    }
                }
            }

            prevX = x;
            prevY = y;

            return true;
        };

        Utils::Math::Line::bresenhamLine(start, end, check);

        if (collided)
        {
            m_verletBody.setPosition(prevX, prevY);
        }
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<int> pos = m_verletBody.getPosition().floor();

        Vec2<int> a = m_collisionBox.getA() + pos;
        Vec2<int> b = m_collisionBox.getB() + pos - 1;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y);

        Utils::Render::drawRectOutline(viewport, a, b, Color(0, 255, 100));
    }
};
