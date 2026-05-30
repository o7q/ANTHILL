#include "room.hpp"

#include "core/logger/logger.hpp"
#include "core/texture/texture.hpp"
#include "world/particle_handler/particle_lookup.hpp"

void Room::init(InitConfig config)
{
    Texture colorTexture(config.colorPath);
    Texture lookupTexture(config.lookupPath);
    Texture backgroundTexture(config.backgroundPath);

    if (!(colorTexture.getSize() == lookupTexture.getSize() &&
          lookupTexture.getSize() == backgroundTexture.getSize()))
    {
        Logger::error("Room::Room()", "Error configuring room! Mismatch between textures!");
        return;
    }

    m_size = colorTexture.getSize().toInt();

    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            StructurePositionalSpawnData data;

            Color colorPixel      = colorTexture.getPixel(Vec2u(x, y));
            Color lookupPixel     = lookupTexture.getPixel(Vec2u(x, y));
            Color backgroundPixel = backgroundTexture.getPixel(Vec2u(x, y));

            std::optional<Particle> lookup = lookupParticleFromColor(lookupPixel);

            if (lookup.has_value())
            {
                Particle p = lookup.value();
                p.setColor(colorPixel);
                data.particle                 = p;
                data.overwriteTerrainParticle = true;
            }

            data.backgroundColor            = backgroundPixel;
            data.overwriteTerrainBackground = true;
            data.overwriteTerrainEntities   = true;

            m_data.set({x, y}, data);
        }
    }
}
