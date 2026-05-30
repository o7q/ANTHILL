#include "particle_lookup.hpp"
#include <optional>

std::optional<Particle> lookupParticleFromColor(Color color)
{
    switch (color.embed())
    {
    case 4294967295: // (255, 255, 255), air
    {
        return Particle{};
    }
    case 4278190335: // (255, 0, 0), basic solid
    {
        Particle p;
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::None);
        p.setHardness(2);
        p.setRestitution(1.0f);
        p.setMass(1000000);
        return p;
    }
    }

    return std::nullopt;
}
