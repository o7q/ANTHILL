#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "types/bounding_box.hpp"
#include "utils/render.hpp"
#include <iostream>

class Player : public Entity
{
  public:
    Player(World &world) : Entity(world)
    {
        m_collisionHandler.getCollisionBox().setSize(7, 7);
    }
    ~Player() override {}

    void update(float dt) override
    {
        Vec2<int> pos = m_kinematicController.getPosition().toGrid();
        if (m_collisionHandler.againstSurface(pos, 3, r_world))
        {
            std::cout << dt << std::endl;
        }

        // Vec2<int> start = m_kinematicController.getPosition().floor();

        m_kinematicController.update(dt);

        // Vec2<int> end = m_kinematicController.getPosition().floor();

        // Vec2<int> bounds =
        //     m_collisionHandler.getCollisionBox().getSize().floor();

        // bool collided = false;
        // int prevX = 0, prevY = 0;

        // bool collidedX = false, collidedY = false;

        // auto check = [&](int x, int y)
        // {
        //     Vec2<int> topLeft = Vec2<int>(x, y) - bounds / 2;

        //     for (int y = 0; y < bounds.y; ++y)
        //     {
        //         for (int x = 0; x < bounds.x; ++x)
        //         {
        //             Vec2<int> worldPos = topLeft + Vec2<int>(x, y);

        //             Particle *p =
        //                 r_world.getParticleHandler().getParticles().get(
        //                     worldPos.x, worldPos.y);

        //             if (!p)
        //             {
        //                 continue;
        //             }

        //             if (p->isSolid())
        //             {
        //                 collided = true;
        //                 if (end.x != prevX)
        //                 {
        //                     collidedX = true;
        //                 }
        //                 if (end.y != prevY)
        //                 {
        //                     collidedY = true;
        //                 }
        //                 return false;
        //             }
        //         }
        //     }

        //     prevX = x;
        //     prevY = y;

        //     return true;
        // };

        // Utils::Math::Line::bresenhamLine(start, end, check);

        // if (collided)
        // {
        //     m_kinematicController.setPosition(prevX, prevY);

        //     Vec2<float> curvel
        // }
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<int> pos = m_kinematicController.getPosition().toGrid();

        Vec2<int> a = m_collisionHandler.getCollisionBox().getA() + pos;
        Vec2<int> b = m_collisionHandler.getCollisionBox().getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y);

        Utils::Render::drawRectOutline(viewport, a, b, Color(0, 255, 100));
    }
};
