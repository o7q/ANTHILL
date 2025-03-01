#include "player.hpp"

Player::Player(Window &window, const std::vector<World *> &worlds) : LivingEntity(window, worlds)
{
    m_bb_collider.setYSensitivity(4.0f);

    m_weapon = new Shotgun();
    m_weapon->setPower(10);
}

Player::~Player()
{
    if (m_weapon != nullptr)
    {
        delete m_weapon;
    }
}