#include "room.hpp"

#include "px/logger/logger.hpp"
#include "px/texture/texture.hpp"
#include "world/particle_handler/particle_lookup.hpp"

void Room::init(InitConfig config)
{
    px::Texture colorTexture(config.colorPath);
    px::Texture lookupTexture(config.lookupPath);
    px::Texture backgroundTexture = config.backgroundPath == "" ? px::Texture(colorTexture.getSize())
                                                                : px::Texture(config.backgroundPath);

    if (!(colorTexture.getSize() == lookupTexture.getSize() &&
          lookupTexture.getSize() == backgroundTexture.getSize()))
    {
        px::Logger::error("Room::Room()", "Error configuring room! Mismatch between textures!");
        return;
    }

    m_size = colorTexture.getSize().toInt();

    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            StructurePositionalSpawnData data;

            px::Color colorPixel      = colorTexture.getPixel(px::Vec2u(x, y));
            px::Color lookupPixel     = lookupTexture.getPixel(px::Vec2u(x, y));
            px::Color backgroundPixel = backgroundTexture.getPixel(px::Vec2u(x, y));

            std::optional<Particle> lookup = createParticlePresetFromColor(lookupPixel);

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
