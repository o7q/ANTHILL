#include "world.hpp"

#include <SDL3/SDL.h>

World::World(SDL_Renderer *renderer,
             unsigned int width,
             unsigned int height) : m_world_texture(renderer, width, height)
{
    m_size.x = width;
    m_size.y = height;

    m_particles = new Particle *[height];

    for (int y = 0; y < m_size.y; ++y)
    {
        m_particles[y] = new Particle[m_size.x];

        for (int x = 0; x < m_size.x; ++x)
        {
            setParticle(x, y, Particle());
        }
    }

    m_world_physics.init(m_particles, &m_world_texture, m_size.x, m_size.y);
}

World::~World()
{
    for (int y = 0; y < m_size.y; ++y)
    {
        if (m_particles[y] != nullptr)
        {
            delete[] m_particles[y];
        }
    }
    if (m_particles != nullptr)
    {
        delete[] m_particles;
    }
}

void World::draw_particles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape)
{
    switch (drawShape)
    {
    case DrawShape::Square:
        for (int y = 0; y < radius; ++y)
        {
            for (int x = 0; x < radius; ++x)
            {
                int x_clamped = std::clamp(loc_x + x - radius / 2, 0, m_size.x - 1);
                int y_clamped = std::clamp(loc_y + y - radius / 2, 0, m_size.y - 1);

                setParticle(x_clamped, y_clamped, particle);
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

                    setParticle(x_clamped, y_clamped, particle);
                }
            }
        }
        break;
    }
}

void World::setParticle(int x, int y, Particle particle)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    m_particles[y][x] = particle;
    m_world_texture.setPixel(x, y, particle.color.hex());
}

Particle World::getParticle(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return Particle();
    }

    return m_particles[y][x];
}

void World::update()
{
    m_world_physics.update_particles();
    m_world_texture.update();
}