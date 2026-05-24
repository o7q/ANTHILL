#include "world_generator.hpp"

#include "core/math/perlin.hpp"
#include "core/math/random.hpp"
#include "core/math/voronoi.hpp"
#include "world/particle_handler/biome.hpp"

BiomeID WorldGenerator::get_biome(Vec2i pos)
{
    const float voronoiSmear = Math::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 2, m_seed) - 0.5f;
    const Math::Voronoi::Sample sample = Math::Voronoi::sampleEx(
        pos.toFloat() + voronoiSmear * 200.0f, {150.0f, 150.0f}, m_seed, Math::Voronoi::Style::Normal);

    std::vector<Math::Random::WeightedValue<BiomeID>> candidates;
    get_biome_candidates(pos, candidates);

    const uint32_t hash = Math::Random::hashFromPosition(sample.cell, m_seed);
    return Math::Random::weightedSelect(candidates, hash);
}

void WorldGenerator::get_biome_candidates(Vec2i pos,
                                          std::vector<Math::Random::WeightedValue<BiomeID>> &candidates)
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
