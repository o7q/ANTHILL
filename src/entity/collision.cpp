#include "entity.hpp"

#include "backend/types/vec.hpp"
#include <optional>

Vec2<float> Entity::calculateWorldResolvePosition()
{
    Vec2<float> posCurrent = m_verletBody.getPosition();
    Vec2<int> size = m_collisionBox.getSize();

    int i = 0;
    while (i < 100)
    {
        std::optional<Vec2<float>> result =
            calculate_world_resolve_direction(posCurrent, size);

        if (result.has_value())
        {
            posCurrent += result.value();
        }
        else
        {
            break;
        }

        ++i;
    }

    return posCurrent;
}

std::optional<Vec2<float>>
Entity::calculate_world_resolve_direction(Vec2<float> pos, Vec2<float> size)
{
    Vec2<float> sum(0, 0);
    int count = 0;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            int px = x + pos.x - size.x / 2.0f;
            int py = y + pos.y - size.y / 2.0f;

            Vec2<int> ppos = Vec2<int>(x, y) + pos - size / 2;

            Particle *p =
                r_world.getParticleHandler().getParticles().get(px, py);
            if (!p)
            {
                continue;
            }

            if (p->isSolid())
            {
                sum += (pos - ppos);
                ++count;
            }
        }
    }

    if (count == 0)
    {
        return std::nullopt;
    }

    return (sum / count).normalize();
}
