#include "world/particle_handler/biome.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/voronoi.hpp"
#include "world_generator.hpp"

BiomeID WorldGenerator::get_biome(Vec2i pos)
{
    const float voronoiSmear = Math::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 2, m_seed) - 0.5f;
    const Math::Voronoi::Sample sample = Math::Voronoi::sampleEx(
        pos.toFloat() + voronoiSmear * 200.0f, {150.0f, 150.0f}, m_seed, Math::Voronoi::Style::Normal);

    std::vector<BiomeWeight> candidates;
    get_biome_candidates(pos, candidates);

    // https://dev.to/jacktt/understanding-the-weighted-random-algorithm-581p
    int totalWeight = 0;
    for (const BiomeWeight &bw : candidates)
    {
        totalWeight += bw.weight;
    }

    const uint32_t hash = Math::Random::hashFromPosition(sample.cell, m_seed);
    const int random    = hash % totalWeight;

    int cursor = 0;
    for (const BiomeWeight &bw : candidates)
    {
        cursor += bw.weight;
        if (cursor > random)
        {
            return bw.id;
        }
    }

    return BiomeID::Void;
}

void WorldGenerator::get_biome_candidates(Vec2i pos, std::vector<BiomeWeight> &candidates)
{
    const float layerBlend_surface =
        Math::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 3, m_seed) - 0.5f;

    const float layerBlend_intermediate =
        Math::Perlin::sampleEx(pos.toFloat(), {10.0f, 10.0f}, 1, m_seed) - 0.5f;

    if (pos.y > 500 + layerBlend_intermediate * 30.0f)
    {
        candidates.push_back({BiomeID::DesertLayer2, 1});
    }
    else if (pos.y > 200 + layerBlend_surface * 20.0f)
    {
        candidates.push_back({BiomeID::DesertLayer1, 1});
        candidates.push_back({BiomeID::DesertLayer2, 1});
    }
    else if (pos.y > 0 + layerBlend_surface * 20.0f)
    {
        candidates.push_back({BiomeID::DesertLayer1, 1});
    }
}
