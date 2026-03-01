#include "collision_handler.hpp"
#include "world/particle.hpp"
#include "world/world.hpp"
#include <array>

// minimum translation vector
Vec2<int> CollisionHandler::calculateWorldPenetration_MTV(Vec2<int> pos,
                                                          World &world)
{
    Vec2<int> size = m_collisionBox.getSize().toGrid();
    Vec2<int> topLeft = pos - size / 2;

    //    0
    // 3 [-] 1
    //    2
    bool collisionOccurred = false;
    std::array<int, 4> penetration = {0, 0, 0, 0};
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Vec2<int> worldPos = topLeft + Vec2<int>(x, y);

            Particle *p = world.getParticleHandler().getParticles().get(
                worldPos.x, worldPos.y);

            if (!p)
            {
                continue;
            }

            if (p->isSolid())
            {
                penetration[0] = std::max(penetration[0], y + 1);
                penetration[1] = std::max(penetration[1], size.x - x);
                penetration[2] = std::max(penetration[2], size.y - y);
                penetration[3] = std::max(penetration[3], x + 1);

                collisionOccurred = true;
            }
        }
    }

    if (!collisionOccurred)
    {
        return Vec2<int>(0, 0);
    }

    int lowest = std::numeric_limits<int>::max();
    int side = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (penetration[i] < lowest)
        {
            lowest = penetration[i];
            side = i;
        }
    }

    Vec2<int> out;
    switch (side)
    {
    case 0:
        out = Vec2<int>(0, lowest);
        break;
    case 1:
        out = Vec2<int>(-lowest, 0);
        break;
    case 2:
        out = Vec2<int>(0, -lowest);
        break;
    case 3:
        out = Vec2<int>(lowest, 0);
        break;
    }

    return out;
}

Vec2<float>
CollisionHandler::calculateWorldPenetration_averageDirection(Vec2<int> pos,
                                                             World &world)
{
    Vec2<int> size = m_collisionBox.getSize().floor();

    Vec2<int> topLeft = pos - size / 2;

    Vec2<float> sum(0, 0);
    int count = 0;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Vec2<int> worldPos = topLeft + Vec2<int>(x, y);

            Particle *p = world.getParticleHandler().getParticles().get(
                worldPos.x, worldPos.y);
            if (!p)
            {
                continue;
            }

            if (p->isSolid())
            {
                sum += (pos - worldPos);
                ++count;
            }
        }
    }

    if (count == 0)
    {
        return Vec2<float>(0, 0);
    }

    return (sum / count).normalize();
}
