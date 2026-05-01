#pragma once

#include "world_generator/generate_result.hpp"
#include <cstdint>

GenerateResult generate_desert_layer1(Vec2i pos, uint32_t seed, const Assets &assets);
GenerateResult generate_desert_layer2(Vec2i pos, uint32_t seed, const Assets &assets);
