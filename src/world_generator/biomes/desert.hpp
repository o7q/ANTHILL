#pragma once

#include "world/particle_handler/particle.hpp"
#include <cstdint>

Particle generate_desert_layer1(Vec2i pos, uint32_t seed);
Particle generate_desert_layer2(Vec2i pos, uint32_t seed);
