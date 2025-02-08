#pragma once

#include "../entity/entity.hpp"

class Player : public Entity
{
public:
    Player(const World &world) : Entity(world)
    {
        m_bb_collider.setYSensitivity(4.0f);
    }
};