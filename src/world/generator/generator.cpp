#include "generator.hpp"
#include "utils/data.hpp"
#include "world/generator/biomes/desert.hpp"

void Generator::generateInRadius(Vec2i origin, Vec2u size)
{
    Index2D chunkOrigin = r_world.getParticles().getChunkIndex(origin);
    Vec2i halfSize = (size / 2).toInt();
    Vec2u chunkSize = r_world.getParticles().getChunkSize();

    for (int cy = chunkOrigin.y - halfSize.y; cy <= chunkOrigin.y + halfSize.y;
         ++cy)
    {
        for (int cx = chunkOrigin.x - halfSize.x;
             cx <= chunkOrigin.x + halfSize.x; ++cx)
        {
            if (Utils::Data::doesVectorContain(m_generatedChunkMarkers,
                                               Index2D(cx, cy)))
            {
                continue;
            }

            m_generatedChunkMarkers.push_back(Index2D(cx, cy));

            for (unsigned int y = 0; y < chunkSize.y; ++y)
            {
                for (unsigned int x = 0; x < chunkSize.x; ++x)
                {
                    int ax = cx * chunkSize.x + x;
                    int ay = cy * chunkSize.y + y;

                    Particle p = generate_desert({ax, ay}, m_seed);
                    r_world.getEditor().set({ax, ay}, p);
                }
            }
        }
    }
}