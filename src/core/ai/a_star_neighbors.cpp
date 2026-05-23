#include "a_star_neighbors.hpp"

#include "core/math/geometry/vec.hpp"

const Vec2i NEIGHBOR_INDICES[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
