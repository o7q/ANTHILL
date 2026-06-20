#include "world_generator.hpp"

#include "px/utils/perlin.hpp"
#include "px/utils/random.hpp"
#include "px/utils/voronoi.hpp"
#include "world/particle_handler/biome.hpp"

BiomeID WorldGenerator::get_biome(px::Vec2i pos)
{
    const float voronoiSmear = px::Utils::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 2, m_seed) - 0.5f;
    const px::Utils::Voronoi::Sample sample = px::Utils::Voronoi::sampleEx(
        pos.toFloat() + voronoiSmear * 200.0f, {150.0f, 150.0f}, m_seed, px::Utils::Voronoi::Style::Normal);

    std::vector<px::Utils::Random::WeightedValue<BiomeID>> candidates;
    get_biome_candidates(pos, candidates);

    const uint32_t hash = px::Utils::Random::hashFromPosition(sample.cell, m_seed);
    return px::Utils::Random::weightedSelect(candidates, hash);
}

void WorldGenerator::get_biome_candidates(px::Vec2i pos,
                                          std::vector<px::Utils::Random::WeightedValue<BiomeID>> &candidates)
{
    const float layerBlend_surface =
        px::Utils::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 3, m_seed) - 0.5f;

    const float layerBlend_intermediate =
        px::Utils::Perlin::sampleEx(pos.toFloat(), {10.0f, 10.0f}, 1, m_seed) - 0.5f;

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
