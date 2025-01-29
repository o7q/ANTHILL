#include "world.hpp"

World::World(SDL_Renderer *renderer, unsigned int width, unsigned int height) : m_world_texture(renderer, width, height)
{
    m_size.x = width;
    m_size.y = height;

    m_particles = new Particle *[height];

    for (unsigned int y = 0; y < m_size.y; ++y)
    {
        m_particles[y] = new Particle[m_size.x];

        for (unsigned int x = 0; x < m_size.x; ++x)
        {
            setParticle(x, y, Particle());
        }
    }
}

World::~World()
{
    for (unsigned int y = 0; y < m_size.y; ++y)
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

void World::setParticle(unsigned int x, unsigned int y, Particle particle)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    m_particles[y][x] = particle;
    m_world_texture.setPixel(x, y, particle.color);
}

void World::update()
{
    m_world_texture.update();
}