#include "world.hpp"

#include <algorithm>

void World::drawParticles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape, bool is_global_coordinate)
{
    if (is_global_coordinate)
    {
        loc_x -= m_position.x;
        loc_y -= m_position.y;
    }

    switch (drawShape)
    {
    case DrawShape::Square:
        for (int y = 0; y < radius; ++y)
        {
            for (int x = 0; x < radius; ++x)
            {
                int x_clamped = std::clamp(loc_x + x - radius / 2, 0, m_size.x - 1);
                int y_clamped = std::clamp(loc_y + y - radius / 2, 0, m_size.y - 1);

                setParticle(x_clamped, y_clamped, particle, false);
            }
        }
        break;
    case DrawShape::Circle:
        for (int y = loc_y - radius; y <= loc_y + radius; ++y)
        {
            for (int x = loc_x - radius; x <= loc_x + radius; ++x)
            {
                if ((x - loc_x) * (x - loc_x) + (y - loc_y) * (y - loc_y) <= radius * radius)
                {
                    int x_clamped = std::clamp(x, 0, m_size.x - 1);
                    int y_clamped = std::clamp(y, 0, m_size.y - 1);

                    setParticle(x_clamped, y_clamped, particle, false);
                }
            }
        }
        break;
    }
}

void World::setParticle(int x, int y, Particle particle, bool is_global_coordinate)
{
    if (is_global_coordinate)
    {
        x -= m_position.x;
        y -= m_position.y;
    }

    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    m_particles[y][x] = particle;
    m_world_texture.setPixel(x, y, particle.color.hex());
}

Particle World::getParticle(int x, int y, bool is_global_coordinate) const
{
    if (is_global_coordinate)
    {
        x -= m_position.x;
        y -= m_position.y;
    }

    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return Particle();
    }

    return m_particles[y][x];
}