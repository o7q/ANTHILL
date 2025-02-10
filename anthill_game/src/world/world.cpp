#include "world.hpp"

#include <SDL3/SDL.h>

#include "../math/bounding_box.hpp"

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
            setParticle(x, y, Particle(Particle::Preset::Sand));
        }
    }

    m_world_physics.init(m_particles, &m_world_texture, m_size.x, m_size.y);
    m_world_texture.setOrigin(0, 0);
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

void World::update(BoundingBox *box)
{
    BoundingBox locked_bb(m_size.x / 2, m_size.y / 2, m_size.x, m_size.y);

    if (box != nullptr)
    {
        Vec2<int> pos = box->getPosition() - m_position;
        Vec2<int> size = box->getSize();
        locked_bb.setPosition(pos.x, pos.y);
        locked_bb.setSize(size.x, size.y);
    }

    for (int i = 0; i < update_speed; ++i)
    {
        m_world_physics.update_particles(&locked_bb);
    }

    generate_world_hitbox(&locked_bb);
    m_world_texture.update();
}