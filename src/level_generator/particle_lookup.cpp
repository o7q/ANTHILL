#include "particle_lookup.hpp"

Particle lookupParticleFromColor(Color color)
{
    Particle p;
    switch (color.embed())
    {
    case 4278190335: // (255, 0, 0), basic solid
    {
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::None);
        p.setHardness(2);
        p.setRestitution(1.0f);
        p.setMass(1000000);
    }
    break;
    }
    return p;
}
