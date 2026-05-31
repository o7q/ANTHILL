#pragma once

#include "world/particle_handler/particle.hpp"
#include <cstdint>
#include <optional>

enum class ParticlePresetID : uint32_t
{
    Air        = 4294967295, // (255, 255, 255)
    BasicSolid = 4278190335  // (255, 0, 0)
};

std::optional<Particle> createParticlePreset(ParticlePresetID id);
inline std::optional<Particle> createParticlePresetFromColor(Color color)
{
    return createParticlePreset(static_cast<ParticlePresetID>(color.embed()));
}
