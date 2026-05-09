#include "a_star_neighbors.hpp"

#include "core/utils/data_structures/index_2d.hpp"

const Index2D NEIGHBOR_INDICES[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
