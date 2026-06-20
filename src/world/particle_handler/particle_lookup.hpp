#pragma once

#include "world/particle_handler/particle.hpp"
#include <cstdint>
#include <optional>

enum class ParticlePresetID : uint32_t
{
    // ids embedded rgba colors
    Air   = 4294967295, // (255, 255, 255)
    Stone = 1684301055  // (100, 100, 100)
};

std::optional<Particle> createParticlePreset(ParticlePresetID id);
inline std::optional<Particle> createParticlePresetFromColor(px::Color color)
{
    return createParticlePreset(static_cast<ParticlePresetID>(color.embed()));
}
