#pragma once

#include "backend/types/vec.hpp"
#include "types/bounding_box.hpp"
#include "world/world.hpp"

class CollisionHandler
{
  public:
    CollisionHandler() {}

    BoundingBox &getCollisionBox() { return m_collisionBox; }

    Vec2<int> calculateWorldPenetration_MTV(Vec2<int> pos, World &world);
    Vec2<float> calculateWorldPenetration_averageDirection(Vec2<int> pos,
                                                           World &world);

    bool againstSurface(Vec2<int> pos, int side, World &world)
    {
        //    0
        // 3 [-] 1
        //    2

        Vec2<int> size = m_collisionBox.getSize();

        Vec2<int> topLeft = pos + m_collisionBox.getA();

        switch (side)
        {
        case 0:
        {
            for (int x = 0; x < size.x; ++x)
            {
                Particle *p = world.getParticleHandler().getParticles().get(
                    topLeft.x + x, topLeft.y - 1);

                if (!p)
                {
                    continue;
                }

                if (p->isSolid())
                {
                    return true;
                }
            }
        }
        break;
        case 1:
        {
            Vec2<int> topRight = Vec2<int>(topLeft.x + size.x, topLeft.y);
            for (int y = 0; y < size.y; ++y)
            {
                Particle *p = world.getParticleHandler().getParticles().get(
                    topRight.x + 1, topRight.y + y);

                if (!p)
                {
                    continue;
                }

                if (p->isSolid())
                {
                    return true;
                }
            }
        }
        break;
        case 2:
        {
            Vec2<int> bottomLeft = Vec2<int>(topLeft.x, topLeft.y + size.y);
            for (int x = 0; x < size.x; ++x)
            {
                Particle *p = world.getParticleHandler().getParticles().get(
                    bottomLeft.x + x, bottomLeft.y + 1);

                if (!p)
                {
                    continue;
                }

                if (p->isSolid())
                {
                    return true;
                }
            }
        }
        break;
        case 3:
        {
            for (int y = 0; y < size.y; ++y)
            {
                Particle *p = world.getParticleHandler().getParticles().get(
                    topLeft.x - 1, topLeft.y + y);

                if (!p)
                {
                    continue;
                }

                if (p->isSolid())
                {
                    return true;
                }
            }
        }
        break;
        }

        return false;
    }

  private:
    BoundingBox m_collisionBox;
};
