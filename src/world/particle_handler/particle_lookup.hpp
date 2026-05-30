#pragma once

#include "world/particle_handler/particle.hpp"
#include <optional>

std::optional<Particle> lookupParticleFromColor(Color color);
