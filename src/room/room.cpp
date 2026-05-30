#include "room.hpp"

#include "core/logger/logger.hpp"
#include "core/texture/texture.hpp"
#include "world/particle_handler/particle_lookup.hpp"

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

            PositionalSpawnData &data = m_data[{x, y}];
            data.particle             = p;
            data.backgroundColor      = backgroundPixel;
        }
    }
}
