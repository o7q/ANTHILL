#include "particle_lookup.hpp"
#include <optional>

std::optional<Particle> createParticlePreset(ParticlePresetID preset)
{
    switch (preset)
    {
    case ParticlePresetID::Air:
    {
        return Particle{};
    }
    case ParticlePresetID::BasicSolid:
    {
        Particle p;
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::None);
        p.setHardness(2);
        p.setRestitution(1.0f);
        p.setMass(1000000);
        return p;
    }
    default:
        return std::nullopt;
    }
}
