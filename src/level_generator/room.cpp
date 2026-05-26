#include "room.hpp"

#include "core/logger/logger.hpp"
#include "core/texture/texture.hpp"
#include "entity/entity.hpp"
#include "level_generator/particle_lookup.hpp"

const std::unordered_map<Vec2i, std::vector<std::unique_ptr<Entity>>, Vec2Hash<int>>
Room::createEntities() const
{
    return {};
}

void Room::init(InitConfig config)
{
    Texture backgroundTexture(config.backgroundPath);
    Texture particleColorTexture(config.particleColorPath);
    Texture particleLookupTexture(config.particleLookupPath);

    if (!(backgroundTexture.getSize() == particleColorTexture.getSize() &&
          particleColorTexture.getSize() == particleLookupTexture.getSize()))
    {
        Logger::error("TestRoom::TestRoom()", "Error configuring room! Mismatch between textures!");
        return;
    }

    m_size = backgroundTexture.getSize().toInt();

    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            Color backgroundPixel = backgroundTexture.getPixel(Vec2u(x, y));
            Color colorPixel      = particleColorTexture.getPixel(Vec2u(x, y));
            Color lookupPixel     = particleLookupTexture.getPixel(Vec2u(x, y));

            Particle p = lookupParticleFromColor(lookupPixel);
            p.setColor(colorPixel);

            m_particles[{x, y}]  = p;
            m_background[{x, y}] = backgroundPixel;
        }
    }
}
